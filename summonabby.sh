#!/bin/bash
echo This way of starting abigail is still under development.
echo ####################################
echo #       Welcome to Abigail!        #
echo #       Developed by BroDev        #
echo ####################################
echo How would you like to begin? Use numbers please...
echo   1. Basic
echo   2. Debug
read choice
if [ $choice = "2" ]; then
php abigail.php
else
screen php abigail.php
fi
