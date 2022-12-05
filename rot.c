#include <ctype.h>
#include <stdint.h>
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

	uint8_t bset[32] = { 0 };
	uint8_t trans[256] = {
		0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,
		16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
		32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
		64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
		80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
		96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
		128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
		144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
		192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
		224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
	};

	uint8_t buf[256] = { 0 };
	int buf_len = 0;

	for (int i = 2; i < argc; i++) {
		for (int j = 0; argv[i][j]; j++) {
			if (buf_len >= 256) {
				fprintf(stderr, "%s: shift alphabet too long\n", argv0);
				return 1;
			}

			if (argv[i][j] == 0x1b) {
				char high = argv[i][++j];
				char low = argv[i][++j];

				if (high == 0 || low == 0) {
					fprintf(stderr, "%s: unterminated escape\n", argv0);
					return 1;
				}

				if (
					(
						('0' <= high && high <= '9') ||
						('a' <= high && high <= 'f') ||
						('A' <= high && high <= 'F')
					) &&
					(
						('0' <= low && low <= '9') ||
						('a' <= low && low <= 'f') ||
						('A' <= low && low <= 'F')
					)
				) {
					buf[buf_len++] = (uint8_t) (
						((high <= '9' ? high - '0' : 10 + tolower(high) - 'a') << 4) |
						(low <= '9' ? low - '0' : 10 + tolower(low) - 'a')
					);
				} else {
					fprintf(stderr, "%s: invalid escape\n", argv0);
					return 1;
				}
			} else {
				buf[buf_len++] = argv[i][j];
			}

			uint8_t thisvalue = buf[buf_len - 1];

			if ((bset[thisvalue >> 3] >> (thisvalue & 0b111)) & 1) {
				if (isgraph(thisvalue))
					fprintf(stderr, "%s: '%c' appears twice\n", argv0, thisvalue);
				else
					fprintf(stderr, "%s: 0x%02x appears twice\n", argv0, thisvalue);

				return 1;
			}

			bset[thisvalue >> 3] |= 1 << (thisvalue & 0b111);
		}

		//

		buf_len = 0;
	}

	if (argc == 2) {
		//
	}

	//

	return 0;
}
