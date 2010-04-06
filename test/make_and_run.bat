@echo off

set app=tesselation
set app=tess

PATH=%PATH%;c:\Borland\BCC55\Bin\

bcc32 %app%.c

echo.
pause

%app%.exe
