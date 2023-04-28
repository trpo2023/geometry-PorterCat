CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

.PHONY: clean

bin/main: bin/main.o bin/geometrylib.a bin/parser.a
	$(CC) $(CFLAGS) -o $@ $^

bin/main.o: src/geometry/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< -I src
	
bin/geometrylib.a: bin/geometrylib.o
	ar rsc $@ $^

bin/parser.a: bin/parser.o
	ar rsc $@ $^

bin/checkFunctions.o: src/geometrylib/checkFunctions.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

bin/parser.o: src/geometrylib/parser.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -rf bin/*.o
	rm -rf bin/*.d
	rm -rf bin/*.a
	
-include bin/main.d bin/geometrylib.d
