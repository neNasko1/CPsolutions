make a
make b
make gen
for((i = 1; ; i ++)); do
    echo $i
    ./gen $i > testInput.in
    if ! diff -w <(./a < testInput.in) <(./b < testInput.in)
    then
    	cat testInput.in
    	break
	fi
done
