#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_VERSION "0.1.0"
#ifndef PROGRAM_NAME
#define PROGRAM_NAME    "rot"
#endif

int main(int argc, char* argv[]) {
	const char* argv0 = argv > 0 ? argv[0] : PROGRAM_NAME;

	if (
		argc < 2 ||
		strcmp(argv[1], "--help") == 0 ||
		strcmp(argv[1], "-h") == 0
	) {
		//

		return 0;
	}

	if (
		strcmp(argv[1], "--version") == 0 ||
		strcmp(argv[1], "-v") == 0
	) {
		//

		return 0;
	}

	char* str_end = NULL;
	int shift = strtol(argv[1], &str_end, 10);

	if (str_end == argv[1]) {
		fprintf(stderr, "%s: invalid shift value\n", argv0);
		return 1;
	}

	//

	return 0;
}
