<?php
/*
Copyright (C) 2012 Brandon Cheng
Abigail Copyright (C) 2013 Liam Stanley (More info here: http://liamstanley.net/gpl)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

// Stop PHP from killing itself in 30 seconds
set_time_limit(0);
// Use this when executing from a web address
// ignore_user_abort(true);

// Log error messages
ini_set('display_errors', 'On');
ini_set('log_errors', 'true');
ini_set('error_log', 'error_log');

// Where is everything?
define('INCLUDES_PATH', 'includes');
define('SETTINGS_PATH', 'settings');
define('MODULES_PATH', 'modules');
define("MODULES_EXTENSION", ".inc");

require("irc.inc"); // IRC Class
require("module.inc"); // Module Class

require(SETTINGS_PATH . "/bot.inc"); // Settings

// Connect to IRC
$irc = new AbigailIRC();
$irc->connect($server["address"], $server["port"]);

// Send the password and user ident info
$irc->sendPassword($user["password"]);
$irc->sendIdent($user["nick"], $user["mode"], $user["unused"], $user["realname"]);

// Import all modules
$module_dir=scandir(MODULES_PATH);
$modules=array();

foreach($module_dir as $module) {
	// Include the file if the module is a file and ends in ".inc";
	if ( is_file(MODULES_PATH . '/' . $module) && preg_match("/^.*" . MODULES_EXTENSION . "$/i", $module) == 1 ) {

		echo "# ", $module;
		for ($i=0; $i <= 30 - 4 - strlen($module); $i++) { echo " "; }
		echo "#\n";

		include(MODULES_PATH . '/' . $module);

		$module = substr($module, 0, strlen($module) - strlen(MODULES_EXTENSION));
		array_push($modules, $module);

		$$module = new $module();
		$$module->setSocket($irc->getSocket());
	}
}

// Continously read new lines
while (true) {

	// Read new line
	$data=$irc->getData(512);

	if (!empty($data)) {
		echo $data; 

		// Trim off line carriage and newline
		$data = str_replace("\r\n", '', $data);

		// Play some Ping Pong!
		$irc->PingPong($data);

		foreach($modules as $module) {
			$$module->run($data);
		}

	} else {
		foreach($modules as $module) {
			if (method_exists($$module, 'runMaintenance')) {
				$$module->runMaintenance();
			}
		}
	}
// Join the default channel
$irc->joinChannel($channel["name"]);
}
?>
