#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int is_correct_bitmask(uint32_t bitmask) {
	uint32_t bit = 1;
	int is_one = bitmask & bit;
	for (int i = 0; i < 32; i++, bit <<= 1) {
		if (bitmask & bit) {
			is_one = 1;
		}
		else if (is_one) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("USAGE: ./is_correct_bitmask <32bit number[s]>\n");
	}
	for (int i = 1; i < argc; i++) {
		int num = atoi(argv[i]);
		printf("result for %d: %s\n", num, is_correct_bitmask((uint32_t)num) ? "true" : "false");
	}
	return 0;
}