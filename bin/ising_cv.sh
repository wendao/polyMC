
for((i=0; i<100; i++))
do
	T=`echo 'scale=1;' $i / 10 + 0.1 | bc`
	./is_can.debug $T
done
