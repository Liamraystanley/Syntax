<?php
class lollygagging extends AbigailModule {

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

		// Hello Message
		if ( (strtolower($command) == "hello" || strtolower($command) == "hey" || strtolower($command) == "hi") && ($arguments == $user["nick"] || $arguments == $user["nick"] . "!") ) {
			$this->say($recipient, "Hello $nick!");

		// Get time
		} else if ( $command == '.time' ) {
			$this->say($recipient, date("H:i:s"));

		// Echo
		/*} else if ( $command == '.echo' ) {
			$this->say($recipient, $arguments);
		*/}

	}
}
?>
