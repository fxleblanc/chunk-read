MLBS=$(shell cat words.txt dict.txt | wc -L)
WWC=$(shell cat words.txt | wc -l)
DWC=$(shell cat dict.txt | wc -l)

all: build

build:
	@echo Maximum line buffer size: $(MLBS)
	gcc -D MAX_LINE_BUFFER_SIZE=$(MLBS) -D WORDS_WORD_COUNT=$(WWC) main.c
debug:
	gcc -g -D MAX_LINE_BUFFER_SIZE=$(MLBS) -D WORDS_WORD_COUNT=$(WWC) main.c
	gdb a.out
run: build
	./a.out
