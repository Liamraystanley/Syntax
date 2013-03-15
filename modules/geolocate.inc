<?php
class geolocate extends AbigailModule {
	/**
	* Run a command
	*
	* @param mixed $recipient A #room or user
	* @param mixed $message Message to send
	* @param mixed $nick Nickname of sender
	* @param mixed $host Host of sender
	*/

	public function commands($recipient, $message, $nick, $host) {
		global $user;

		// Remove all unneeded whitespaces
		$message = $this->sanitize($message);

		// Split the first part of $message into a command and its arguments
		$message = $this->split($message);

		$command = $message["0"];
		$arguments = $message["1"];
		$arguments = explode(" ", $arguments);
		
		// Locate an IP address
		if ( $command == '.locate' ) {
			global $ipdb_key;

			// Fetch the ipinfodb api page
			if ( empty($arguments[0]) ) {
				$this->say($recipient, $nick . ", Please enter a valid value.");
				return;
			}

			$args = explode(".", $arguments[0]);
			foreach($args as $arg) {
				if(strlen(strval($arg)) > 4) {
					$this->say($recipient, $nick . ", Please enter a valid value.");
					return;
				}
			}

			if ( !is_numeric(str_replace(".", "", $arguments[0])) ) {
				$this->say($recipient, $nick . ", Please enter a valid value.");
				return;
			}


			$res = fopen("http://api.ipinfodb.com/v3/ip-city/?key=" . $ipdb_key . "&ip=" . $arguments["0"] . "&format=xml", 'r');
			$ret = fread($res, 1024);

			$xmlString = json_decode(json_encode((array) simplexml_load_string($ret)), 1);
			var_dump($xmlString);

			// Now that we've gotten our reults back,
			// Sort tham into different variable.
			$retString = "";
			$rep = $xmlString;
			$ipAddress = $rep["ipAddress"][0];
			$countryCode = $rep["countryCode"][0];
			$countryName = ucwords(strtolower($rep["countryName"][0]));
			$regionName = ucwords(strtolower($rep["regionName"][0]));
			$cityName = ucwords(strtolower($rep["cityName"][0]));

			$latitude = $rep["latitude"];
			$longitude = $rep["longitude"];
			$timeZone = $rep["timeZone"][0];
			$zipCode = $rep["zipCode"][0];

			// Form the string to send to IRC
			if ( $cityName != "-" && $cityName != "" ) {
				$retString .= "\002Location:\002 " . $cityName;
			}
			if ( $countryName != "-" && $countryName != "" ) {
				$retString .= ", " . $countryName;
			}
			if ( $regionName !== "-" && $regionName !== "" ) {
				$retString .= ", " . $regionName;
			}

			$retString .= " (";
			if (!empty($latitude)) {
				$retString .= "\002Latitude:\002 " . $latitude;
			}
			if (!empty($longitude)) {
				$retString .= ", \002Longitude:\002 " . $longitude;
			}
			if ( $zipCode != "-" && $zipCode != "" ) {
				$retString .= ", \002Zip Code:\002 " . $zipCode;
			}
			if ( $timeZone !== "-" && $timeZone !== "" ) {
				$retString .= ", \002Time Zone:\002 " . $timeZone;
			}
			$retString .= ")";
			$retString = str_replace("()", "", $retString);
			$retString = str_replace("(, ", "(", $retString);
			$retString = trim($retString);
			$retString = utf8_encode($retString);
			var_dump($retString);

			// Finally, say it in IRC.
			if(!empty($retString)) {
				$this->say($recipient, $nick . ", " . $retString);
			} else {
				$this->say($recipient, $nick . ", IP \x0302" . $arguments[0] . "\x0F is reserved.");
			}
		}
	}
}
?>