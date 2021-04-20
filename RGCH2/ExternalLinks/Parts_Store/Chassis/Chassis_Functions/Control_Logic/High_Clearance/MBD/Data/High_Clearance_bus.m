%% Danfoss_Interface_Bus

%  Example for Creating Buses:
%{
%EXAMPLE START

%% Bus object: EXAMPLE
size_bus = 4; %Number of bus elements
%Define individual bus elements 
names_bus = {'FrontLeft','FrontRight','RearLeft','RearRight'};
dataType_bus = {'single','single','single','single'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
EXAMPLE = Simulink.Bus;
EXAMPLE.HeaderFile = '';
EXAMPLE.Description = '';
EXAMPLE.DataScope = 'Auto';
EXAMPLE.Alignment = -1;
EXAMPLE.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%EXAMPLE END
%}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% *********************************************************************
%  ************************Buses****************************************
%  *********************************************************************
% Bus object: CylinderBus
size_bus = 4; %Number of bus elements
%Define individual bus elements 
names_bus = {'FrontLeft','FrontRight','RearLeft','RearRight'};
dataType_bus = {'single','single','single','single'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
CylinderBus = Simulink.Bus;
CylinderBus.HeaderFile = '';
CylinderBus.Description = '';
CylinderBus.DataScope = 'Auto';
CylinderBus.Alignment = -1;
CylinderBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: CoilBus
size_bus = 2; %Number of bus elements
%Define individual bus elements 
names_bus = {'extend','retract'};
dataType_bus = {'CylinderBus','CylinderBus'};
docUnits_bus = {'',''};
description_bus = {'',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
CoilBus = Simulink.Bus;
CoilBus.HeaderFile = '';
CoilBus.Description = '';
CoilBus.DataScope = 'Auto';
CoilBus.Alignment = -1;
CoilBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: UserWarningBus
size_bus = 8; %Number of bus elements
%Define individual bus elements 
names_bus = {'trackWidth','speed','guide','was','fws','fieldRoad','cal','parkBrake'};
dataType_bus = {'boolean','boolean','boolean','boolean','boolean','boolean','boolean','boolean'};
docUnits_bus = {'','','','','','','',''};
description_bus = {'','','','','','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
UserWarningBus = Simulink.Bus;
UserWarningBus.HeaderFile = '';
UserWarningBus.Description = '';
UserWarningBus.DataScope = 'Auto';
UserWarningBus.Alignment = -1;
UserWarningBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: ErrorBus
size_bus = 3; %Number of bus elements
%Define individual bus elements 
names_bus = {'movementErr1','movementErr2','noMovementErr'};
dataType_bus = {'boolean','boolean','boolean'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
ErrorBus = Simulink.Bus;
ErrorBus.HeaderFile = '';
ErrorBus.Description = '';
ErrorBus.DataScope = 'Auto';
ErrorBus.Alignment = -1;
ErrorBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: ErrorsBus
size_bus = 4; %Number of bus elements
%Define individual bus elements 
names_bus = {'FrontLeft','FrontRight','RearLeft','RearRight'};
dataType_bus = {'ErrorBus','ErrorBus','ErrorBus','ErrorBus'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
ErrorsBus = Simulink.Bus;
ErrorsBus.HeaderFile = '';
ErrorsBus.Description = '';
ErrorsBus.DataScope = 'Auto';
ErrorsBus.Alignment = -1;
ErrorsBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: MfaBus
size_bus = 5; %Number of bus elements
%Define individual bus elements 
names_bus = {'upBtn','downBtn','stopBtn','isAlive','downDiag'};
dataType_bus = {'uint8','uint8','uint8','uint8','uint8'};
docUnits_bus = {'','','','','',''};
description_bus = {'','','','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
MfaBus = Simulink.Bus;
MfaBus.HeaderFile = '';
MfaBus.Description = '';
MfaBus.DataScope = 'Auto';
MfaBus.Alignment = -1;
MfaBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: StateBus
size_bus = 4; %Number of bus elements
%Define individual bus elements 
names_bus = {'FrontLeft','FrontRight','RearLeft','RearRight'};
dataType_bus = {'uint8','uint8','uint8','uint8'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
StateBus = Simulink.Bus;
StateBus.HeaderFile = '';
StateBus.Description = '';
StateBus.DataScope = 'Auto';
StateBus.Alignment = -1;
StateBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus

%% Bus object: CoilStateBus
size_bus = 2; %Number of bus elements
%Define individual bus elements 
names_bus = {'extend','retract'};
dataType_bus = {'StateBus','StateBus'};
docUnits_bus = {'',''};
description_bus = {'',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
CoilStateBus = Simulink.Bus;
CoilStateBus.HeaderFile = '';
CoilStateBus.Description = '';
CoilStateBus.DataScope = 'Auto';
CoilStateBus.Alignment = -1;
CoilStateBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus
%% Bus object: ControlWarningsBus
size_bus = 2; %Number of bus elements
%Define individual bus elements 
names_bus = {'track','height'};
dataType_bus = {'StateBus','StateBus','single','single'};
docUnits_bus = {'','','',''};
description_bus = {'','','',''};
%Creat individual bus elements
clear elems
for i_bus = 1:size_bus
elems(i_bus) = Simulink.BusElement;
elems(i_bus).Name = char(names_bus(i_bus));
elems(i_bus).Dimensions = 1;
elems(i_bus).DimensionsMode = 'Fixed';
elems(i_bus).DataType = char(dataType_bus(i_bus));
elems(i_bus).SampleTime = -1;
elems(i_bus).Complexity = 'real';
elems(i_bus).SamplingMode = 'Sample based';
elems(i_bus).Min = [];
elems(i_bus).Max = [];
elems(i_bus).DocUnits = char(docUnits_bus(i_bus));
elems(i_bus).Description = char(description_bus(i_bus));   
end
%Create bus
ControlWarningsBus = Simulink.Bus;
ControlWarningsBus.HeaderFile = '';
ControlWarningsBus.Description = '';
ControlWarningsBus.DataScope = 'Auto';
ControlWarningsBus.Alignment = -1;
ControlWarningsBus.Elements = elems;
% clean up
clear elems i_bus size_bus names_bus dataType_bus docUnits_bus...
    description_bus


