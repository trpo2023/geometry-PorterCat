CFLAGS = -Wall -Wextra -Werror -lm
CPPFLAGS = -MMD

.PHONY: clean

bin/main: bin/main.o bin/geometrylib.a 
	$(CC) $(CFLAGS) -o $@ $^

bin/main.o: src/geometry/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< -I src
	
bin/geometrylib.a: bin/geometrylib.o
	ar rsc $@ $^

bin/geometrylib.o: src/geometrylib/geometrylib.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<
	
bin/main:  bin/main example.wkt

clean:
	rm -rf bin/*.o
	rm -rf bin/*.d
	rm -rf bin/*.a
	rm -rf bin/main
	
-include bin/main.d bin/geometrylib.d

