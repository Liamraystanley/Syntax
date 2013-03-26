<?php
/*
 * This module is used for pinging support members
 * when a user with a specific nick joins the channel.
 * 
 */

define('PING_LIST', 'ping_list');

class ping extends SyntaxModule {

	private $ping;
	private $ping_file;

	public function __construct() {
		$this->ping_file = SETTINGS_PATH . '/ping/' . PING_LIST;
		if (file_exists($this->ping_file)) {
			$this->ping = explode(',', file_get_contents($this->ping_file) );
		} else {
			$this->ping = array();
		}
	}

	public function commands($recipient, $message, $nick, $host) {
		global $user;

		// Remove all unneeded whitespaces
		$message = $this->sanitize($message);

		// Split the first part of $message into a command and its arguments
		$message = $this->split($message);

		$command = $message["0"];
		$arguments = $message["1"];

		if ($recipient = $user["nick"]) {
			$send = $nick;
		} else {
			$send = $recipient;
		}

		if (strtolower($command) == ".pinghelp") {
			$this->say($send, $nick. ": Hi! I'm Syntax. I'm used to ping people when a user " .
					"looking for help arrives. Use .pingadd or .pingremove to add or remove yourself from " .
					"the ping list.");
		}

		else if (strtolower($command) == ".pingadd") {
			if (in_array($nick, $this->ping)) {
				$this->commands($recipient, ".pingremove", $nick, $host);
			} else {
				array_push($this->ping, $nick);
				$this->say($send, $nick . ": You have been added to the ping list. Whenever " .
						"pa_**** joins the channel, or someone says \"help\", you will be pinged.");
				$this->updateFile();
			}
		}

		else if (strtolower($command) == ".pingremove") {

			if (in_array($nick, $this->ping)) {
				unset($this->ping[array_search($nick, $this->ping)]);
				$this->say($send, $nick . ": You have been removed from the ping list.");

				$this->updateFile();
			} else {
				$this->say($send, $nick . ": You were never in the ping list.");
			}

		}

		else if ( strpos(implode($message), 'help') !== false || strpos($command, 'help') !== false  ) {
			if (!in_array($nick, $this->ping)) {
				$this->pingHelp($nick);
			}
		}

	}

	public function ping($nick) {
		foreach($this->ping as $person) {
			$this->notice($person, "\002$nick\002 has joined #L");
		}
	}

	public function pingHelp($nick) {
		foreach($this->ping as $person) {
			$this->notice($person, "\002$nick\002 called for help in #L");
		}
	}

	public function updateFile() {
		if (!file_exists($this->ping_file)) {
			mkdir(SETTINGS_PATH . '/ping');
		}
		file_put_contents($this->ping_file, implode(',', $this->ping) );
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
			case 'JOIN':
				$recipient = $data["2"];

				if (preg_match("/webuser_\d{4,4}$/i", $nick) == 1) {
					$this->ping($nick);
					$this->say("#BroCrafting", 'Hi ' . $nick . '! Welcome to the #L'.
							'IRC channel. Please ask your question and someone should be with you shortly. '. 
							'If you do not receive an answer wait a bit longer or consider posting '. 
							'it on the forums.');
				}
			break;
		}
	}

}
?>
