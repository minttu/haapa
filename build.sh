#!/bin/bash

i=0
x=0
export ADD_FILE=""
export ADD_LIB=""

echo "> Checking for dependencies"

# event
VARS[$i]=false
OPTIONAL[$i]=false
NAME[$i]="Required | libevent"
FILES[$i]=""
LIBS[$i]=""
REQUIRE[$i]="/usr/include/event.h"
i=`expr $i + 1`
# end event

# mpd
VARS[$i]=false
OPTIONAL[$i]=true
NAME[$i]="Optional | libmpdclient"
FILES[$i]="mpd.c"
LIBS[$i]="-lmpdclient"
REQUIRE[$i]="/usr/include/mpd/client.h"
i=`expr $i + 1`
# end mpd

while [ $x -le `expr $i - 1` ]
do
	if [ -f ${REQUIRE[$x]} ]; then
		VARS[$x]=true
	fi
	echo ${NAME[$x]}": "${VARS[$x]}
	if [ ${VARS[$x]} = true ]; then
		ADD_LIB=$FINALLIBS" "${LIBS[$x]}
		ADD_FILE=$FINALFILES" "${FILES[$x]}
	else
		if [ ${OPTIONAL[$x]} = true ]; then
			echo "Error: Missing required library!"
			return
		fi
	fi
	x=`expr $x + 1`
done

echo "> Compiling"

make clean
make