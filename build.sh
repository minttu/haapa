#!/bin/bash

i=0
x=0
export ADD_FILE=""
export ADD_LIB=""

echo "> Checking for optional dependencie"

# mpd
VARS[$i]=false
NAME[$i]="libmpdclient"
FILES[$i]="mpd.c"
LIBS[$i]="-lmpdclient"

if [ -f /usr/include/mpd/client.h ]; then
	VARS[$i]=true
fi
i=`expr $i + 1`
# end mpd

while [ $x -le `expr $i - 1` ]
do
	echo ${NAME[$x]}": "${VARS[$x]}
	if [ ${VARS[$x]} = true ]; then
		ADD_LIB=$FINALLIBS" "${LIBS[$x]}
		ADD_FILE=$FINALFILES" "${FILES[$x]}
	fi
	x=`expr $x + 1`
done

echo "> Compiling"

make