@echo off

del mapgl.exe
del *.o
del *.obj
del *.res
del *.tds

bcc32 mapgl.c stringhandling.c datastructure.c polishfm.c trigonometry.c

echo.
pause

mapgl.exe
