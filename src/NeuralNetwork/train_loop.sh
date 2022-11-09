#!/bin/bash

i=1
max=1000
while [ $i -le $max ]
do
    ./main -t -v 100
    tail -n 100 _build/accuracies.csv >> agregated_accuracies.csv
    cp _build/ocr_save.nn _build/ocr_save.nn.$i
    i=$((i+1))
done

