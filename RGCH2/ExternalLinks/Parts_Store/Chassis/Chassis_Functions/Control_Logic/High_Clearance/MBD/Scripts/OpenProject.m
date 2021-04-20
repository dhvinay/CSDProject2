%% Project specific defines needed for shared files
ProjectName             = 'High_Clearance';
TopModuleModel_name     = 'HighClearance_model';
ConfigurationFile_name  = 'Config_C';
PathToCommonMbdFiles    = '..\..\..\..\..\MBD';
%PathToLibraryFiles      = '..\..\..\..\Libraries\AGCO\MBD';
EnumFileNames           = {'HighClearance_enum.h'};

%% Should not need to change below here

%Set path to shared files
cd('..\')
PathToCommonMbdFiles = genpath(PathToCommonMbdFiles);
path(PathToCommonMbdFiles,path);

%Run shared files
run SharedOpenProject.m


