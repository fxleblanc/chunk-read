MLBS=$(shell cat words.txt dict.txt | wc -L)
CWC=2
DWC=$(shell cat dict.txt | wc -l)

all: build

build:
	@echo Maximum line buffer size: $(MLBS)
	gcc -D MAX_LINE_BUFFER_SIZE=$(MLBS) -D CHUNK_WORD_COUNT=$(CWC) main.c
debug:
	gcc -g -D MAX_LINE_BUFFER_SIZE=$(MLBS) -D CHUNK_WORD_COUNT=$(CWC) main.c
	gdb --args a.out words.txt dict.txt
run: build
	./a.out words.txt dict.txt
