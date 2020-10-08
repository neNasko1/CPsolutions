for((i = 1; ; i ++)); do
    echo $i
    ./gen.exe $i > testInput.in
    if ! diff -w <(./a.exe < testInput.in) <(./b.exe < testInput.in)
    then
    	cat testInput.in
    	break
	fi
done
