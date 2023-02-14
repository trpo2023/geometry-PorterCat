all: main

make: main.c
	gcc -o -Wall -Werror main main.c
run: 
	./main
clear:
	rm main
