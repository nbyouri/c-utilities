#include <stdio.h>
#include "xmalloc.h"
#include <stdlib.h>

int main(void) {
    int nb = 100;
    char * string = NULL;

    // no need to check if destination is NULL, x* functions
    // do it for us and exit if so.
    xasprintf(&string, "%d", nb);

    printf("%s\n", string);

    // test error case
    char * stemp = xmalloc(0);
    char * stemp2 = xcalloc(0, sizeof(char));

    free(stemp);
    free(stemp2);
    free(string);
    string = NULL;
    return 0;
}
