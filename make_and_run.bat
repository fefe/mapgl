@echo off

PATH=%PATH%;c:\Borland\BCC55\Bin\

del mapgl.exe
del *.o > nul
del *.obj > nul
del *.res > nul
del *.tds > nul

bcc32 mapgl.c stringhandling.c datastructure.c polishfm.c trigonometry.c

echo.
pause

start mapgl.exe
