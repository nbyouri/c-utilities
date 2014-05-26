#include <stdio.h>
#include <xmalloc.h>
#include <stdlib.h>

int main(void) {
    int nb = 100;
    char * string = NULL;

    // no need to check, x* functions
    // do it for us!
    xasprintf(&string, "%d", nb);

    printf("%s\n", string);

    free(string);
    string = NULL;

    return 0;
}
