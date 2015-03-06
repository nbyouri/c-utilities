#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <humanize_number.h>

/*
 * NOTES:
 *
 * before patch, it would not copy the string into the buffer with GETSCALE
 *               and it would segfault when given a NULL buffer.
 *
 * after patch,  it copies the humanized number into the buffer when GETSCALE or AUTOSCALE is
 *               set if the buffer is not null. suffix can be NULL.
 *
 *               TODO:
 *               errno never set.
 *
 */
#define H_BUF 6

int main(void) {
        char readable_number1[H_BUF];
        char readable_number2[H_BUF];
        char readable_number3[H_BUF];
        char readable_number4[H_BUF];
        char readable_number5[H_BUF];
        char readable_number6[H_BUF];
        char readable_number7[H_BUF];
        int64_t scary_number = 2097152;

        /*
         * TEST 1
         * GETSCALE and suffix
         * return: 2
         */
        printf("scary number: %ld\n\n", scary_number);
        printf("test1 : humanize_number(readable_number, H_BUF, scary_number, \"M\",\n"
                        "\tHN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        int scale = humanize_number(readable_number1, H_BUF, scary_number, "M",
                        HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);

        printf("readable_number: %s\n", readable_number1);
        printf("scale : %d\n", scale);


        /*
         * TEST 2
         * AUTOSCALE option
         * return: 5
         */
        printf("\ntest2 : humanize_number(readable_number, H_BUF, scary_number, \"\",\n"
                        "\tHN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        int num_chars = humanize_number(readable_number2, H_BUF, scary_number, "",
                        HN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("nicey number: %s\n", readable_number2);
        printf("num of chars in buf : %d\n", num_chars);

        /*
         * TEST 3
         * GETSCALE option
         * return: 1
         */
        printf("\ntest3 : humanize_number(readable_number, H_BUF, scary_number, \"\",\n"
                        "\tHN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        scale = humanize_number(readable_number3, H_BUF, scary_number, "",
                        HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("nicey number: %s\n", readable_number3);
        printf("scale : %d\n", scale);

        /*
         * TEST 4
         * NULL buffer
         * return: 2
         */
        printf("\ntest4 : humanize_number(NULL, H_BUF, scary_number, \"k\",\n"
                        "\tHN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        scale = humanize_number(NULL, H_BUF, scary_number, "k",
                        HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("scale : %d\n", scale);

        /*
         * TEST 5
         * AUTOSCALE + GETSCALE.
         * return: 2
         */
        printf("\ntest5 : humanize_number(readable_number, H_BUF, scary_number, \"M\",\n"
                        "\tHN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        scale = humanize_number(readable_number4, H_BUF, scary_number, "M",
                        HN_AUTOSCALE | HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("nicey number: %s\n", readable_number4);
        printf("scale : %d\n", scale);

        /*
         * TEST 6
         * suffix is NULL.
         * return: 5
         */
        printf("\ntest6 : humanize_number(readable_number, H_BUF, scary_number, NULL,\n"
                        "\tHN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        num_chars = humanize_number(readable_number5, H_BUF, scary_number, NULL,
                        HN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("nicey number: %s\n", readable_number5);
        printf("num of chars in buffer : %d\n", num_chars);

        /*
         * TEST 7
         * suffix is NULL and GETSCALE
         * return: -1
         */
        strlcpy(readable_number6, "empty\0", H_BUF);
        printf("\ntest7 : humanize_number(readable_number, H_BUF, scary_number, NULL,\n"
                        "\tHN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        int ret = humanize_number(readable_number6, H_BUF, scary_number, NULL,
                        HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("nicey number: %s\n", readable_number6);
        printf("ret: %d\n", ret);

        /*
         * TEST 8
         * suffix is NULL buffer is NULL
         * return: -1
         */
        printf("\ntest8 : humanize_number(NULL, H_BUF, scary_number, NULL,\n"
                        "\tHN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        ret = humanize_number(NULL, H_BUF, scary_number, NULL,
                        HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("ret: %d\n", ret);

        /*
         * TEST 9
         * scale = 0
         * return: -1
         */
        printf("\ntest9 : humanize_number(readable_number7, H_BUF, scary_number, \"\",\n"
                        "\t0, HN_DECIMAL | HN_NOSPACE | HN_B);\n");
        ret = humanize_number(readable_number7, H_BUF, scary_number, "k",
                        HN_AUTOSCALE | HN_GETSCALE, HN_DECIMAL | HN_NOSPACE | HN_B);
        printf("ret: %d\n", ret);
        printf("num : %s\n", readable_number7);
        return 0;
}
