#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uncompress_file(char* filename);
void print_populated(char ch, int times);

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("wunzip: file1 [file2 ...]\n");
		return 1;
	}
	for (int i=1; i<argc; i++)
		uncompress_file(argv[i]);
	return 0;
}

void uncompress_file(char* filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("connot open file\n");
		exit(1);
	}

	int count;
	char ch;

	while((fread(&count, 4, 1, fp)) != 0) {
		fread(&ch, 1, 1, fp);
		print_populated(ch, count);
	}
	fclose(fp);
}

void print_populated(char ch, int times)
{
	char str[times+1];
	memset(str, ch, times);
	str[times] = 0;
	printf("%s", str);
}
