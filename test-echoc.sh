#!/bin/sh

colors="blue red green magenta pink yellow white light black"

# testar
echo "> Testando"

for c in $colors; do
	for opt in "" "-B" "-s" "-p" "-l"; do
		for b in $colors; do
			echo -n "[$c]{$b} "
			/tmp/echoc -c $c -b $b $opt "Hola!"
		done
		echo
	done
	echo
done
/tmp/setcolor
echo "RESETADO"

echo "> Fim"



