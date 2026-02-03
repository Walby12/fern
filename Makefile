CFLAGS := -Wall -Wextra -O2
SRC := src/main.c src/lexer.c src/comp.c src/parser.c src/vm.c src/argparse.c

all: setup build

setup:
	@if not exist bin mkdir bin

build:
	gcc -o bin/fern $(SRC) $(CFLAGS)

clean:
	@if exist bin rmdir /s /q bin
