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

struct chunk {
	int num_char;
	char **strings;
};

int main() {
	FILE *words_file = fopen("words.txt", "r");
	if (!words_file) {
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	printf("Maximum line size: %d\n", MAX_LINE_BUFFER_SIZE);
	printf("Number of words: %d\n", WORDS_WORD_COUNT);

	struct chunk *ch = malloc(sizeof(struct chunk *));
	get_chunk(words_file, ch, 0);

	for(int i = 0;i < WORDS_WORD_COUNT;i++) {
		printf("%s\n", ch->strings[i]);
	}
	printf("Total number of characters: %d\n", ch->num_char);

	return 0;
}

void get_chunk(FILE *file, struct chunk *ch, int start) {
	char **strings = malloc(WORDS_WORD_COUNT * sizeof(char *));
	int i = 0;
	int num_char = 0;
	char line_buffer[MAX_LINE_BUFFER_SIZE];
	while(fgets(line_buffer, sizeof(line_buffer), file) && i < WORDS_WORD_COUNT) {
		strings[i] = malloc(MAX_LINE_BUFFER_SIZE * sizeof(char));
		char *end_char_ptr = strchrnul(line_buffer, '\n');
		int end_char_pos = end_char_ptr - line_buffer;
		num_char += end_char_pos + 1;// +1 for \n characters
		strncpy(strings[i], line_buffer, end_char_pos);
		i++;
	}
	ch->strings = strings;
	ch->num_char = num_char;
}
