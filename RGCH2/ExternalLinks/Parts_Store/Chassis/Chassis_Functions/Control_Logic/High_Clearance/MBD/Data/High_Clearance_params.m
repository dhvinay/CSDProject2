%% Danfoss_Interface_Params
% engine_speed_logic parameters
%
% Example of how to define parameters:
%{ 
EXAMPLE = Simulink.Parameter;
EXAMPLE.Value = 0;
EXAMPLE.DataType = 'single';
EXAMPLE.Min = [];
EXAMPLE.Max = [];
EXAMPLE.DocUnits = '';
EXAMPLE.CoderInfo.StorageClass= 'SimulinkGlobal';

EXAMPLE = Simulink.Signal;
EXAMPLE.DataType = 'single';
EXAMPLE.InitialValue = '0';
EXAMPLE.DocUnits = '';
EXAMPLE.Dimensions = 1;
EXAMPLE.Complexity = 'Real';
EXAMPLE.SamplingMode = 'Sample based';
EXAMPLE.CoderInfo.StorageClass = 'SimulinkGlobal';
EXAMPLE.CoderInfo.Alias = 'EXAMPLE';
%}
% 
%% *********************************************************************
%  *************************Model Properties****************************
%  *********************************************************************
step_time   = 0.01;                 %model sample time




%% *********************************************************************
%  *****************************Params**********************************
%  *********************************************************************
%General
plausiDistance = Simulink.Parameter;
plausiDistance.Value = 5;
plausiDistance.DataType = 'single';
plausiDistance.Min = [];
plausiDistance.Max = [];
plausiDistance.DocUnits = 'mm';
plausiDistance.CoderInfo.StorageClass= 'SimulinkGlobal';

errDelay = Simulink.Parameter;
errDelay.Value = 3;
errDelay.DataType = 'uint8';
errDelay.Min = [];
errDelay.Max = [];
errDelay.DocUnits = 'sec';
errDelay.CoderInfo.StorageClass= 'SimulinkGlobal';

calTolMultiplier = Simulink.Parameter;
calTolMultiplier.Value = 5;
calTolMultiplier.DataType = 'single';
calTolMultiplier.Min = [];
calTolMultiplier.Max = [];
calTolMultiplier.DocUnits = '';
calTolMultiplier.CoderInfo.StorageClass= 'SimulinkGlobal';

useSensorFilter = Simulink.Parameter;
useSensorFilter.Value = 0;
useSensorFilter.DataType = 'boolean';
useSensorFilter.Min = [];
useSensorFilter.Max = [];
useSensorFilter.DocUnits = '';
useSensorFilter.CoderInfo.StorageClass= 'SimulinkGlobal';

sensorCutOffHz = Simulink.Parameter;
sensorCutOffHz.Value = (3/15)/(2*pi()); %0.032
sensorCutOffHz.DataType = 'single';
sensorCutOffHz.Min = [];
sensorCutOffHz.Max = [];
sensorCutOffHz.DocUnits = 'hz';
sensorCutOffHz.CoderInfo.StorageClass= 'SimulinkGlobal';

IOD_OK = Simulink.Parameter;
IOD_OK.Value = 0;
IOD_OK.DataType = 'uint8';
IOD_OK.Min = [];
IOD_OK.Max = [];
IOD_OK.DocUnits = '';
IOD_OK.CoderInfo.StorageClass= 'SimulinkGlobal';

IOD_Open = Simulink.Parameter;
IOD_Open.Value = 1;
IOD_Open.DataType = 'uint8';
IOD_Open.Min = [];
IOD_Open.Max = [];
IOD_Open.DocUnits = '';
IOD_Open.CoderInfo.StorageClass= 'SimulinkGlobal';

IOD_ScGnd = Simulink.Parameter;
IOD_ScGnd.Value = 2;
IOD_ScGnd.DataType = 'uint8';
IOD_ScGnd.Min = [];
IOD_ScGnd.Max = [];
IOD_ScGnd.DocUnits = '';
IOD_ScGnd.CoderInfo.StorageClass= 'SimulinkGlobal';

IOD_ScHigh = Simulink.Parameter;
IOD_ScHigh.Value = 3;
IOD_ScHigh.DataType = 'uint8';
IOD_ScHigh.Min = [];
IOD_ScHigh.Max = [];
IOD_ScHigh.DocUnits = '';
IOD_ScHigh.CoderInfo.StorageClass= 'SimulinkGlobal';

baseClearance = Simulink.Parameter;
baseClearance.Value = 1270;
baseClearance.DataType = 'single';
baseClearance.Min = [];
baseClearance.Max = [];
baseClearance.DocUnits = 'mm';
baseClearance.CoderInfo.StorageClass= 'SimulinkGlobal';

calSettlingTime = Simulink.Parameter;
calSettlingTime.Value = 4000;
calSettlingTime.DataType = 'uint16';
calSettlingTime.Min = [];
calSettlingTime.Max = [];
calSettlingTime.DocUnits = 'msec';
calSettlingTime.CoderInfo.StorageClass= 'SimulinkGlobal';

calStepTimeOut = Simulink.Parameter;
calStepTimeOut.Value = 120;
calStepTimeOut.DataType = 'uint16';
calStepTimeOut.Min = [];
calStepTimeOut.Max = [];
calStepTimeOut.DocUnits = 'sec';
calStepTimeOut.CoderInfo.StorageClass= 'SimulinkGlobal';

calOKAY_e.DataType = 'uint16';
calSTART_e.DataType = 'uint16';
calSTEP1_e.DataType = 'uint16';
calSTEP2_e.DataType = 'uint16';
calCONFIRM2_e.DataType = 'uint16';
calSTEP3_e.DataType = 'uint16';
calSTEP4_e.DataType = 'uint16';
calCONFIRM4_e.DataType = 'uint16';
calABORT_e.DataType = 'uint16';
calDECLINE_e.DataType = 'uint16';
calERROR0_e.DataType = 'uint16';
calERROR1_e.DataType = 'uint16';
calERROR2_e.DataType = 'uint16';
calERROR3_e.DataType = 'uint16';
calERROR4_e.DataType = 'uint16';
calBAD_e.DataType = 'uint16';

calSensorTolerance = Simulink.Parameter;
calSensorTolerance.Value = 0.5;
calSensorTolerance.DataType = 'single';
calSensorTolerance.Min = [];
calSensorTolerance.Max = [];
calSensorTolerance.DocUnits = 'mA';
calSensorTolerance.CoderInfo.StorageClass= 'SimulinkGlobal';

positionSensor_tblData = Simulink.Parameter;
positionSensor_tblData.Value = [0 500];
positionSensor_tblData.DataType = 'single';
positionSensor_tblData.Min = [];
positionSensor_tblData.Max = [];
positionSensor_tblData.DocUnits = 'mm';
positionSensor_tblData.CoderInfo.StorageClass= 'SimulinkGlobal';

positionSensorFL_BrkPnts = Simulink.Parameter;
positionSensorFL_BrkPnts.Value = [4 20];
positionSensorFL_BrkPnts.DataType = 'single';
positionSensorFL_BrkPnts.Min = [];
positionSensorFL_BrkPnts.Max = [];
positionSensorFL_BrkPnts.DocUnits = 'mA';
positionSensorFL_BrkPnts.CoderInfo.StorageClass= 'SimulinkGlobal';

positionSensorFR_BrkPnts = Simulink.Parameter;
positionSensorFR_BrkPnts.Value = [4 20];
positionSensorFR_BrkPnts.DataType = 'single';
positionSensorFR_BrkPnts.Min = [];
positionSensorFR_BrkPnts.Max = [];
positionSensorFR_BrkPnts.DocUnits = 'mA';
positionSensorFR_BrkPnts.CoderInfo.StorageClass= 'SimulinkGlobal';

positionSensorRL_BrkPnts = Simulink.Parameter;
positionSensorRL_BrkPnts.Value = [4 20];
positionSensorRL_BrkPnts.DataType = 'single';
positionSensorRL_BrkPnts.Min = [];
positionSensorRL_BrkPnts.Max = [];
positionSensorRL_BrkPnts.DocUnits = 'mA';
positionSensorRL_BrkPnts.CoderInfo.StorageClass= 'SimulinkGlobal';

positionSensorRR_BrkPnts = Simulink.Parameter;
positionSensorRR_BrkPnts.Value = [4 20];
positionSensorRR_BrkPnts.DataType = 'single';
positionSensorRR_BrkPnts.Min = [];
positionSensorRR_BrkPnts.Max = [];
positionSensorRR_BrkPnts.DocUnits = 'mA';
positionSensorRR_BrkPnts.CoderInfo.StorageClass= 'SimulinkGlobal';

defaultPositionSensor_BrkPnts = Simulink.Parameter;
defaultPositionSensor_BrkPnts.Value = [4 20];
defaultPositionSensor_BrkPnts.DataType = 'single';
defaultPositionSensor_BrkPnts.Min = [];
defaultPositionSensor_BrkPnts.Max = [];
defaultPositionSensor_BrkPnts.DocUnits = 'mA';
defaultPositionSensor_BrkPnts.CoderInfo.StorageClass= 'SimulinkGlobal';

%Arbitration
heightTolerance = Simulink.Parameter;
heightTolerance.Value = 2;
heightTolerance.DataType = 'single';
heightTolerance.Min = [];
heightTolerance.Max = [];
heightTolerance.DocUnits = '';
heightTolerance.CoderInfo.StorageClass= 'SimulinkGlobal';

heightToleranceRoad = Simulink.Parameter;
heightToleranceRoad.Value = 4;
heightToleranceRoad.DataType = 'single';
heightToleranceRoad.Min = [];
heightToleranceRoad.Max = [];
heightToleranceRoad.DocUnits = '';
heightToleranceRoad.CoderInfo.StorageClass= 'SimulinkGlobal';

errorMinSpd = Simulink.Parameter;
errorMinSpd.Value = 1.6;
errorMinSpd.DataType = 'single';
errorMinSpd.Min = [];
errorMinSpd.Max = [];
errorMinSpd.DocUnits = 'kph';
errorMinSpd.CoderInfo.StorageClass= 'SimulinkGlobal';

trackWidthMax = Simulink.Parameter;
trackWidthMax.Value = 3657.6;
trackWidthMax.DataType = 'single';
trackWidthMax.Min = [];
trackWidthMax.Max = []; 
trackWidthMax.DocUnits = 'mm';
trackWidthMax.CoderInfo.StorageClass= 'SimulinkGlobal';

trackWidthMin = Simulink.Parameter;
trackWidthMin.Value = 3048;
trackWidthMin.DataType = 'single';
trackWidthMin.Min = [];
trackWidthMin.Max = [];
trackWidthMin.DocUnits = 'mm';
trackWidthMin.CoderInfo.StorageClass= 'SimulinkGlobal';

twoWheelSteer = Simulink.Parameter;
twoWheelSteer.Value = 2;
twoWheelSteer.DataType = 'uint8';
twoWheelSteer.Min = [];
twoWheelSteer.Max = [];
twoWheelSteer.DocUnits = 'enum';
twoWheelSteer.CoderInfo.StorageClass= 'SimulinkGlobal';

maxMedianWheelAngle = Simulink.Parameter;
maxMedianWheelAngle.Value = 10;
maxMedianWheelAngle.DataType = 'single';
maxMedianWheelAngle.Min = [];
maxMedianWheelAngle.Max = [];
maxMedianWheelAngle.DocUnits = 'deg';
maxMedianWheelAngle.CoderInfo.StorageClass= 'SimulinkGlobal';

maxTransitionMachineSpd = Simulink.Parameter;
maxTransitionMachineSpd.Value = 8;
maxTransitionMachineSpd.DataType = 'single';
maxTransitionMachineSpd.Min = [];
maxTransitionMachineSpd.Max = [];
maxTransitionMachineSpd.DocUnits = 'kph';
maxTransitionMachineSpd.CoderInfo.StorageClass= 'SimulinkGlobal';

minTransitionMachineSpd = Simulink.Parameter;
minTransitionMachineSpd.Value = 0.0;
minTransitionMachineSpd.DataType = 'single';
minTransitionMachineSpd.Min = [];
minTransitionMachineSpd.Max = [];
minTransitionMachineSpd.DocUnits = 'kph';
minTransitionMachineSpd.CoderInfo.StorageClass= 'SimulinkGlobal';

legMovingTimeout = Simulink.Parameter;
legMovingTimeout.Value = 1000;
legMovingTimeout.DataType = 'uint16';
legMovingTimeout.Min = [];
legMovingTimeout.Max = [];
legMovingTimeout.DocUnits = 'msec';
legMovingTimeout.CoderInfo.StorageClass= 'SimulinkGlobal';

minDistanceMoving = Simulink.Parameter;
minDistanceMoving.Value = 1;
minDistanceMoving.DataType = 'single';
minDistanceMoving.Min = [];
minDistanceMoving.Max = [];
minDistanceMoving.DocUnits = 'mm';
minDistanceMoving.CoderInfo.StorageClass= 'SimulinkGlobal';

%Control
heightControlToleranceStart = Simulink.Parameter;
heightControlToleranceStart.Value = 2;
heightControlToleranceStart.DataType = 'single';
heightControlToleranceStart.Min = [];
heightControlToleranceStart.Max = [];
heightControlToleranceStart.DocUnits = 'mm';
heightControlToleranceStart.CoderInfo.StorageClass= 'SimulinkGlobal';

heightControlToleranceStop = Simulink.Parameter;
heightControlToleranceStop.Value = 1;
heightControlToleranceStop.DataType = 'single';
heightControlToleranceStop.Min = [];
heightControlToleranceStop.Max = [];
heightControlToleranceStop.DocUnits = 'mm';
heightControlToleranceStop.CoderInfo.StorageClass= 'SimulinkGlobal';

ctrlWarningTime = Simulink.Parameter;
ctrlWarningTime.Value = 5;
ctrlWarningTime.DataType = 'single';
ctrlWarningTime.Min = [];
ctrlWarningTime.Max = [];
ctrlWarningTime.DocUnits = 'sec';
ctrlWarningTime.CoderInfo.StorageClass= 'SimulinkGlobal';

noMovementTimeOut = Simulink.Parameter;
noMovementTimeOut.Value = 250;
noMovementTimeOut.DataType = 'single';
noMovementTimeOut.Min = [];
noMovementTimeOut.Max = [];
noMovementTimeOut.DocUnits = 'msec';
noMovementTimeOut.CoderInfo.StorageClass= 'SimulinkGlobal';

movementTimeOut = Simulink.Parameter;
movementTimeOut.Value = 100;
movementTimeOut.DataType = 'single';
movementTimeOut.Min = [];
movementTimeOut.Max = [];
movementTimeOut.DocUnits = 'msec';
movementTimeOut.CoderInfo.StorageClass= 'SimulinkGlobal';

heightDiffTolerance = Simulink.Parameter;
heightDiffTolerance.Value = 26;
heightDiffTolerance.DataType = 'single';
heightDiffTolerance.Min = [];
heightDiffTolerance.Max = [];
heightDiffTolerance.DocUnits = 'mm';
heightDiffTolerance.CoderInfo.StorageClass= 'SimulinkGlobal';

trackWidthTolerance = Simulink.Parameter;
trackWidthTolerance.Value = 6;
trackWidthTolerance.DataType = 'single';
trackWidthTolerance.Min = [];
trackWidthTolerance.Max = [];
trackWidthTolerance.DocUnits = 'mm';
trackWidthTolerance.CoderInfo.StorageClass= 'SimulinkGlobal';

%Bang Bang Controller
bangBang_maxOut = Simulink.Parameter;
bangBang_maxOut.Value = 100;
bangBang_maxOut.DataType = 'single';
bangBang_maxOut.Min = [];
bangBang_maxOut.Max = [];
bangBang_maxOut.DocUnits = '%';
bangBang_maxOut.CoderInfo.StorageClass= 'SimulinkGlobal';


%{
bangBang_Active = Simulink.Parameter;
bangBang_Active.Value = 0;
bangBang_Active.DataType = 'uint8';
bangBang_Active.Min = [];
bangBang_Active.Max = [];
bangBang_Active.DocUnits = 'logic';
bangBang_Active.CoderInfo.StorageClass= 'SimulinkGlobal';

% %Position Controller
% positionControl_Kp = Simulink.Parameter;
% positionControl_Kp.Value = 700;
% positionControl_Kp.DataType = 'single';
% positionControl_Kp.Min = [];
% positionControl_Kp.Max = [];
% positionControl_Kp.DocUnits = '';
% positionControl_Kp.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% positionControl_Ki = Simulink.Parameter;
% positionControl_Ki.Value = 500;
% positionControl_Ki.DataType = 'single';
% positionControl_Ki.Min = [];
% positionControl_Ki.Max = [];
% positionControl_Ki.DocUnits = '';
% positionControl_Ki.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% positionControl_maxOut = Simulink.Parameter;
% positionControl_maxOut.Value = 2000;
% positionControl_maxOut.DataType = 'single';
% positionControl_maxOut.Min = [];
% positionControl_maxOut.Max = [];
% positionControl_maxOut.DocUnits = 'mA';
% positionControl_maxOut.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% positionControl_minOut = Simulink.Parameter;
% positionControl_minOut.Value = -2000;
% positionControl_minOut.DataType = 'single';
% positionControl_minOut.Min = [];
% positionControl_minOut.Max = [];
% positionControl_minOut.DocUnits = 'mA';
% positionControl_minOut.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% positionControl_IC = Simulink.Parameter;
% positionControl_IC.Value = 0;
% positionControl_IC.DataType = 'single';
% positionControl_IC.Min = [];
% positionControl_IC.Max = [];
% positionControl_IC.DocUnits = 'mA';
% positionControl_IC.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% %Current Controller
% currentControl_Kp = Simulink.Parameter;
% currentControl_Kp.Value = 0.01;
% currentControl_Kp.DataType = 'single';
% currentControl_Kp.Min = [];
% currentControl_Kp.Max = [];
% currentControl_Kp.DocUnits = '';
% currentControl_Kp.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% currentControl_Ki = Simulink.Parameter;
% currentControl_Ki.Value = 0.8;
% currentControl_Ki.DataType = 'single';
% currentControl_Ki.Min = [];
% currentControl_Ki.Max = [];
% currentControl_Ki.DocUnits = '';
% currentControl_Ki.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% currentControl_maxOut = Simulink.Parameter;
% currentControl_maxOut.Value = 100;
% currentControl_maxOut.DataType = 'single';
% currentControl_maxOut.Min = [];
% currentControl_maxOut.Max = [];
% currentControl_maxOut.DocUnits = '%';
% currentControl_maxOut.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% currentControl_minOut = Simulink.Parameter;
% currentControl_minOut.Value = 0;
% currentControl_minOut.DataType = 'single';
% currentControl_minOut.Min = [];
% currentControl_minOut.Max = [];
% currentControl_minOut.DocUnits = '%';
% currentControl_minOut.CoderInfo.StorageClass= 'SimulinkGlobal';
% 
% currentControl_IC = Simulink.Parameter;
% currentControl_IC.Value = 0;
% currentControl_IC.DataType = 'single';
% currentControl_IC.Min = [];
% currentControl_IC.Max = [];
% currentControl_IC.DocUnits = '%';
% currentControl_IC.CoderInfo.StorageClass= 'SimulinkGlobal';
%}



