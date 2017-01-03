#!/bin/bash

i=10
f=$(mktemp)
while [ $i -lt 400 ]
do
	./randomInput.py $i > $f
	timer=`date +%s.%N`
	./cut.py $f > /dev/null
	elapsed=`echo $(date +%s.%N) -$timer | bc`
	echo $i $elapsed
	i=$(( $i + 1 ))
done


