haapa
=====

A simple status program.

dependencies
------------

required:
* libevent

optional:
* libmpdclient
* alsa
* iwlib
* Xlib

installation
------------

	make
	sudo make install

configuration
-------------

see ```docs/CONFIGURATION.md``` and [this](https://JuhaniImberg.github.io/haapa/)

example output
--------------

<pre><span style="color: #859900;">♫</span> <span style="color: #859900;">muted</span> <span style="color: #DC322F;">⇋</span> <span style="color: #DC322F;">Guest</span> <span style="color: #DC322F;"> 82%</span> <span style="color: #DC322F;">192.168.0.7</span> <span style="color: #CB4B16;">❤</span> <span style="color: #CB4B16;">56°C</span> <span style="color: #CB4B16;">│▎         │</span> <span style="color: #CB4B16;">≣</span> <span style="color: #CB4B16;">│███▌      │</span> <span style="color: #2AA198;">☇</span> <span style="color: #2AA198;">Charging</span> <span style="color: #2AA198;">│█████████▋│</span> <span style="color: #B58900;">13:55:50</span> </pre>

license
-------

MIT, see LICENSE
