all: geometry

make: geometry.c
	gcc -o -Wall -Werror geometry geometry.c
run: 
	./geometry example.wkt
clear:
	rm geometry
