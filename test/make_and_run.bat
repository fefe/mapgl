@echo off

set app=select

PATH=%PATH%;c:\Borland\BCC55\Bin\

bcc32 %app%.c

echo.
pause

%app%.exe
