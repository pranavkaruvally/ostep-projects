#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

void reverse_file(FILE* infile, FILE* outfile);
bool is_files_same(char* infilename, char* outfilename);

struct node {
	char* str;
	struct node* prev;
};

int main(int argc, char** argv)
{
	if (argc == 1)
		reverse_file(stdin, stdout);
	else if (argc == 2) {
		FILE *infile;
		if ((infile = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			return 1;
		}
		reverse_file(infile, stdout);

		fclose(infile);
	}
	else if (argc == 3) {
		if (is_files_same(argv[1], argv[2])) {
			fprintf(stderr, "reverse: input and output file must differ\n");
			return 1;
		}
		FILE *infile, *outfile;
		if ((infile = fopen(argv[1], "r")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			return 1;
		}
		if ((outfile = fopen(argv[2], "w")) == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
			return 1;
		}
		reverse_file(infile, outfile);

		fclose(infile);
		fclose(outfile);
	}
	else {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		return 1;
	}

	return 0;
}

void reverse_file(FILE* infile, FILE* outfile)
{
	size_t bufsize = 256;
	char *buffer = malloc(bufsize);
	if (buffer == NULL) {
		fprintf(stderr, "reverse: malloc failed\n");
		exit(1);
	}
	struct node *prev = NULL;
	struct node *node;
	while (getline(&buffer, &bufsize, infile) != -1) {
		node = malloc(sizeof(struct node));
		if (node == NULL) {
			fprintf(stderr, "reverse: malloc failed\n");
			exit(1);
		}

		node->str = malloc(bufsize);
		if (node->str == NULL) {
			fprintf(stderr, "reverse: malloc failed\n");
			exit(1);
		}

		strncpy(node->str, buffer, bufsize);
		node->prev = prev;
		prev = node;
	}
	free(buffer);

	if (prev == NULL)
		exit(1);
	while (prev != NULL) {
		fprintf(outfile, "%s", prev->str);
		struct node* temp = prev->prev;
		free(prev->str);
		free(prev);
		prev = temp;
	}
}

bool is_files_same(char* infilename, char* outfilename)
{
	struct stat infilestat, outfilestat;
	if (stat(infilename, &infilestat) == -1) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", infilename);
		exit(1);
	}
	if (stat(outfilename, &outfilestat) == -1) {
		// Most likely file does not exist and hence is not the same. Have to edit once a better logic is devised
		return false;
	}
	if ((infilestat.st_dev == outfilestat.st_dev) && (infilestat.st_ino == outfilestat.st_ino))
		return true;
	return false;
}
