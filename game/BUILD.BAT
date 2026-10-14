@echo off
rem Build one episode of Duke Nukum v2.0 with Turbo C 2.0, TASM 1.0, TLINK 2.0 and LZEXE 0.91.
rem usage: BUILD 1|2|3      (expects TCC, TASM, TLINK, LZEXE on the PATH and TC = the Turbo C directory)
if "%1"=="" goto usage
if "%TC%"=="" set TC=C:\TC
tcc -c -ml -Z -G -O -1- -f- -K -I%TC%\INCLUDE -DEPISODE=%1 GAME1.C GAME2.C
if errorlevel 1 goto fail
tasm /MX TOOLBOX.ASM
if errorlevel 1 goto fail
tlink /c /d /s %TC%\LIB\C0L TOOLBOX GAME1 GAME2, DN%1.EXE, DN%1.MAP, %TC%\LIB\CL.LIB
if errorlevel 1 goto fail
lzexe DN%1.EXE
goto end
:usage
echo usage: BUILD 1^|2^|3
goto end
:fail
echo build failed
:end
