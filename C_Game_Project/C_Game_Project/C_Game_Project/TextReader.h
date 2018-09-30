#include "Header.h"



int F_ReadFromText(char* url) {
	errno_t err;
	FILE *fp;
	char str[maxchar];
	char* filename = url;

	err = fopen_s(&fp, filename, "r");
	if (err != NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}
	while (fgets(str, maxchar, fp) != NULL)
		printf("%s", str);
	fclose(fp);
	return 0;
}