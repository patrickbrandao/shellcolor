#!/bin/sh

colors="blue red green magenta pink yellow white light black"

# testar
echo "> Testando"

for c in $colors; do
	for opt in "" "-b" "-s" "-p" "-l"; do
		for b in $colors; do
			/tmp/setcolor $c $b $opt
			echo -n "[$c]{$b} "
			/tmp/setcolor
		done
		echo
	done
	echo
done
/tmp/setcolor
echo "RESETADO"



echo "> Fim"



