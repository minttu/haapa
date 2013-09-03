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

function expto () {
	string=$1
	length=${#string}
	untill=$2
	echo -n $1
	while [ $length -ne $untill ]
	do
		echo -n ' '
		length=`expr $length + 1`
	done
}

function check_deps () {
	echo -e "> Checking for dependencies\n"

	# dependency checking
	# optional | name | .c files | cflags | libs | required files

	adddep false "libevent" "src/haapa.c src/proc.c src/result.c src/time.c src/battery.c src/network.c src/exec.c src/format.c src/output.c" "" "" "/usr/include/event.h"
	adddep true "libmpdclient" "src/mpd.c" "-DINCLUDE_MPD" "-lmpdclient" "/usr/include/mpd/client.h"
	adddep true "iwlib" "src/wireless.c" "-DINCLUDE_IWLIB" "-liw" "/usr/include/iwlib.h"
	adddep true "alsa" "src/alsa.c" "-DINCLUDE_ALSA" "-lasound" "/usr/include/alsa/asoundlib.h"
	adddep true "Xlib" "src/output_x.c" "-DINCLUDE_XLIB" "-lX11" "/usr/include/X11/Xlib.h"

	echo "+-----------+---------------------+-----------+"
	echo "| Needed    | Name                | Found     |"
	echo "+-----------+---------------------+-----------+"

	while [ $x -le `expr $i - 1` ]
	do
		if [ -f ${REQUIRE[$x]} ]; then
			VARS[$x]=true
		fi

		echo -n "| "
		if [ ${OPTIONAL[$x]} = true ]; then
			expto "no" 10
		else
			expto "yes" 10
		fi
		echo -n "| "
		expto ${NAME[$x]} 20
		echo -n "| "
		if [ ${VARS[$x]} = true ]; then
			expto "yes" 10
		else
			expto "no" 10
		fi
		echo -e "|"

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
	echo "+-----------+---------------------+-----------+"
	status=0
	return 0
}

function compile () {
	echo -e "\n> Cleaning\n"
	make clean

	echo -e "\n> Compiling\n"
	make build_haapa
}

function test_run () {
	echo -e "\n> Testing\n"

	./haapa -o

	if [ $? -eq 0 ]; then
		echo -e "\nTesting successfull"
	else
		echo -e "\nTesting unsuccessfull"
	fi
}

init
check_deps
if [ $status -eq 0 ]; then
	compile
	if [ $? -eq 0 ]; then
		test_run
	fi
fi

