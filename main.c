#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_BUFFER_SIZE 1000
#define MAX_WORD_COUNT 6

int main() {
	FILE *words_file = fopen("words.txt", "r");
	if (!words_file) {
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	char **chunk = malloc(MAX_WORD_COUNT * sizeof(char *));
	int i = 0;
	int num_char = 0;
	char line_buffer[MAX_LINE_BUFFER_SIZE];
	while(fgets(line_buffer, sizeof(line_buffer), words_file) && i < MAX_WORD_COUNT) {
		printf("%s\n", line_buffer);
		chunk[i] = malloc(MAX_LINE_BUFFER_SIZE * sizeof(char));
		char *end_char_ptr = strchr(line_buffer, '\n');
		int end_char_pos = end_char_ptr - line_buffer;
		printf("%d\n", end_char_pos);
		num_char += end_char_pos + 1;// +1 for \n characters
		strncpy(chunk[i], line_buffer, end_char_pos);
		i++;
	}
	printf("%d", num_char);

	return 0;
}
