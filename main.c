#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_LINE_BUFFER_SIZE
#define MAX_LINE_BUFFER_SIZE 0
#endif
#ifndef CHUNK_WORD_COUNT
#define CHUNK_WORD_COUNT 0
#endif
#ifndef DICT_WORD_COUNT
#define DICT_WORD_COUNT 0
#endif

struct chunk {
	char **strings;
	int start;
};

int main() {
	FILE *words_file = fopen("words.txt", "r");
	if (!words_file) {
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	printf("Maximum line size: %d\n", MAX_LINE_BUFFER_SIZE);
	printf("Number of words per chunk: %d\n", CHUNK_WORD_COUNT);

	struct chunk *ch = malloc(sizeof(struct chunk *));
	ch->start = 0;
	while(ch->start >= 0) {
		printf("Getting chunk at %d\n", ch->start);
		get_chunk(words_file, ch);
		if(ch->start != -1) {
			print_chunk(ch->strings);
		}
	}

	return 0;
}

void get_chunk(FILE *file, struct chunk *ch) {
	ch->strings = malloc(CHUNK_WORD_COUNT * sizeof(char *));
	int i = 0;
	char line_buffer[MAX_LINE_BUFFER_SIZE + 1];
	char *end_char_ptr = malloc(sizeof(char));
	int end_char_pos = 0;
	fseek(file, ch->start, SEEK_SET);
	while(i < CHUNK_WORD_COUNT) {
		if(fgets(line_buffer, sizeof(line_buffer), file)) {
			ch->strings[i] = malloc(MAX_LINE_BUFFER_SIZE * sizeof(char));
			end_char_ptr = strchr(line_buffer, '\n');
			end_char_pos = end_char_ptr - line_buffer;
			ch->start += end_char_pos + 1; // +1 for \n character
			strncpy(ch->strings[i], line_buffer, end_char_pos);
			i++;
		} else {
			ch->start = -1;
			break;
		}
	}
}

void print_chunk(char **strings) {
	for(int i = 0;i < CHUNK_WORD_COUNT;i++) {
		printf("%s\n", strings[i]);
	}
}
