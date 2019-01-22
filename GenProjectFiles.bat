@echo off
color a
cls

title Generating Project Files...
mkdir Build
cd Build
cmake ../
mkdir Debug
mkdir Release
cd /d %~dp0
copy Thirdparty\Libs\_bin\ Build\Debug
copy Thirdparty\Libs\_bin\ Build\Release

MARS.sln.bat
EXIT