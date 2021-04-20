%%*************************************************************************
% This file when called will setup the workspace for the projects
%{

            
%}
%%*************************************************************************

%% Load types/defines from hand code
if exist('EnumFileNames','var')
    run ReadEnums.m;   
else
    fprintf('No enum files defined. Define "EnumFileNames"\n');
end

%% Load WorkSpace
if exist(horzcat(ProjectName,'_params.m'),'file')
    try 
        run(horzcat(ProjectName,'_params.m'));
    catch
        fprintf(horzcat('Check case on params file.\n Does not match "',ProjectName,'_params.m"\n'));
    end
else
    fprintf(horzcat(ProjectName,'_params.m does not exist.\n'));
end

if exist(horzcat(ProjectName,'_bus.m'),'file')
    try 
        run(horzcat(ProjectName,'_bus.m'));
    catch
        fprintf(horzcat('Check case on bus file. Does not match "',ProjectName,'_bus.m"\n'));
    end
else
    fprintf(horzcat(ProjectName,'_bus.m does not exist.\n'));
end

