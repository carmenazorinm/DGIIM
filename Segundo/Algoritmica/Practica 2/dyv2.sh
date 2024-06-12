#!/bin/bash
echo "" >> salida.dat


n="1000"
while [ $n -le 100000 ]
do
./gen1 $n >> salida2.dat
n=$(( $n+1000 ))
done


