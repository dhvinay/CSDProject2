REM Save Caller's Path
SET localDir=%cd%
REM Change to file's directory
cd %~dp0

REM Clear files in Work dir
del /q "Work\*"
FOR /D %%p IN ("Work\*.*") DO rmdir "%%p" /s /q

REM Generate Code
matlab.exe -wait -r "build;quit"

REM Copy Src
call copySrc.bat

REM Copy Utilities
SET localUtilities=Work\slprj\ert\_sharedutils\*.h
SET destUtilities=..\..\..\..\Utilities\MBD
copy /Y %localUtilities% %destUtilities%

SET localUtilities=Work\slprj\ert\_sharedutils\*.c
copy /Y %localUtilities% %destUtilities%

REM Return to Directory
cd %localDir%
