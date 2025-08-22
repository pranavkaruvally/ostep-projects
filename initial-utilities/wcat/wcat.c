#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

void read_single_file(char* filename);

int main(int argc, char** argv)
{
	for (int i=1; i<argc; i++) {
		read_single_file(argv[i]);
	}
	return 0;
}

void read_single_file(char* filename)
{
	char buff[256];

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("wcat: cannot open file\n");
		exit(1);
	}
	while(true) {
		if(fgets(buff, 256, fp) == NULL) {
			break;
		}
		printf("%s", buff);
	}
	fclose(fp);
}
