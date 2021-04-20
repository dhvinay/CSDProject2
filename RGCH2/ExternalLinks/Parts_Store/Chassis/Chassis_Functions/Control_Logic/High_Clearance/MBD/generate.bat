REM Save Caller's Path
SET localDir=%cd%
REM Change to file's directory
cd %~dp0

REM Clear files in Work dir
del /q "Work\*"
FOR /D %%p IN ("Work\*.*") DO rmdir "%%p" /s /q

REM Build Model
matlab.exe -wait -r "build;quit"

REM Copy Files
call copySrc.bat

REM Commit Changes
svn commit Gen -m "[ID:][Type:CodeGen][Desc: Auto commit after code generation]

REM Return to Directory
cd %localDir%