#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_LINE_BUFFER_SIZE
#define MAX_LINE_BUFFER_SIZE 0
#endif
#ifndef WORDS_WORD_COUNT
#define WORDS_WORD_COUNT 0
#endif
#ifndef DICT_WORD_COUNT
#define DICT_WORD_COUNT 0
#endif

int main() {
	FILE *words_file = fopen("words.txt", "r");
	if (!words_file) {
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	char **chunk = malloc(WORDS_WORD_COUNT * sizeof(char *));
	printf("Maximum line size: %d\n", MAX_LINE_BUFFER_SIZE);
	printf("Number of words: %d\n", WORDS_WORD_COUNT);
	int i = 0;
	int num_char = 0;
	char line_buffer[MAX_LINE_BUFFER_SIZE];
	while(fgets(line_buffer, sizeof(line_buffer), words_file) && i < WORDS_WORD_COUNT) {
		chunk[i] = malloc(MAX_LINE_BUFFER_SIZE * sizeof(char));
		char *end_char_ptr = strchrnul(line_buffer, '\n');
		int end_char_pos = end_char_ptr - line_buffer;
		num_char += end_char_pos + 1;// +1 for \n characters
		strncpy(chunk[i], line_buffer, end_char_pos);
		i++;
	}
	for(int i = 0;i < WORDS_WORD_COUNT;i++) {
		printf("%s\n", chunk[i]);
	}
	printf("Total number of characters: %d\n", num_char);

	return 0;
}
