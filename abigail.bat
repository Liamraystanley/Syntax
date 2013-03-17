@echo off
title Abigail PHP IRC Bot
goto start
:start
color 07
cls
echo Copyright (C) 2012 Brandon Chengecho Abigail Copyright (C) 2013 Liam Stanleyecho.echo This program is free software: you can redistribute it and/or modifyecho it under the terms of the GNU General Public License as published byecho the Free Software Foundation, either version 3 of the License, orecho (at your option) any later version.echo.echo This program is distributed in the hope that it will be useful,echo but WITHOUT ANY WARRANTY; without even the implied warranty ofecho MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See theecho GNU General Public License for more details.echo.echo You should have received a copy of the GNU General Public Licenseecho along with this program.  If not, see <http://www.gnu.org/licenses/>.
echo.
echo.
echo Starting Abigail...
echo MAKE SURE YOU EDITED ABIGAILS CONFIG!
php abigail.php || goto failed
echo Successfully started Abigail!
goto success
:failed
color 04
echo Oh no! There was an error when starting Abigail!
echo have you added PHP to your path environment variable?
echo (if not, goto our Git-Hub page for a how-to)
echo press anything to try and start Abigail again...
:success
pause > nul
cls
goto start
exit