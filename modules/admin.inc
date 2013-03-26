<?php
class admin extends SyntaxModule {

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

		// !op
		if ( $command == ".op" && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) { 
				$this->mode($recipient, '+o', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '+o', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '+o', $arguments["0"]);
			}
		}

		// !deop
		else if ( $command == ".deop" && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) { 
				$this->mode($recipient, '-o', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '-o', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '-o', $arguments["0"]);
			}
		}
	
		// !voice
		else if ( $command == ".voice" && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) {
				$this->mode($recipient, '+v', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '+v', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '+v', $arguments["0"]);
			}
		}

		// !devoice
		else if ( $command == ".devoice" && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) {
				$this->mode($recipient, '-v', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '-v', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '-v', $arguments["0"]);
			}
		}
	
		// !quiet
		else if ( $command == ".quiet" && $this->isAdmin($host)  ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) {
				$this->mode($recipient, '+q', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '+q', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '+q', $arguments["0"]);
			}
		}

		// !unquiet
		else if ( $command == ".unquiet" && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments);
			if (empty($arguments["0"]) && $recipient != $nick) {
				$this->mode($recipient, '-q', $nick);
			} else if (count($arguments) >= 2) {
				$this->mode($arguments["0"], '-q', $arguments["1"]);
			} else if (count($arguments) >= 1 && $recipient != $nick) {
				$this->mode($recipient, '-q', $arguments["0"]);
			}

		// Send Message (from admin)
		} else if ( $command == '.msg' && $this->isAdmin($host) ) {
			$arguments=explode(" ", $arguments, 2);
			$this->say($arguments["0"], $arguments["1"]);

		// Join channel (from admin)
		} else if ( $command == '.join' && $this->isAdmin($host) ) {
			$this->sendData("JOIN " . $arguments);

		// Leave channel (from admin)
		} else if ( $command == '.part' && $this->isAdmin($host) ) {
			$this->sendData("PART " . $arguments);

		// Change nickname (from admin)
		} else if ( $command == '.nick' && $this->isAdmin($host) ) {
			$this->sendData("NICK " . $arguments);

		// Execute a raw php command. Dangerous.
		} else if ( $command == '.execute' && $this->isAdmin($host) ) {
			eval($arguments);

		}
	}
}
?>
