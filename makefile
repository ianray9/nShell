build:
	gcc --std=c99 -c nShell.c -o nShell.o -g
	gcc main.c nShell.o -o nsh

run:
	./nsh

clean:
	rm nsh nShell.o
