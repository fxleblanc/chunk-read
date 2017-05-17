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
	printf("Number of words: %d\n", CHUNK_WORD_COUNT);

	struct chunk *ch = malloc(sizeof(struct chunk *));
	ch->start = 0;
	while(ch->start >= 0) {
		get_chunk(words_file, ch);
		printf("Printing chunk...\n");
		print_chunk(ch->strings);
	}

	return 0;
}

void get_chunk(FILE *file, struct chunk *ch) {
	ch->strings = malloc(CHUNK_WORD_COUNT * sizeof(char *));
	int i = 0;
	char line_buffer[MAX_LINE_BUFFER_SIZE];
	char *end_char_ptr = malloc(sizeof(char));
	int end_char_pos = 0;
	printf("Starting at %d\n", ch->start);
	fseek(file, ch->start, SEEK_SET);
	while(fgets(line_buffer, sizeof(line_buffer), file) && i < CHUNK_WORD_COUNT) {
		ch->strings[i] = malloc(MAX_LINE_BUFFER_SIZE * sizeof(char));
		end_char_ptr = strchr(line_buffer, '\n');
		if(end_char_ptr == NULL) {
			end_char_pos = strlen(line_buffer);
			ch->start = -1;
			strncpy(ch->strings[i], line_buffer, end_char_pos);
		} else {
			end_char_pos = end_char_ptr - line_buffer;
			ch->start += end_char_pos + 1; // +1 for \n character
			strncpy(ch->strings[i], line_buffer, end_char_pos);
		}
		i++;
	}
}

void print_chunk(char **strings) {
	for(int i = 0;i < CHUNK_WORD_COUNT;i++) {
		printf("%s\n", strings[i]);
	}
}
