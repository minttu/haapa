haapa
=====

A simple status program.

dependencies
------------

	required:
	- libevent
	optional:
	- libmpdclient

usage
-----

	./build.sh
	./haapa

configuration
-------------

see config.h

daydreaming (ignore this)
=========================

configuration:

	OUTPUT \
	s(t("B: ") string(battery_status) t(" ") bar(battery_capacity) ,"#FF0000", TRUE)

	s(commands, color, condition) ->
		if !condition()
			return
		output += SEGMENT_START
		commands()
		output += create_color(color)
		output += SEGMENT_END
		output += SEGMENT_SEPERATOR

	t(text) ->
		output += text

	string(function) ->
		result = function()
		output += result.string

	bar(function) ->
		result = function()
		bar_output = generate_bar(result.value, result.max)
		output += bar_output

	percent(function) ->
		result = function()
		output += result.value/result.max %

	time(function) ->
		result = function()
		output += format(result.time)

	TRUE is a function pointer to a function thats always true

	functions that are passed to output functions are pointers to those functions

config:

	- segment seperators (eg. i3 format)
	- bar format
	- time format
	- percent format

segments:
	
	- statements
	- color
	- optional condition

result:

	- string
	- value
	- max
	- time
	- status
	- error

compiling:

	> checking dependencies
	Required | libevent: true
	Optional | libmpdclient: false
	> modules
	base, cpu, battery
	> ignored modules
	mpd
	> building
	gcc -Wall -O2 --std=gnu99 -g -lm -levent haapa.c cpu.c battery.c -o haapa

config file:

	1) do we need one
	2) what format

	1) No, but it would be still usefull.
	2) Must be different from other status scripts. json? yaml? custom?