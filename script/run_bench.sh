#!/bin/bash

solver=$1
bench=$2

log=log/$solver

if [ -f $log ]; then
	rm $log
fi

for fname in ./benchmarks/$bench/*; do
	(time ./$solver $fname) >> ./log/${bench}_${solver} 2>&1
done
