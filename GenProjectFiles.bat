@echo off
color a
cls

title Generating Project Files...
mkdir Build
cd Build
cmake ../ -G "Visual Studio 15 Win64"
mkdir Debug
mkdir Release
cd /d %~dp0
copy Thirdparty\Libs\_bin\ Build\Debug
copy Thirdparty\Libs\_bin\ Build\Release

pause