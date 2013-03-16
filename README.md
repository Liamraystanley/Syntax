Abigail - The Modular PHP IRC Bot
=================================

What is Abigail?
----------------
________________
This is a modular PHP IRC bot forked from [nessa](http://github.com/gluxon/nessa).

Features
--------
________
- PHP based, Which is highly configureable.
- Modular - Interchangeable, and easy to addon.
- Multi-OS - Can be run on many operating systems, including linux, mac, and windows.

Documentation
-------------
_____________
The documentation for Abigail is a work in progress. If you'd like to contribute feel free to fork Abigail and request a source merge.
If you'd like to discuss forks from this project or know what a module does, feel free to tap into our IRC channel #xBlaze on irc.esper.net:6667.

Download
--------
________
To install Abigail, you may require a few packages.
[Abigail](https://github.com/xBlazeTECH/abigail/archive/master.zip) (obviously, it's the core)
[PHP5](http://us.php.net/downloads.php) (highly recommended, PHP 4+ required).
nohup (for ability to fork into background, whould be in your linux distro package by default).
screen (for ability to fork into background, and reattach at a later time).
- usually have to install, via "apt-get install screen", "yum install screen", or the default distrobution package manager.

Installation
------------
____________

Linux

To install Abigail on linux, make sure to have a way to fork Abigail into the background (READ ABOVE).
download the abigail using the link above (if using a GUI linux). If you are using UNIX, or a unix based server, use `wget` to download the package

    mkdir abigail
	cd abigail
	wget https://github.com/xBlazeTECH/abigail/archive/master.zip

Now, unzip the archive to the `abigail` directory

    unzip master.zip

To run Abigail, there are a few different methods.

Screen - Multiscreen terminal tool

    screen (hit enter twice once you type this command)
	php abigail.php

now, to close safely just press `CTRL+A` then `CTRL+D`. then you can exit terminal, or SSH safely :D.
- To get back to that screen, in terminal type `screen -r`.

Nohup - background process forker

    nohup php abigail.php &

it should push all stdout and all error messages to nohup.out or process.out