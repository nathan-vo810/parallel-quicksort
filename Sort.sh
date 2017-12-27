#!/bin/bash

echo "Compiling all necessary file..."

echo "1. Array_Generate.c"
gcc Array_Generate.c -o Array_Generate.exe

echo "2. QuickSort_Serial.c"
gcc-7 -g -fopenmp -lm QuickSort_Serial.c -o QuickSort_Serial.exe

echo "3. QuickSort_Parallel.c"
gcc-7 -g -fopenmp -lm QuickSort_Parallel.c -o QuickSort_Parallel.exe
echo "Done"

echo "--------------------------------"

echo "Setting up number of threads: " $2
export OMP_NUM_THREADS=$2

echo "Generating array of size" $1
./Array_Generate.exe $1
echo "Done"

echo "--------------------------------"

echo "Executing Quicksort Serial"
./QuickSort_Serial.exe
echo "Done"

echo "--------------------------------"

echo "Executing QuickSort Parallel"
./QuickSort_Parallel.exe
echo "Done"

rm -fr *~ *.exe*


echo "--------------------------------"
echo "Plotting exectution time"
python3 Plot_Time.py