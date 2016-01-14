#!/bin/sh

	USRDIR="$1"
	if [ "x$USRDIR" = "x" ]; then USRDIR="/usr"; fi

	TMPDST="$2"
	if [ "x$TMPDST" = "x" ]; then TMPDST="/tmp/shellcolor"; fi

	echo "> Compilando"
	mkdir -p $TMPDST
	mkdir -p $USRDIR
	mkdir -p $TMPDST$USRDIR/bin

	echo -n " - setcolor "
	rm $USRDIR/bin/setcolor $TMPDST$USRDIR/bin/setcolor 2>/dev/null
	gcc setcolor.c -o $TMPDST$USRDIR/bin/setcolor
	if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 1; fi
	cp $TMPDST$USRDIR/bin/setcolor $USRDIR/bin/setcolor
	chmod 755 $TMPDST$USRDIR/bin/setcolor $USRDIR/bin/setcolor

	echo -n " - echoc "
	rm $USRDIR/bin/echoc $TMPDST$USRDIR/bin/echoc 2>/dev/null
	gcc echoc.c -o $TMPDST$USRDIR/bin/echoc
	if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 1; fi
	cp $TMPDST$USRDIR/bin/echoc $USRDIR/bin/echoc
	chmod 755 $TMPDST$USRDIR/bin/echoc $USRDIR/bin/echoc

	echo -n " - beep "
	rm $USRDIR/bin/beep $TMPDST$USRDIR/bin/beep 2>/dev/null
	gcc beep.c -o $TMPDST$USRDIR/bin/beep
	if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 1; fi
	cp $TMPDST$USRDIR/bin/beep $USRDIR/bin/beep
	chmod 755 $TMPDST$USRDIR/bin/beep $USRDIR/bin/beep

	# instalar copias
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
		echo -n " - status :: $x "
		rm $USRDIR/bin/status $TMPDST$USRDIR/bin/status 2>/dev/null
		gcc status.c -o $TMPDST$USRDIR/bin/$x
		if [ "$?" = "0" ]; then echo "OK"; else echo "ERR"; exit 1; fi
		cp $TMPDST$USRDIR/bin/$x $USRDIR/bin/$x
		chmod 755 $TMPDST$USRDIR/bin/$x $USRDIR/bin/$x
	done
	echo "OK"
