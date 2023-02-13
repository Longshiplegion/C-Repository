#!/bin/bash
number=51
if [ $number -lt 50 ]
then
    echo "The Number is less than 50"
elif [ $number -eq 50 ]
then
    echo "The Number is equal to 50"
else
    echo "The Number is greater than 50"
fi
