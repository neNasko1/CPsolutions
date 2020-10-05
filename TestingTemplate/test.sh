make a
make b
make gen
for((i = 1; ; i ++)); do
    echo $i
    ./gen $i > int
    if ! diff -w <(./a < int) <(./b < int) 
    then
    	cat int
    	break
	fi
done