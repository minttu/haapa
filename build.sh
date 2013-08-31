#!/bin/bash

function init () {
	i=0
	x=0
	status=0
	export ADD_FILE=""
	export ADD_LIB=""
	export ADD_CFLAG=""
	return 0
}

function adddep () {
	VARS[$i]=false
	OPTIONAL[$i]=$1
	NAME[$i]=$2
	FILES[$i]=$3
	CFLAGS[$i]=$4
	LIBS[$i]=$5
	REQUIRE[$i]=$6
	i=`expr $i + 1`
}

function check_deps () {
	echo "> Checking for dependencies"

	# dependency checking
	# optional | name | .c files | cflags | libs | required files

	adddep false "Required | libevent" "src/haapa.c src/proc.c src/result.c src/time.c src/battery.c src/network.c" "" "" "/usr/include/event.h"
	adddep true "Optional | libmpdclient" "src/mpd.c" "-DINCLUDE_MPD" "-lmpdclient" "/usr/include/mpd/client.h"
	adddep true "Optional | iwlib" "src/wireless.c" "-DINCLUDE_IWLIB" "-liw" "/usr/include/iwlib.h"

	while [ $x -le `expr $i - 1` ]
	do
		if [ -f ${REQUIRE[$x]} ]; then
			VARS[$x]=true
		fi
		echo ${NAME[$x]}": "${VARS[$x]}
		if [ ${VARS[$x]} = true ]; then
			ADD_LIB=$ADD_LIB" "${LIBS[$x]}
			ADD_FILE=$ADD_FILE" "${FILES[$x]}
			ADD_CFLAG=$ADD_CFLAG" "${CFLAGS[$x]}
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

