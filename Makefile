CWC=2

all: build

build:
	@echo Maximum number of words per chunk: $(CWC)
	gcc -D CHUNK_WORD_COUNT=$(CWC) main.c
debug:
	gcc -g -D CHUNK_WORD_COUNT=$(CWC) main.c
	gdb --args a.out words.txt dict.txt
run: build
	./a.out words.txt dict.txt
