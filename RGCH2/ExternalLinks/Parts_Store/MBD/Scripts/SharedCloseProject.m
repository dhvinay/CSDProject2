%% Path Clean Up
%open script adds these
Simulink.fileGenControl('reset');

if exist('projectPath','var')
    rmpath(strcat(projectPath,'\Scripts'));
    rmpath(strcat(projectPath,'\Data'));
    rmpath(strcat(projectPath,'\Models'));
else
    fprintf('Project path does not exist.\n');
end

if exist('libraryPath','var')
    rmpath(libraryPath);
else
    fprintf('Library path does not exist.\n');
end

if exist('configPath','var')
    rmpath(configPath);
else
    fprintf('Configuration path does not exist.\n');
end

if exist('commonScriptsPath','var')
    rmpath(commonScriptsPath);
else
    fprintf('Path to common scripts does not exist.\n');
end

if exist(projectPath,'var')
    cd(projectPath)
end

%% Workspace Clean Up
close all
clear projectPath libraryPath configPath
