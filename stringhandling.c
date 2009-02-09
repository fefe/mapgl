
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strReplace(char *sLine, char s, char d) {
	//Replace every occurence of s in sLine to d
	int l=strlen(sLine);
	int i;
	for (i=0; i<l; i++) {
		if (sLine[i]==s) {
			sLine[i]=d;
		}
	}
}

char *sGetLine (FILE *pFile) {
	char buffer[128]; /* Buffer for partial lines */
	char *result = NULL; /* Buffer for the complete line */
	size_t size = 0;	 /* Amount of memory assigned to result */

	/* In the average case, this should only run once */
	while (fgets(buffer, sizeof buffer, pFile) != NULL) {
		size_t len = strlen(buffer);
		char *save = realloc(result, size + len + 1);

		/* If allocation fails, take what we've got */
		if (save == NULL)
			break;

		/* Update the result buffer */
		strcpy(save + size, buffer);
		result = save;
		size += len;

		/* Finish up if we found a newline */
		if (result[size - 1] == '\n') {
			result[size - 1] = '\0';
			break;
		}
	}
	
	return result;
}

#define DEBUG 1

void debug(char *info) {
#ifdef DEBUG
	printf("<<<debug>>> %s\n", info);
#endif /* DEBUG */
}

void debugi(char *info, int i) {
#ifdef DEBUG
	printf("%s%d", info, i);
#endif /* DEBUG */
}

void debugf(char *info, float f) {
#ifdef DEBUG
	printf("%s%f", info, f);
#endif /* DEBUG */
}
