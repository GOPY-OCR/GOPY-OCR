#!/bin/bash

i=1
max=50
checkpoint_interval=20
while [ $i -le $max ]
do
    ./main -t -vv $checkpoint_interval
    tail -n $checkpoint_interval _build/accuracies.csv >> agregated_accuracies.csv
    #cp _build/ocr_save.nn _build/ocr_save.nn.$i
    i=$((i+1))
done

