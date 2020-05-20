# -*- coding: utf-8 -*-
"""
Created on Fri Jan  4 11:39:52 2019

@author: wenca
"""
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from scipy.stats import norm
from numpy import meshgrid
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import math
import datetime as dt
import time
import re
from urllib.request import urlopen
from bs4 import BeautifulSoup

class Para():
    def __init__(self):
        self.opt=1 ####choose 1 as call,0 as put.
        self.S=148
        self.r=0.05
        self.ticker = "AAPL"
para = Para()
Date = ["2019-01-10 19:00:00","2019-01-17 19:00:00","2019-01-24 19:00:00","2019-01-31 19:00:00",
          "2019-02-07 19:00:00","2019-02-14 19:00:00","2019-02-21 19:00:00","2019-03-14 20:00:00",
          "2019-04-17 20:00:00","2019-06-20 20:00:00","2019-07-18 20:00:00","2020-01-16 19:00:00",
          "2020-06-18 20:00:00","2021-01-14 19:00:00"]
#Date = ["2019-01-17 19:00:00"]
##############notice that K in every date of option are differently distributed
K=list(range(para.S-40,para.S+10))
T=[]
for d in Date:
    import time
    timestamp=int(time.mktime(time.strptime(d[:10], "%Y-%m-%d")))
    now=int(time.mktime(time.strptime("2019-01-06", "%Y-%m-%d")))
    time = (timestamp-now)/(3600*12)
    T.append(round(time/365,4))

##########################parse option data from yahoo finance
def parseOpt(para,Date):
    callOpt={}
    putOpt={}
    for date in Date:
        import time
        timeArray = time.strptime(date, "%Y-%m-%d %H:%M:%S")
        timestamp = int(time.mktime(timeArray))
        htmlz = urlopen(
            "https://finance.yahoo.com/quote/%s/options?straddle=false&date=%s"%(para.ticker,timestamp)).read().decode('utf-8')
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
#######################Retrieve real option price with yahoo
def RealPrice(callOpt,putOpt,t,k,T,Date,opt):
    date=Date[T.index(t)][:10]
    k=str(k)+".00"#############################because this k is intager when initialized
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
def BSPrice(Exercise,Time,sigma,para):
    K = float(Exercise)
    T = float(Time)
    d_1 = float(float((math.log(para.S/K)+(para.r+(sigma**2)/2)*T))/float((sigma*(math.sqrt(T)))))
    d_2 = float(float((math.log(para.S/K)+(para.r-(sigma**2)/2)*T))/float((sigma*(math.sqrt(T)))))
    BSPrice = float(para.S*norm.cdf(d_1) - K*math.exp(-para.r*T)*norm.cdf(d_2))
    return BSPrice
######################calculate the impied volatility
def implied_volatility(Price,Exercise,Time,para):
    P = float(Price)
    K = float(Exercise)
    T = float(Time)
    left=0.0001
    right=10
    PLeft=BSPrice(K,T,left,para)-P
    PRight=BSPrice(K,T,right,para)-P
    while  right-left> 0.001:
        PLeft=BSPrice(K,T,left,para)-P
        PRight=BSPrice(K,T,right,para)-P
        if PLeft*PRight<=0:
            sigma=(left+right)/2
            PMid=BSPrice(K,T,sigma,para)-P
            if PMid*PLeft<0:
                right=sigma
            else:
                left=sigma
        else:
            return 0
            break
    return (left+right)/2
#####################calculate the surf of implied volatitlity
def surfIV(K,T,callOpt,putOpt,para):
    IV=[]
    for k in K:
        cur=[]
        for t in T:
            p=RealPrice(callOpt,putOpt,t,k,T,Date,para.opt)##I choose call option here
            cur.append(implied_volatility(p,k,t,para))
        IV.append(cur)
    #iv=pd.DataFrame(IV,index=K,columns=T)
    #########################################  smooth the iv refill the zeros with average
#    for i in IV:
#        for j in range(len(i)):
#            if i[j]==0:
#                if j==0:
#                    i[j]=i[j+1]/2
#                elif j==len(i)-1:
#                    i[j]=i[j-1]/2
#                else:
#                    i[j]=(i[j-1]+i[j+1])/2
#    IV=np.array(IV).T.tolist()
#    for i in IV:
#        for j in range(len(i)):
#            if i[j]==0:
#                if j==0:
#                    i[j]=i[j+1]/2
#                elif j==len(i)-1:
#                    i[j]=i[j-1]/2
#                else:
#                    i[j]=(i[j-1]+i[j+1])/2
    ########################################smooth the iv refill the zeros with last value

    for i in IV:
        for j in range(len(i)):
            if i[j]==0:
                if j==0:
                    k=j+1
                    while i[k]==0 and k!=len(i)-1:##find next nonzero
                        k+=1
                    if k==len(i)-1:
                        break
                    i[j]=i[k]
                else:
                    i[j]=i[j-1]
    IV=np.array(IV).T.tolist()
    for i in IV:
        for j in range(len(i)):
            if i[j]==0:
                if j==0:
                    k=j+1
                    while i[k]==0 and k!=len(i)-1:##find next nonzero
                        k+=1
                    i[j]=i[k]
                    if k==len(i)-1:
                        break
                    
                else:
                    i[j]=i[j-1]
    IV=np.array(IV).T.tolist()
#    plt.plot(Iv)
    return IV
#####################plot the surf
def plotIV(K,T,callOpt,putOpt,para):
    X,Y = meshgrid(K, T)
    iv=np.array(surfIV(K,T,callOpt,putOpt,para)).T
    fig = plt.figure(figsize=(14,6))
    # `ax` is a 3D-aware axis instance, because of the projection='3d' keyword argument to add_subplot
    ax = fig.add_subplot(1, 2, 1, projection='3d')
    surf = ax.plot_surface(X, Y, iv, cmap=cm.coolwarm,
                           linewidth=0, antialiased=False)
    return surf
##########################################main function
callOpt,putOpt,callStrike,putStrike=parseOpt(para,Date)

iv=surfIV(K,T,callOpt,putOpt,para)
#plt.plot(K,iv)
plotIV(K,T,callOpt,putOpt,para)
#ivo=[]
#for k in K:
#    i=callOpt["2019-01-17"][1].loc[k][0].replace(",","").replace("%","")
#    ivo.append(float(i))
#plt.plot(K,ivo)
