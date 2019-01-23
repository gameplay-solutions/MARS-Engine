@echo off
color a
cls

title Launching MARS...
cd Build
IF EXIST MARS.sln (
MARS.sln GOTO end 
) ELSE (
echo Project files haven't been generated.
echo Press any key to launch GenProjectFiles.bat
pause >nul
cd /d %~dp0
GenProjectFiles.bat) 

: end
exit