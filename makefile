# Flags
CFLAGS = --std=c99 -Wall -Wextra -Werror -Iinclude

# Files
SRC = src/main.c src/nShell.c
OBJ = build/main.o build/nShell.o
BIN = bin/nshell

all: $(BIN)

# Compile nshell executable
$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

# Compile c src files to obj files
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

run: $(BIN)
	./bin/nshell

clean:
	$(RM) -r build bin
