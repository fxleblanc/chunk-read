all: build

build:
	gcc main.c
debug:
	gcc -g main.c
	gdb a.out
run: build
	./a.out
