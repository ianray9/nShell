build:
	gcc --std=c99 nShell.c -o nsh -g

run:
	./nsh

clean:
	rm nsh
