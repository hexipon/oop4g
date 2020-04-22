REM Usage:

REM  - Open a terminal / command prompt (Windows-key + R , type "cmd", press ENTER)

REM  - To delete VS rubbish from one more directories

REM      del_vs_crap BUILDIR1 [BUILDIR2] [BUILDIR3] [...]

REM =======================================================================

set DIR=%CD%

:Loop

IF "%1"=="" GOTO Continue

cd %1

rd /s /q .git

rd /s /q .vs

del /s /q *.obj 

del /s /q *.o 

del /s /q *.pch

del /s /q *.pdb

del /s /q *.ilk

del /s /q *.idb

del /s /q *.gch

del /s /q *.tlog

del /s /q *.lastbuildstate

SHIFT

cd %DIR%

GOTO Loop

:Continue