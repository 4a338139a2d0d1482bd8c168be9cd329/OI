g++ gen.cpp -o gen
g++ miku.cpp -o miku
g++ bf.cpp -o bf
while true; do
	./gen
	./miku
	./bf
	if diff miku.out bf.out; then
		echo ok
	else
		echo jiba
		break
	fi
done
