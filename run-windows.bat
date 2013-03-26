@echo off
title Syntax PHP IRC Bot
MODE CON: COLS=120 LINES=45
goto start
:start
color 07
cls
echo Syntax Copyright (C) 2013 Liam Stanley
echo.
echo This program is free software: you can redistribute it and/or modify
echo it under the terms of the GNU General Public License as published by
echo the Free Software Foundation, either version 3 of the License, or
echo (at your option) any later version.
echo.
echo This program is distributed in the hope that it will be useful,
echo but WITHOUT ANY WARRANTY; without even the implied warranty of
echo MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
echo GNU General Public License for more details.
echo.
echo.
choice /c yn /n /d y /t 3 > nul
cls
echo Starting Syntax...
choice /c yn /n /d y /t 1 > nul
cls
echo MAKE SURE YOU EDITED SYNTAX'S CONFIG!
choice /c yn /n /d y /t 1 > nul
cls
php syntax.php || goto failed
echo Successfully started Syntax!
goto success
:failed
color 04
echo Oh no! There was an error when starting Syntax!
echo have you added PHP to your path environment variable?
echo (if not, goto our Git-Hub page for a how-to)
echo press anything to try and start Syntax again...
:success
pause > nul
cls
goto start
exit