#include <stdio.h>
#include <stdlib.h>

unsigned char* readpgm(char *nom, int *w, int *h) {
	char line[5];
	unsigned char *buf = NULL;
	FILE *fp = fopen(nom, "rb");

	if (fp == NULL) {
		fprintf(stderr, "fichier non trouve\n");
		return NULL;
	}

	fgets(line, 4, fp);
	if (*line == 'P' && *(line + 1) == '5') {
		int c;

		if ((c = fgetc(fp)) == '#')
			while ((c = fgetc(fp)) != '\n')
				;
		else
			ungetc(c, fp);

		fscanf(fp, "%d %d\n%d\n", w, h, &c);

		buf = malloc(sizeof(char) * *w * *h);
		if (buf == NULL) {
			fprintf(stderr, "buffer non alloue\n");
			return NULL;
		}

		fread(buf, sizeof(char), *w * *h, fp);

		printf("w=%d h=%d size=%d\n", *w, *h, *w * *h);
	} else
		fprintf(stderr, "readpgm: %s has an unsupported format\n", nom);

	fclose(fp);
	return buf;
}
