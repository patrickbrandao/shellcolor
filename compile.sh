#!/bin/sh

TMPDST="$1"
if [ "$TMPDST" = "" ]; then TMPDST="/tmp"; fi

rm $TMPDST/setcolor $TMPDST/echoc 2>/dev/null 1>/dev/null

echo "> Compilando"

echo -n " - setcolor "
gcc setcolor.c -o $TMPDST/setcolor; if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 1; fi

echo -n " - echoc "
gcc echoc.c -o $TMPDST/echoc; if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 2; fi

echo -n " - beep "
gcc beep.c -o $TMPDST/beep; if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 2; fi

statuslist="
	echo_danger
	echo_done
	echo_failure
	echo_started
	echo_stopped
	echo_success
	echo_skip
	echo_warning
"
echo -n " - status "
for x in $statuslist; do
	gcc status.c -o $TMPDST/$x
	if [ "$?" = "0" ]; then echo -n "."; else -n echo "x"; fi
done
echo "OK"


