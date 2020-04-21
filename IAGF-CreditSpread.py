"""
Created on Wed Jan 23 11:05:42 2019

@author: wenca
"""
import datetime
import numpy as np
import pandas as pd
import scipy as sp
#IAQF  credit sread prediction
class Para():
    def __init__(self):
        self.monthTestStart = None
        self.monthTestEnd = None
        self.method = 'XGBOOST-L' #XGBOOST-L 
        self.dataPath = 'C:\\Users\\wenca\\Desktop\\IAQF\\' #csv_demo_hs300 or csv_demo_zz500
        self.resultPath = '.\\results_single\\' + self.method + '\\'
def go(para, data1,data2):

#-- basic parameters
    global model
    method = para.method #choose methods
    
    if method == 'XGBOOST-R'  : #-- regression
        percentBin = 0.3
    elif method == 'GBDT-C' or method == 'XGBOOST-C' or method == 'XGBOOST-L': #-- classification
        percentBin = 0.3 #-- 30% postive samples, 30% negtive samples
    isPCA = 0 #I didn't perform PCA, so we add a parameter
    from xgboost import XGBRegressor

    data1=data1[~data1['TEST'].isin(["."])]
    data=data[~data['DGS10'].isin(["."])]
    x=pd.DataFrame(data.loc[:,"TEST"].astype('float'))
    y=pd.DataFrame(data.loc[:,"DGS10"].astype('float'))
    result = pd.concat([df1, df4], axis=1, join_axes=[df1.index])
    model = XGBRegressor(random_state=10, subsample = 0.9)
    model.fit(dfTrainX, dfTrainY)
    fi = pd.DataFrame(data=model.feature_importances_).transpose()
    arPredictedCScore = model.predict(dfTrainX)
    return arPredictedCScore
#######main
para=Para()
nameFile = para.dataPath + 'DGS10.csv'
data1 = pd.read_csv(para.dataPath + 'DGS10.csv',index_col="DATE")
data2=pd.DataFrame(para.dataPath + 'BAMLC0A1CAAAEY.csv')
a=(go(para, data1,data2))
