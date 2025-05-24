build:
	gcc --std=c99 -Werror -Wall -c src/nShell.c -o nShell.o -g
	gcc --std=c99 -Werror -Wall src/main.c nShell.o -o nsh

run:
	./nsh

clean:
	rm nsh nShell.o
