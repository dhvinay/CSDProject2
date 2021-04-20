%% Script to generate code for modules.
% When the build is done the script copies the generated files to the correct folders
% for compile.
%
% ***Need to update script to match Model names*** 
%
% Once this is run you should make sure to commit the source!  
%   - dont forget to commit the shared utilities!
%
% Don't forget to update the make file for any new files!
%
%Creator: Nick Edwards
%Edited: Adam LeMay, 11/27/2013

%% 
slproject.loadProject('High_Clearance.prj');
Simulink.fileGenControl('reset');
cd('../Work');

diary('Output.txt')

if exist('customeSFuncGeneration','file')
    run('customeSFuncGeneration.m'); %Generates sfunctions if they don't exist
end
rtwbuild('HighClearance_model') %Initiates build



%% cleanup
delete('*.mexw64')

diary('Off')

quit force
