# -*- coding: utf-8 -*-
"""
Created on Thu Nov 14 18:33:46 2017

@author: Wencai Zheng
"""

import datetime
import numpy as np
import pandas as pd
import scipy as sp
from sklearn.externals.six import StringIO  
#import pydot
#from evaluation import *
#-------------------------------------------choose your factors--------------------------------------------------------
Chosenfactors=['EP','BP'] # 2 out of 71

names = pd.read_csv('name_test.csv')
names=names.loc[:,Chosenfactors]
names=names.columns
fi_all = pd.DataFrame(columns=names)
score_all = pd.DataFrame(columns=names)

#coef_all = pd.DataFrame(columns=names)

class Para():
    def __init__(self):
        self.monthTestStart = None
        self.monthTestEnd = None
        self.previous_month = 72
        self.method = 'XGBOOST-L' #XGBOOST-L 
        self.dataPath = 'C:\\Users\\wenca\\Desktop\\Original desk\\xgboost\\csv_demo\\' #csv_demo_hs300 or csv_demo_zz500
        self.resultPath = '.\\results_single\\' + self.method + '\\'
        
def go(para, fac_1):

#-- basic parameters
    global model
    method = para.method #choose methods
    resultPath = '.\\results_single\\' + method + '\\'
    monthTrain = range(para.monthTestStart-para.previous_month,para.monthTestStart) #-- 72 months
    monthTest = range(para.monthTestStart,para.monthTestEnd+1) #-- test on next 12 months
    
    
    #monthTrain2 = range(para.monthTestStart-para.previous_month - 150, para.monthTestStart-para.previous_month - 100)

    #dictInfo = {'indMonth':0,'indStock':1,'is_trading':2,'Y1':3,'Y2':4,'is_limit_up':5,'days_from_ipo':6,'ln_mkt_cap_ard':7,'is_not_stpt':8}
    if method == 'XGBOOST-R'  : #-- regression
        percentBin = 0.3
    elif method == 'GBDT-C' or method == 'XGBOOST-C' or method == 'XGBOOST-L': #-- classification
        percentBin = 0.3 #-- 30% postive samples, 30% negtive samples
    isPCA = 0 #I didn't perform PCA, so we add a parameter


    
    import os
    #-- check data folder
    if not os.path.exists(para.dataPath):
        print('missing ./data/csv folder')
        raise(IOError)
    #-- generate results folder
    if not os.path.exists(resultPath):
        os.makedirs(resultPath)
    
    #-- generate raw within-sample data
    
    for iMonth in monthTrain:
        #print(iMonth)
        nameFile = para.dataPath + str(iMonth) + '.csv'
        dfCurrMonth = pd.read_csv(nameFile)
        dfCurrMonth = dfCurrMonth.dropna(axis=0)
        if iMonth == monthTrain[0]:
            dfWithinRaw = dfCurrMonth
        else:
            dfWithinRaw = dfWithinRaw.append(dfCurrMonth,ignore_index=True)
    dfWithinRaw.index = range(len(dfWithinRaw))
    
    '''
    for iMonth in monthTrain2:
        print(iMonth)
        nameFile = para.dataPath + str(iMonth) + '.csv'
        dfCurrMonth = pd.read_csv(nameFile)
        dfCurrMonth = dfCurrMonth.dropna(axis=0)
        dfWithinRaw = dfWithinRaw.append(dfCurrMonth,ignore_index=True)
    dfWithinRaw.index = range(len(dfWithinRaw))
    '''

    dfWithinX=dfWithinRaw.loc[:,Chosenfactors]
    #-- label data
    #-- factors as feature (X)
    #dfWithinX = dfWithinRaw.loc[:,'EP':'sh300']
    #-- excess return as target (y)
    srWithinY = dfWithinRaw.loc[:,'return']
    #-- initialize binary target
    srWithinYbin = -pd.Series(np.ones(len(srWithinY),dtype='int'))
    for iMonth in monthTrain:
        #-- select one-month-data
        indCurrMonth = dfWithinRaw[dfWithinRaw['month']==iMonth].index
        srCurrMonthY = srWithinY.iloc[indCurrMonth]
        srCurrMonthYcopy = srCurrMonthY.copy()
        #-- sort with excess return
        srCurrMonthYcopy = srCurrMonthYcopy.sort_values()
        #-- choose top and bottom stocks
        nSelectStock = int(np.round(percentBin*len(srCurrMonthY)))     
        indPos = srCurrMonthYcopy[-nSelectStock:].index
        indNeg = srCurrMonthYcopy[0:nSelectStock].index
        srWithinYbin[indPos] = 1
        srWithinYbin[indNeg] = 0
    #-- remove other samples
    srWithinYbin = srWithinYbin[(srWithinYbin>-1)]
    srWithinY = srWithinY[(srWithinYbin>-1).index]
    dfWithinX = dfWithinX.iloc[(srWithinYbin>-1).index,:]
                               
    data_in_sample = pd.concat([dfWithinX, srWithinY, srWithinYbin] , axis=1) 
    data_in_sample =  data_in_sample.sort_values(by='return',ascending=False)      

    #data_in_sample.to_csv(str(para.monthTestStart) + '_.csv')
    
    dfTrainX = dfWithinX
    srTrainY = srWithinY
    srTrainYbin = srWithinYbin
    
    #-- pca
    if isPCA==1:
        from sklearn import decomposition #-dedemension
        pca = decomposition.PCA(n_components=70)
        pca.fit(dfTrainX)
        dfTrainX = pca.transform(dfTrainX)
    
    
    #-- set model
    if method == 'XGBOOST-L':
        from xgboost import XGBClassifier
        from xgboost import plot_tree
        import matplotlib.pyplot as plt
        from graphviz import Digraph
        model = XGBClassifier(random_state=10, subsample = 0.95, max_depth=3)
        #model = XGBClassifier(random_state=10, booster='dart', subsample = 0.9, n_estimators = 400, learning_rate = 0.08)
        #eval_set = [(dfTrainX, srTrainYbin)]
        
        model.fit(dfTrainX, srTrainYbin)#, eval_metric="error", eval_set=eval_set)  
        #---------------draw the pircture of trees
       # plot_tree(model, num_trees= 2)
        #plt.show()
#        plot_tree(model,num_trees= 2).figure.set_size_inches(20, 20)#adjust the size of the picture

        
        fi = pd.DataFrame(data=model.feature_importances_).transpose()
        fi.columns = names
        fi.index = [para.monthTestStart - 1]
        global fi_all
        fi_all = fi_all.append(fi)
        print(fi_all)

        
    elif method == 'XGBOOST-C':
        from xgboost import XGBClassifier
        #model = XGBClassifier(random_state=10)
        #model = XGBClassifier(random_state=10, subsample = 0.95)
        #model = XGBClassifier(random_state=10, subsample = 0.95, reg_alpha = 0.8, reg_beta = 0.8)
        #model = XGBClassifier(subsample = 0.75, colsample_bylevel=0.9, colsample_bytree=0.6)
        #model = XGBClassifier(random_state=10, subsample = 0.95,min_child_weight=8)
        model = XGBClassifier(random_state=10, subsample = 0.95)
        
        #names = pd.read_csv('name.csv').columns
        #dfTrainX.columns = names
        #dfCVX.columns = names

        model.fit(dfTrainX, srTrainYbin)
        
    elif method == 'XGBOOST':
        import xgboost as xgb
        xgb_train = xgb.DMatrix(dfTrainX, label = srTrainYbin)    
        watchlist = [(xgb_train, 'train')] 
        param = {'subsample':0.95}
        model = xgb.train(param, xgb_train, 2000, watchlist, early_stopping_rounds = 50)
        
        
        score = model.get_score(fmap='', importance_type='cover')
        
        score = pd.DataFrame(score, index=[0])

        global score_all
        score_all = score_all.append(score)
        
    elif method == 'XGBOOST-R':
        from xgboost import XGBRegressor
        #model = XGBRegressor(random_state=10)
        model = XGBRegressor(random_state=10, subsample = 0.9)
        model.fit(dfTrainX, srTrainY)
        
        fi = pd.DataFrame(data=model.feature_importances_).transpose()
        fi.columns = names
        
       # global fi_all
        fi_all = fi_all.append(fi)
        
        
    #-- predict
    #-- fac_1: save all y_hat
    #fac_1 = pd.DataFrame(np.nan * np.zeros((nStock,monthTest[-1])))
    for iMonth in monthTest:
        #-- load 
        nameFile = para.dataPath + str(iMonth) + '.csv'
        print('Predict month ' + str(iMonth))
        dfTestRaw1 = pd.read_csv(nameFile)

        dfTestRaw=dfTestRaw1.loc[:,Chosenfactors]

        #-- insert one column as index 
        dfTestRaw.insert(len(dfTestRaw.columns),'indRow',pd.Series(range(len(dfTestRaw))))
        #-- remove nan  
        #dfTestRaw = dfTestRaw.dropna(axis=0)    
        srIsNaN = np.sum(np.isnan(np.transpose(dfTestRaw.loc[:,Chosenfactors])))         
        dfTestRaw = dfTestRaw.iloc[srIsNaN[srIsNaN==0].index,:] 
        

        dfTestRaw.index = range(len(dfTestRaw))
        #-- generate X and y
        
        #if para.monthTestStart == 226:
            #del dfTestRaw['ln_capital']
        
        dfTestX = dfTestRaw.loc[:,Chosenfactors]
        srTestY = dfTestRaw1.loc[:,'return']

        #dfTestX = rank(dfTestX)
        

        
        #-- pca
        if isPCA==1:
            dfTestX = pca.transform(dfTestX)#-return after PCA
        #-- predict and get decision function
        if method == 'XGBOOST-C'  or method == 'XGBOOST-L' :
            #dfTestX.columns = names
            arPredictedCScore_csv = model.predict_proba(dfTestX)[:,1]#RETURN the prob of classified to each
            arPredictedCScore = arPredictedCScore_csv-0.5
        elif method == 'XGBOOST-R':
            arPredictedCScore = model.predict(dfTestX)
            arPredictedCScore_csv = arPredictedCScore
        elif method  == 'XGBOOST':
            arPredictedCScore = model.predict( xgb.DMatrix(dfTestX) ) 
            arPredictedCScore_csv = arPredictedCScore
    
        #-- save
        dfPredictResults = pd.DataFrame(np.zeros((dfTestX.shape[0],3))) #- score returnHedge index             
        dfPredictResults.loc[:,0] = srTestY #-- y_true
        dfPredictResults.loc[:,1] = arPredictedCScore #-- y_hat
        dfPredictResults.loc[:,2] = dfTestRaw.iloc[:,-1] #-- row index
        #nameFileSave = resultPath + '\\predict_' + str(iMonth) + '.csv'
        #dfPredictResults.to_csv(nameFileSave,header=False,index=False) 
        #-- write fac_1
        fac_1.loc[dfTestRaw.iloc[:,-1],iMonth-1] = arPredictedCScore_csv
         



#-- main
#-- loop for 7 parts 
totalStock = 3541
totalMonth = 236
fac_1 = pd.DataFrame(np.nan * np.zeros((totalStock,totalMonth)))

d1 = datetime.datetime.now()

#monthTestStartList = range(225, totalMonth+1)
#monthTestStartList = [154,166,178,190,202,214,226]
monthTestStartList = [226]
for i in monthTestStartList:
    para = Para()
    para.monthTestStart = i
    para.monthTestEnd = i + 11
    #para.monthTestEnd = i
    if para.monthTestEnd > totalMonth:
        para.monthTestEnd = totalMonth
    go(para, fac_1)

d2 = datetime.datetime.now()

print((d2-d1).seconds)


 
fac_1.to_excel(para.resultPath + '\\fac_1_year.xls',header=False,index=False)
#fi_all.to_csv(para.resultPath + '\\fi_all.csv')
#score_all.to_csv(para.resultPath + '\\score_all.csv')

'''

for l in [2,3,6,9,12,24,48,72]:
    totalStock = 3541
    totalMonth = 236
    fac_1 = pd.DataFrame(np.nan * np.zeros((totalStock,totalMonth)))
    ic_all = []
    
    d1 = datetime.datetime.now()
    
    monthTestStartList = range(210, totalMonth+1)
    for i in monthTestStartList:
        para = Para()
        para.monthTestStart = i
        para.monthTestEnd = i
        para.previous_month = l
        if para.monthTestEnd > totalMonth:
            para.monthTestEnd = totalMonth
        go(para, fac_1, ic_all)
    
    d2 = datetime.datetime.now()
    
    print((d2-d1).seconds)
     
    fac_1.to_csv(para.resultPath + '\\XGBOOST_' + str(l) +'month.csv',header=False,index=False)
    ic_df = pd.DataFrame(ic_all)
    ic_df.to_csv(para.resultPath + str(l) +'month.csv',header=False,index=False)
'''

'''
for l in range(48, 74, 2):
    totalStock = 3506
    totalMonth = 235
    fac_1 = pd.DataFrame(np.nan * np.zeros((totalStock,totalMonth)))
    
    d1 = datetime.datetime.now()
    
    monthTestStartList = range(154, totalMonth+1)
    for i in monthTestStartList:
        para = Para()
        para.monthTestStart = i
        para.monthTestEnd = i
        para.previous_month = l
        if para.monthTestEnd > totalMonth:
            para.monthTestEnd = totalMonth
        go(para, fac_1)
    
    d2 = datetime.datetime.now()
    
    print((d2-d1).seconds)
     
    fac_1.to_csv(para.resultPath + '\\XGBOOST_' + str(l) +'month.csv',header=False,index=False)
'''
    
