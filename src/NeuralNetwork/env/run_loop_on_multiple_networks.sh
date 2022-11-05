# this works by compiling the code with differents network
# configurations in differents main files such as
# main.10 main.100 main.64 etc.
base="main"
versions="256"
epochs=100
for i in $versions
do
    echo "running train loop on $base.$i"
    ./$base.$i -t -v $epochs
    mv _build/ocr_save.nn _build/ocr_save.$i.nn
    mv _build/accuracies.csv _build/accuracies.$i.csv
done
