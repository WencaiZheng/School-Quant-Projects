setwd("C:/Users/Administrator/Desktop")
rm(list=ls())

#packages
library(tseries)
library(lmtest)
library(forecast)

## load data
data = read.table('VIX.csv',header = T,sep=",")
datav = ts(data)[1:252,1] # the data from 1/2/2014 to 12/31/2014

## choose a trend
TIME = c(1:252)
TIME2 = TIME*TIME
TIME3=TIME2*TIME
result1 =lm(datav ~ TIME)
result2 =lm(datav ~ TIME + TIME2)
result3=lm(datav~TIME+TIME2+TIME3)
result4=lm(datav~log(TIME))
summary(result1)
summary(result2)
summary(result3)
summary(result4)
AIC(result1)
AIC(result2)
AIC(result3)
AIC(result4)

## detrend
datav.detrend = result2$residuals

##plot
ma<-max(datav)
mi<-min(datav)
plot(datav,type='l',axes=F,ylim=c(-0.4*ma,ma),xlab="",ylab="",main="",col="red")
box()
par(new=T)
plot(result2$fitted.values,type="l",axes=F,ylim=c(-0.4*ma,ma),xlab="",ylab="",main="",col="green")
par(new=T)
plot(datav.detrend,type="l",axes=F,ylim=c(-0.4*ma,ma),xlab="",ylab="",main="",col="blue")
n=ceiling((ma-mi)/10)
axis(side=2,at=c(seq(mi,ma,by=n)),lab=c(seq(mi,ma,by=n)),cex.axis=0.8)
axis(side=4,at=c(seq(-3*mi,2*mi,by=mi)),lab=c(seq(-3*mi,2*mi,by=mi)),cex.axis=0.8)
abline(h=0,col="black")

## fit with arma
vix.ar1=arma(datav.detrend,order=c(1,0))
vix.ma1=arma(datav.detrend,order=c(0,1))
vix.arma11=arma(datav.detrend,order=c(1,1))

##choose a model 
summary(vix.ar1)$aic
summary(vix.ma1)$aic
summary(vix.arma11)$aic

##forecast
time=c(253:299)
time2=time*time
#ar1
vix.ar1=Arima(datav.detrend,order=c(1,0,0))
fcst=forecast.Arima(vix.ar1,h=47)
#trend
trend=matrix(NA,47,1)
for(i in 1:47)
{
  trend[i]=result2$coef[1]+result2$coef[2]*time[i]+result2$coef[3]*time2[i]
}
#with trend and arimafcst
fcstdata=fcst$mean[1:47]+trend
#with white noise
whitenoise=rnorm(47,mean=0,sd=sd(datav.detrend))
fcstdata1=fcst$mean[1:47]+trend+whitenoise
#one replacement
fcst2=rep(vix.ar1$coef[2],47)+vix.ar1$coef[1]*data[252:298,1]
fcstdata2=trend+fcst2
#plot the lines of real and fsct
datav2=ts(data)[253:299,1]
plot(datav2,type="l",xlab="time",xlim=c(1,47),col="red")
par(new=T)
plot(fcstdata,type="l",axes=F,xlab="",ylab="",main='Forecast',xlim=c(1,47),col="green")
par(new=T)
plot(fcstdata1,type="l",axes=F,xlab="",ylab="",main='Forecast',xlim=c(1,47),col="blue")
par(new=T)
plot(fcstdata2,type="l",axes=F,xlab="",ylab="",main='Forecast',xlim=c(1,47),col="black")
box()
legend(x='topright',y=null,c("Actual","Forecast","Forecast1","Forecast2"),lty=c(1,1),col=c("red","green","blue","black"),cex=0.3)