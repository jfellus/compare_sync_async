#!/bin/sh

for N in 10000; do
	for TP in 2000 3000 4000 5000 6000 7000 8000 9000 10000; do
		echo "$N $TP"
		./Debug/sync_async $N $TP >/dev/null
		tail times.txt
	done
done
