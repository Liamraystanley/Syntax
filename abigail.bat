@echo off
title Abigail PHP IRC Bot
:start
echo Starting Abigail...
echo MAKE SURE YOU EDITED ABIGAILS CONFIG!
php abigail.php || goto failed
echo Successfully started Abigail!
goto success
:failed
echo Oh no! There was an error when starting Abigail!
echo have you added PHP to your path environment variable?
echo (if not, goto our Git-Hub page for a how-to)
echo press anything to try and start Abigail again...
:success
pause > nul
clr
goto start
exit