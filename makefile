main: clean
	gcc -Wall -Wpedantic -lncurses -lm src/*.c -o TTE

clean: 
	rm -f TTE