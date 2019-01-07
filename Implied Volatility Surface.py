# -*- coding: utf-8 -*-
"""
Created on Fri Jan  4 11:39:52 2019

@author: wenca
"""
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from scipy.stats import norm
from numpy import linspace,meshgrid,cos
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import math
from lxml import html  
import time
import re
from urllib.request import urlopen
from bs4 import BeautifulSoup

class Para():
    def __init__(self):
        self.opt=1 ####choose 1 as call,0 as put.

Date = ["2019-01-10 19:00:00","2019-01-17 19:00:00","2019-01-24 19:00:00","2019-01-31 19:00:00",
          "2019-02-07 19:00:00","2019-02-14 19:00:00","2019-02-21 19:00:00","2019-03-14 20:00:00",
          "2019-04-17 20:00:00","2019-06-20 20:00:00","2019-07-18 20:00:00","2020-01-16 19:00:00",
          "2020-06-18 20:00:00","2021-01-14 19:00:00"]
#Date = ["2019-01-17 19:00:00"]
ticker = "AAPL"
S=148
K=list(range(S-10,S+10))
T=[]
for d in Date:
    import time
    timestamp=int(time.mktime(time.strptime(d[:10], "%Y-%m-%d")))
    now=int(time.mktime(time.strptime("2019-01-06", "%Y-%m-%d")))
    time = (timestamp-now)/(3600*12)
    T.append(round(time/365,4))

##########################parse option data from yahoo finance
def parseOpt(ticker,Date):
    callOpt={}
    putOpt={}
    for date in Date:
        import time
        timeArray = time.strptime(date, "%Y-%m-%d %H:%M:%S")
        timestamp = int(time.mktime(timeArray))
        htmlz = urlopen(
            "https://finance.yahoo.com/quote/%s/options?straddle=false&date=%s"%(ticker,timestamp)).read().decode('utf-8')
        soup = BeautifulSoup(htmlz, features='lxml')
        Strike= soup.find_all('td', {'class': re.compile('data-col2')})
        Price=soup.find_all('td', {'class': re.compile('data-col3')})
        iVol= soup.find_all('td', {'class': re.compile('data-col10')})
        callPrice=[]
        putPrice=[]
        strike=[]
        iV=[]
        iV.append(iVol[0].get_text())
        strike.append(Strike[0].get_text())
        callPrice.append(Price[0].get_text())
        flag=0
        for i in range(1,len(Price)):
            iV.append(iVol[i].get_text())
            strike.append(Strike[i].get_text())
            if float(strike[i])<=float(strike[i-1]):####begin to record put opiton price
                flag=1
            if flag==0:
                callPrice.append(Price[i].get_text())
            else:
                putPrice.append(Price[i].get_text())
        callStrike=strike[:len(callPrice)]####split the strikes into call and put
        putStrike=strike[len(callPrice):]
        callIV=iV[:len(callPrice)]
        putIV=iV[len(callPrice):]
        callOpt[date[:10]]=pd.DataFrame(callPrice,index=callStrike),pd.DataFrame(callIV,index=callStrike)
        putOpt[date[:10]]=pd.DataFrame(putPrice,index=putStrike),pd.DataFrame(putIV,index=putStrike)
    return callOpt,putOpt,callStrike,putStrike

#
#######################Retrieve real option price with other sourse
def RealPrice(callOpt,putOpt,t,k,T,Date,opt):
    date=Date[T.index(t)][:10]
    k=str(k)+".00"#############################because this k is intagers when initialized
    if opt==1:##choose return option type
        try:return float(callOpt[date][0].loc[k][0])
        except:
            print(date,"and the",k,"don't exist") 
            return 0
    elif opt==0:
        try:return float(putOpt[date][0].loc[k][0])
        except:
            print(date,"and the",k,"don't exist")
            return 0
########################BS price
def BSPrice(Stock,Exercise,Time,Rf,sigma):
    S = float(Stock)
    E = float(Exercise)
    T = float(Time)
    r = float(Rf)
    d_1 = float(float((math.log(S/E)+(r+(sigma**2)/2)*T))/float((sigma*(math.sqrt(T)))))
    d_2 = float(float((math.log(S/E)+(r-(sigma**2)/2)*T))/float((sigma*(math.sqrt(T)))))
    BSPrice = float(S*norm.cdf(d_1) - E*math.exp(-r*T)*norm.cdf(d_2))
    return BSPrice
######################calculate the impied volatility
def implied_volatility(Price,Stock,Exercise,Time,Rf):
    P = float(Price)
    S = float(Stock)
    E = float(Exercise)
    T = float(Time)
    r = float(Rf)
   
    left=0.0001
    right=10
    PLeft=BSPrice(S,E,T,r,left)-P
    PRight=BSPrice(S,E,T,r,right)-P
    while  right-left> 0.001:
        PLeft=BSPrice(S,E,T,r,left)-P
        PRight=BSPrice(S,E,T,r,right)-P
        if PLeft*PRight<=0:
            sigma=(left+right)/2
            PMid=BSPrice(S,E,T,r,sigma)-P
            if PMid*PLeft<0:
                right=sigma
            else:
                left=sigma
        else:
            return 0
            break
    return (left+right)/2
#####################calculate the surf of implied volatitlity
def surfIV(S,K,T,callOpt,putOpt):
    IV=[]
    for k in K:
        cur=[]
        for t in T:
            p=RealPrice(callOpt,putOpt,t,k,T,Date,Para.opt)##I choose call option here
            cur.append(implied_volatility(p,S,k,t,0.05))
        IV.append(cur)
    #Iv=pd.DataFrame(IV,index=K,columns=T)
    #plt.plot(Iv)
    return IV
#####################plot the surf
def plotIV(S,K,T,callOpt,putOpt):
    X,Y = meshgrid(K, T)
    iv=np.array(surfIV(S,K,T,callOpt,putOpt)).T
    fig = plt.figure(figsize=(14,6))
    # `ax` is a 3D-aware axis instance, because of the projection='3d' keyword argument to add_subplot
    ax = fig.add_subplot(1, 2, 1, projection='3d')
    surf = ax.plot_surface(X, Y, iv, cmap=cm.coolwarm,
                           linewidth=0, antialiased=False)
    return surf
##########################################main function
callOpt,putOpt,callStrike,putStrike=parseOpt(ticker,Date)
iv=surfIV(S,K,T,callOpt,putOpt)
#plt.plot(K,iv)
plotIV(S,K,T,callOpt,putOpt)
#ivo=[]
#for k in K:
#    i=callOpt["2019-01-17"][1].loc[k][0].replace(",","").replace("%","")
#    ivo.append(float(i))
#plt.plot(K,ivo)
