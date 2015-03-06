#include "strtonum.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM "23230002"

int main(void) {
	long long res = 0;
	const char *err = NULL;

	res = strtonum(NUM, 0, 1024 * 1024 * 1024, &err);

	printf("%s -> %lld (%s)\n", NUM, res, err ? err : "");

	return 0;
}
