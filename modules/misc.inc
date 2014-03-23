<?php
class misc extends SyntaxModule {

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
		/*} else if ( $command == '.client' ) { 
			 $this->sendData("PRIVMSG $arguments \x01VERSION\x01");
			 $this->getData("NOTICE ", $arguments);*/

		} else if ( $command == '.uptime' ) {
			$uptime = system('uptime');
			$this->say($recipient, "$uptime");
		} else if ( $command == '.memory' ) {
		    $usedMem = round(((memory_get_usage() / 1024) / 1024),2);
		    $freeMem = round(($this->config['memoryLimit'] - $usedMem),2);
			$this->say($recipient, ": Memory status: {$usedMem} MB used");

		} else if ( $command == '.slap') {
			 	$this->say($recipient, "\x01ACTION slaps $arguments with a large trout\x01");

		} else if ( $command == '.bitcoin' ) {
            $price = json_decode(file_get_contents( "http://data.mtgox.com/api/1/BTCUSD/ticker"),true);
			$this->say($recipient, "MtGox Buy: {$price['return']['buy']['display_short']}; Sell: {$price['return']['sell']['display_short']}; High: {$price['return']['high']['display_short']}; Low: {$price['return']['low']['display_short']}");
	/*	} else if ( $command == '.urban' ) {
			$ud = json_decode(file_get_contents("http://api.urbandictionary.com/v0/define?term=$arguments"),true);
			$this->say($recipient, "Urban Dictionary: {$ud['definition']}");*/
		} else if ( $command == '.fml' ) {
			
		    $url = 'http://www.fmylife.com/random';
		    $cache = array();
		    $data = $this->curlGet($url);
		    $lines = explode("\n", $data);
		    foreach ($lines as $line) {
		    	if (preg_match('/class="fmllink">(.+)<\/a>.+? FML<\/a>.+?life sucks<\/a> \(<span.+?>([0-9]+?)<\/span>\).+?deserved it<\/a> \(<span.+?>([0-9]+?)<\/span>\)/', $line, $matches) !== false) {
		    		if (count($matches) == 4 && $matches[2] > $matches[3]) {
		    			$this->cache[] = strip_tags(trim($matches[1]));
		    		}
		    	}
		    }
		    if (count($this->cache) < 3) $this->refillCache();
		    $fml = array_shift($this->cache);
		    $this->say($recipient, "$fml");
		} else if ( $command == '.8ball') {
			$result = Rand (1,8); 
            if ($result ==1) 
            { 
            $this->say($recipient, "The 8-ball) says: Yes"); 
            } 
            if ($result ==2) 
            { 
            $this->say($recipient, "The 8-ball) says: No"); 
            } 
            if ($result ==3) 
            { 
            $this->say($recipient, "The 8-ball) says: Ask again later"); 
            } 
            if ($result ==4) 
            { 
            $this->say($recipient, "The 8-ball) says: Perhaps, perhaps, perhaps"); 
            } 
            if ($result ==5) 
            { 
            $this->say($recipient, "The 8-ball) says: The future is hazy"); 
            } 
            if ($result ==6) 
            { 
            $this->say($recipient, "The 8-ball) says: It is certain"); 
            } 
            if ($result ==7) 
            { 
            $this->say($recipient, "The 8-ball) says: Without a doubt"); 
            } 
            if ($result ==8) 
            { 
            $this->say($recipient, "The 8-ball) says: There is no chance"); 
            } 
		/*} else if ( $command == '.whois' || $command == '.geoip' ) {
            $geoip = json_decode(file_get_contents("http://geo.liamstanley.io/json/$arguments"), true);
			$this->say($recipient, "{$geoip['ip']['zipcode']['city']['region_name']['country_name']}");*/
		}else if ( $command == '.portcheck') {
            $conn = fsockopen($arguments); 
            if($conn) {
                $this->say($recipient, "Port Open");
                } else {
                	$this->say($recipient, "Port Closed");
                }
		}
}
}
