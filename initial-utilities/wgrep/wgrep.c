#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define READ_FILE(file) \
	while (fgets(buff, 256, (file)) != NULL) { \
		if (match_exp(buff, pattern)) { \
			printf("%s", buff); \
		} \
	}

void grep_single_file(char* filename, char* pattern);
void grep_stdin(char* pattern);
bool match_exp(char* str, char* pattern);

int main(int argc, char** argv)
{
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	else if (argc == 2)
		grep_stdin(argv[1]);

	for (int i=2; i<argc; i++)
		grep_single_file(argv[i], argv[1]);

	return 0;
}

void grep_single_file(char* filename, char* pattern)
{
	char buff[256];
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("wgrep: cannot open file\n");
		exit(1);
	}
	READ_FILE(fp);
	fclose(fp);
}

void grep_stdin(char* pattern)
{
	char buff[256];
	READ_FILE(stdin);
}

bool match_exp(char* str, char* pattern)
{
	int str_len = strnlen(str, 256);
	int pattern_len = strlen(pattern);

	if (str_len < pattern_len) {
		return false;
	}
	for (int i=0; i<str_len - pattern_len; i++) {
		if (strncmp(str + i, pattern, pattern_len) == 0) {
			return true;
		}
	}
	return false;
}
