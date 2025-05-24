build:
	gcc --std=c99 -Werror -Wall -c src/nShell.c -o nShell.o -g
	gcc --std=c99 -Werror -Wall src/main.c nShell.o -o nshell

run:
	./nsh

clean:
	rm nshell nShell.o
