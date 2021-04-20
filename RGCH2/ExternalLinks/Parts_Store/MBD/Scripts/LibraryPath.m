%% Library Path
%   This file adds the path to the project defined Library folder
%
%
%
%%

% Changes directory
cd(projectPath);
% Setup
libraryError  = 0;
clear libraryPath
% Change directory to library
if exist('PathToLibraryFiles','var')
    try
        cd(PathToLibraryFiles);
    catch
        fprintf('Library path not correct.\n');
        libraryError = 1;
    end
    if libraryError == 0
        %Add library to path
        libraryPath = genpath(pwd);
        path(genpath(pwd),path);
        % Change directory back
        cd(projectPath) 
    end
else
    fprintf('No library path defined. Define "PathToLibraryFiles"\n');
end

%% Clean Up
clear  TopModuleModel_name libraryError