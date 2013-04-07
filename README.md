Syntax -- The Modular PHP IRC Bot
=================================

What is Syntax?
===============
_______________
This is a modular PHP IRC bot forked from [nessa](http://github.com/gluxon/nessa) developed by the Liam Stanley.

Features
========
________
- PHP based, Which is highly configureable.
- Modular - Interchangeable, and easy to addon.
- Multi-OS - Can be run on many operating systems, including linux, mac, and windows.

Documentation
=============
_____________
The documentation for Syntax is a work in progress. If you'd like to contribute feel free to fork Syntax and request a source merge.
If you'd like to discuss forks from this project or know what a module does, feel free to tap into our IRC channel #xBlaze on irc.esper.net:6667.

Download
========
________
To install Syntax, you may require a few packages.
[Syntax](https://github.com/liamraystanley/Syntax/archive/master.zip) (obviously, it's the core)
[PHP5](http://us.php.net/downloads.php) (highly recommended, PHP 4+ required).
nohup (for ability to fork into background, whould be in your linux distro package by default).
screen (for ability to fork into background, and reattach at a later time).
- usually have to install, via "apt-get install screen", "yum install screen", or the default distrobution package manager.

Installation
============
____________

Linux
-----
_____

to install Syntax on linux, make sure to have a way to fork Syntax into the background (READ ABOVE).
download the syntax using the link above (if using a GUI linux). if you are using UNIX, or a unix based server, use `wget` to download the package.

    mkdir syntax
	cd syntax
	wget https://github.com/liamraystanley/Syntax/archive/master.zip

now, unzip the archive to the `syntax` directory

    unzip master.zip


Windows
-------
_______

to install Syntax on Windows, make sure you have syntax downloaded and you have PHP added to the environment path. use [this](http://www.php.net/manual/en/faq.installation.php#faq.installation.addtopath) method.
download the syntax using the link in the downloads section.

Configuration
=============
_____________

Linux
-----
_____

to configure Syntax for the first time on a linux OS, you must first edit the bot.inc file. make sure you are in the `syntax` directory.

    cd syntax (or what ever directory you unzipped syntax to)

now, you must copy the `bot_example.inc` file and rename the copied version to `bot.inc`. you must have a text editor installed on your linux/unix box, or direct FTP access to the file. common text editors would include `vi` or `vim`, `nano`, `emacs`, or your favorite text/source editor.

    cd settings (make sure you are in the syntax directory before you do this)
	edit bot.inc (or vi bot.inc, nano bot.inc, etc)

make sure you check and recheck every setting, once you are done configuring, feel free to head to the Running Syntax section.

Windows
-------
_______

to configure Syntax on windows for the first time, just go into the `/syntax/settings/` directory and find `bot_example.inc`.
copy that file and rename the copied version of the file to `bot.inc`, and edit  the file.
- Be advised, the windows notepad tends to fuck up some text-based files, so i'd recommend using notepad++. once you are done, save it, and head down to the Running Syntax, in hte windows section.


Running Syntax
===============
_______________

Linux
-----
_____
to run Syntax, on linux, there are a few different methods.

Screen - multiscreen terminal tool
----------------------------------

    screen (hit enter twice once you type this command)
	php syntax.php

now, to close safely just press `CTRL+A` then `CTRL+D`. then you can exit terminal, or SSH safely :D.
- To get back to that screen, in terminal type `screen -r`.

Nohup - background process forker
---------------------------------

    nohup php syntax.php &

it should push all stdout and all error messages to nohup.out. to forcefully stop a nohup process, you can kill the process with `killall -9 php`. WARNING this will kill any other process running with php.

Executeable bash script
----------------------

Syntax has another useful tool. the executeable bash script.
to use this just go to the `syntax` directory, and make it executeable, do this command:

    cd syntax (or directory that you stored syntax)
	chmod +x syntax
	./syntax

this should bring up a prompt asking you to use screen, nohup, or just run without forking into background.

Windows
-------
_______

if you added PHP to your `$PATH` environment variable, then you can just double click and run syntax.bat, which is a windows DOS version command-prompt.

if you did not, or do not know how to add it to your `$PATH` variable, then you have to navigate to the default PHP install directory in command-prompt and run Syntax from there. i.e:

    C:/path/to/php syntax.php

Syntax Copyright (C) 2013 Liam Stanley (More info here: http://liamstanley.net/gpl)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
