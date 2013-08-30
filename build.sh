#!/bin/bash

function init () {
	i=0
	x=0
	status=0
	export ADD_FILE=""
	export ADD_LIB=""
	return 0
}

function require_event () {
	VARS[$i]=false
	OPTIONAL[$i]=false
	NAME[$i]="Required | libevent"
	FILES[$i]="src/haapa.c src/proc.c src/result.c src/time.c src/battery.c src/network.c"
	LIBS[$i]=""
	REQUIRE[$i]="/usr/include/event.h"
	i=`expr $i + 1`
}

function require_mpd () {
	VARS[$i]=false
	OPTIONAL[$i]=true
	NAME[$i]="Optional | libmpdclient"
	FILES[$i]="src/mpd.c"
	LIBS[$i]="-lmpdclient"
	REQUIRE[$i]="/usr/include/mpd/client.h"
	i=`expr $i + 1`
}

function check_deps () {
	echo "> Checking for dependencies"
	require_event
	require_mpd

	while [ $x -le `expr $i - 1` ]
	do
		if [ -f ${REQUIRE[$x]} ]; then
			VARS[$x]=true
		fi
		echo ${NAME[$x]}": "${VARS[$x]}
		if [ ${VARS[$x]} = true ]; then
			ADD_LIB=$ADD_LIB" "${LIBS[$x]}
			ADD_FILE=$ADD_FILE" "${FILES[$x]}
		else
			if [ ${OPTIONAL[$x]} = false ]; then
				echo "Error: Missing required library!"
				status=1
				return 1
			fi
		fi
		x=`expr $x + 1`
	done
	status=0
	return 0
}

function compile () {
	echo "> Compiling"

	make clean
	make build_haapa
}

init
check_deps
if [ $status = 0 ]; then
	compile
fi

