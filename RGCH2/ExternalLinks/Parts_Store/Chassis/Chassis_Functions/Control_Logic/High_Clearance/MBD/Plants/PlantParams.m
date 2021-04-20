clc
%% Simulation Params
runTime = 30; % sec
Vs = 12; %volts
fs = 100; %Hz
ts = 1/fs; %sec
dc = 90; % pct

Wc = 10; %Hz
Wt = 1/Wc; %sec
a = 3/Wt;

%% Physical Params
amp2mAmp = 1000; %gain

coilR = 6; %ohms
coilL = 0.125; %Henrys

coilMaxI = 0.9*amp2mAmp*Vs/coilR; %mAmps
coilMinI = 0.2*amp2mAmp*Vs/coilR; %mAmps

maxFlowRate = 16; %mm/sec
maxFlowRate = maxFlowRate*1;

strokeLegnth = 500; %mm
extendTime = 20; %sec
retractTime = 15; %sec
extendRateFL = strokeLegnth/extendTime; %mm/sec
retractRateFL = strokeLegnth/retractTime; %mm/sec

extendTime = 10; %sec
retractTime = 22; %sec
extendRateFR = strokeLegnth/extendTime; %mm/sec
retractRateFR = strokeLegnth/retractTime; %mm/sec

extendTime = 22; %sec
retractTime = 18; %sec
extendRateRL = strokeLegnth/extendTime; %mm/sec
retractRateRL = strokeLegnth/retractTime; %mm/sec

extendTime = 17; %sec
retractTime = 20; %sec
extendRateRR = strokeLegnth/extendTime; %mm/sec
retractRateRR = strokeLegnth/retractTime; %mm/sec

reducer_ex = 0.01;%0.22;
reducer_rt = 0.01;%0.28;

dampeningFL = 20; %Hz
dampeningFL = 1/dampeningFL; %sec
dampeningFL = 3/dampeningFL;

dampeningFR = 20; %Hz
dampeningFR = 1/dampeningFR; %sec
dampeningFR = 3/dampeningFR;

dampeningRL = 20; %Hz
dampeningRL = 1/dampeningRL; %sec
dampeningRL = 3/dampeningRL;

dampeningRR = 20; %Hz
dampeningRR = 1/dampeningRR; %sec
dampeningRR = 3/dampeningRR;

dampening = 20; %Hz
dampening = 1/dampening; %sec
dampening = 3/dampening;

% dampening = 20; %Hz
% dampening = 1/dampening; %sec
% dampening = 3/dampening;

positionSensorFL_BrkPnts.Value = [4.49 19.59];
positionSensorFR_BrkPnts.Value = [4.1 19.75];
positionSensorRL_BrkPnts.Value = [4.25 19.9];
positionSensorRR_BrkPnts.Value = [4.001 19.999];

legMovingTimeout.Value = 20; %1000;
movementTimeOut.Value = 500; %100;

%% Simulate
%load('PlantConfig.mat');
sim HighClearancePlant;
%sim trackAdjustPlant.slx
%sim cylinderPlant.slx
