build:
	gcc --std=c99 -Werror -Wall -c nShell.c -o nShell.o -g
	gcc --std=c99 -Werror -Wall main.c nShell.o -o nsh

run:
	./nsh

clean:
	rm nsh
