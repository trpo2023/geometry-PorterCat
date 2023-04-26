all: main

make: main.c
	gcc -o -Wall -Werror main main.c
run: 
	./main example.wkt
clear:
	rm main
