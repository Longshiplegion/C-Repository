#!/bin/bash
for i in 1 2 3 4 5

do
    echo "Welcome $i times"
done

for i in $(ls)
do
    echo  item: $i
done
