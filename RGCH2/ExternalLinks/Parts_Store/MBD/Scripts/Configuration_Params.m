%%*************************************************************************
% This file when called will create the configuration base-workspace
%   variable for the model's referenced configuration.
%{
    Author: A. LeMay, adam.lemay@agcocorp.com
    Created: 11/15/13
    Notes: 
    ~ "configPath" will need to be updated/checked for each module
    ~ Model's 'Reference Configuration' will need to refernece "configRef"
    ~ "configRef" will need to be updated/checked for each module
    ~ There are four configurations avaliable (as of: 11/15/13)
        1) Config_C_10ms --> 10ms fixed step time
        2) Config_C_100ms --> 100ms fixed step time
        3) Config_CPP_10ms
        4) Config_CPP_100ms
    ~ All models within one module must referance the same configuration
            
%}
%%*************************************************************************

%% Add configuration referance variable to workspace

if exist('ConfigurationFile_name','var')
    tempfunc = str2func(ConfigurationFile_name);
    configRef = tempfunc(); 
    configPath = genpath(fileparts(which(ConfigurationFile_name)));
    path(configPath,path);    
else
    fprintf('No configuration file defined. Define "ConfigurationFile_name"\n');
end


clear ConfigurationFile_name tempfunc  

