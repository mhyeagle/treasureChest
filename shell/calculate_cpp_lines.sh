#!/bin/bash

num=0
lines=0
for i in `find . -name *.cpp`
do
    let lines=`wc -l $i|awk '{print $1}'`
    let sum=$sum+$lines
done

echo $sum

