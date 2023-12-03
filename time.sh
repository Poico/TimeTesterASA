for file in teste_*.txt; do
    echo "-----------------------"
    echo $file
    echo $file >> tempo.txt
    { time ./a.out < $file; } 2>> tempo.txt
done
