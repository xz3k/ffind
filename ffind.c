#include "ffind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stddef.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("%s: No pattern specified.\n", argv[0]);
		return 0;
	}

	struct stat buffer;
	if (stat(DB_PATH, &buffer) != 0) {
		fprintf(stderr, "%s: No ffind database found! Please generate one using ffupdate.\n", argv[0]);
		return 1;
	}

	FILE* db_fp = fopen(DB_PATH, "r");
	if (db_fp == NULL) {
		perror("fopen");
		return 1;
	}

	char* pattern = NULL;
	if (argc > 2) {
		int i;

		int bytes = 0;
		for (i = 1; i < argc; i++)
			bytes += strlen(argv[i]);

		pattern = (char*)malloc(bytes + argc);
		if (pattern == NULL) {
			fclose(db_fp);
			perror("malloc");
			return 1;
		}
		pattern[0] = '\0';

		for (i = 1; i < argc; i++) {
			strcat(pattern, argv[i]);
			if (i != argc - 1)
				strcat(pattern, " ");
		}
	}
	else
		pattern = argv[1];

	char path_buffer[MAX_PATH_SZ + 1];
	while (fgets(path_buffer, MAX_PATH_SZ, db_fp) != NULL) {
		path_buffer[strcspn(path_buffer, "\n")] = '\0';

		if (strstr(path_buffer, pattern) != NULL)
			printf("%s\n", path_buffer);
	}
	fclose(db_fp);

	if (argc > 2)
		free(pattern);

	return 0;
}
