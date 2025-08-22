#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_files(char** files, int num_fies);

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}
	compress_files(argv, argc);
	return 0;
}

void compress_files(char** files, int num_files)
{
	int count = 0;
	char ch, prev_ch = -1;
	for (int i=1; i<num_files; i++) {
		FILE *fp = fopen(files[i], "r");
		if (fp == NULL) {
			printf("cannot open file\n");
			exit(1);
		}
		while ((ch = fgetc(fp)) != EOF) {
			if (ch == prev_ch)
				count++;
			else {
				if (prev_ch != -1) {
					fwrite(&count, sizeof(count), 1, stdout);
					fwrite(&prev_ch, sizeof(prev_ch), 1, stdout);
				}
				prev_ch = ch;
				count = 1;
			}
		}
		fclose(fp);
	}
	if (prev_ch != -1) {
		fwrite(&count, sizeof(count), 1, stdout);
		fwrite(&prev_ch, sizeof(prev_ch), 1, stdout);
	}
}
