%BL-Model
clear all;
ExpReturn=[.02,.08,.09,.15];%预期收益率
NumPorts=10;
Z=.001*[0.7676,0.1907,-0.1723,-0.0707
        0.1907,0.6483,0.2717,0.1093
        -0.1723,0.2717,0.4841,-0.1342
        -0.0707,0.1093,-0.1342,0.8610];%n种资产超额收益的协方差矩阵Σ
% [PortRisk,PortReturn,PortWts]=frontcon(ExpReturn,Z,NumPorts);
% Sharpe=PortReturn./PortRisk;
% [~,id]=max(Sharpe);
%w_eq=PortWts(id,:)';市场均衡下的配置权重  
y=.5;%平均风险厌恶系数；y=δ=(E(r)-rf)/σ^2
w_mkt=[.1,.2,.3,.4]';%市场资产权重起点配置
P=[1,0,-1,0;
   0,1, 0,0];%观点矩阵m×n;m种观点n种资产
Q=[2,3]';%观点收益率矩阵

t=0.05;%主观观点占比
O=diag(diag(P*(t*Z)*P'));%观点的相关矩阵Ω,反映观点误差
TT=y*Z*w_mkt;%均衡超额回报矩阵;隐含均衡收益率向量
A=O./t+P*(Z./(1+t))*P';
V=1/y*t*(inv(O))*Q-(inv(A))*P*(Z./(1+t))*w_mkt-(inv(A))*P*(Z./(1+t))*(1/y)*P'*t*(inv(O))*Q;
w=1/(1+t)*(w_mkt+P'*V);%最优权重组合
E_R=inv(inv(t*Z)+P'*(inv(O))*P)*((inv(t*Z))*TT+P'*(inv(O))*Q);%最优组合收益
