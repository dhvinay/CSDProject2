if exist('ProjectName','var')
%% Add local paths    
    projectPath = fileparts(which(horzcat(ProjectName,'.prj')));
    addpath(strcat(projectPath,'\Scripts'));
    addpath(strcat(projectPath,'\Data'));
    addpath(strcat(projectPath,'\Models'));
    Simulink.fileGenControl('set','CacheFolder',strcat(projectPath,'\Work'));
    
    %Add path to project Simulink_Test folder
    addpath(genpath(strcat(projectPath,'\Simulink_Test')));
    
    %Runs file to add MBD libraries to simulink browser
    run slblocks.m;

%% Load Model files
    try 
        run Configuration_Params.m
    catch
         fprintf('Could not find/run "Configuration_Params.m"\n');
    end
    try 
        run WorkspaceSetup.m
    catch
         fprintf('Could not find/run "WorkspaceSetup.m"\n');
    end
    try 
        run LibraryPath.m
    catch
         fprintf('Could not find/run "LibraryPath.m"\n');
    end
%% Get Absolute path to scripts 
    commonScriptsPath = genpath(fileparts(which('SharedOpenProject.m')));
    if( strcmp(version('-release'),'2014b') )
        path(commonScriptsPath,path);
    end
    
%% Clean Up
    if( strcmp(version('-release'),'2014b') )
        rmpath(PathToCommonMbdFiles);
    end
    clear  PathToCommonMbdFiles ProjectName PathToLibraryFiles TopModuleModel_name...
         ParamsName
         
%% Change Directory to models
    cd(strcat(projectPath,'\Models'));
else
    fprintf('No project name defined. Define "ProjectName"\n');
end