<?php
class NessaModule extends NessaIRC {

	public function sanitize($string) {
		// Remove double, extraneous whitespaces
		$string = preg_replace("/\s+/", " ", $string);
		if ( substr($string, -1, 1) == " " ) {
			$string = substr($string, 0, -1);
		}
		return $string;
	}

	public function split($string) {
		$ex = explode(' ', $string);
		$command = $ex["0"];
		if (isset($ex["1"])) {
			unset($ex["0"]);
			$arguments = implode(' ', $ex);
		} else {
			$arguments = '';
		}

		return array($command, $arguments);
	}

	/**
	* Check if the user is an admin
	*
	* @param mixed $nick Nickname of player
	* @param mixed $host Hostname of player
	* @param mixed $command Command
	* @return boolean True or False answer
	*/
	public function isAdmin($host) {
		global $admins;

		foreach($admins as $admin) {
			$admin = str_replace('.', '\\.', $admin);
			$admin = str_replace('/', '\/', $admin);
			$admin = str_replace('*', '.*', $admin);

			if (preg_match("/" . $admin . "$/i", $host) == 1) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Runs the bot functions
	 * 
	 * @param array $data explodeData() return
	 */
	public function run($data) {
		// Remove unneeded newline colon at beginning
		$data=substr($data, 1);

		$data = explode(' ', $data);
		// Check if there's a ! in the first part of $data
		if ( strpos($data["0"], '!') ) {
			// Message from user
			$nick=substr($data["0"], 0, strpos($data["0"], "!"));
			$host=substr($data["0"], strpos($data["0"], "!")+1);
		} else {
			// Message from server
			$server = implode(' ', $data);
		}

		$event = $data["1"];
		switch($event) {
			case 'PRIVMSG':
				$recipient = $data["2"];

				$implode=$data;
				unset($implode["0"], $implode["1"], $implode["2"]);
				$implode["3"] = substr($implode["3"], 1);

				$message=implode(" ", $implode);

				$this->commands($recipient, $message, $nick, $host);
			break;
		}
	}
}
?>
