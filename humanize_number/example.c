#include <stdio.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include "humanize_number.h"

/*
 * Use a small buffer or it's 
 * not going to work. 
 */
#define H_BUF 6

int main(void) {
    char readable_number[H_BUF];
    int64_t scary_number = 123201230103;
    
    // Make the big number more readable by humans
    humanize_number(readable_number, H_BUF, scary_number, "",
            HN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);

    printf("nice number : %s\n", readable_number);

    // make the number scary again:
    int64_t number = 0;
    dehumanize_number(readable_number, &number);
    printf("scary number : %lld\n", number);
}
