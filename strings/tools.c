#include "tools.h"
#include <err.h>

/*
 * Join a number of strings to form one long string
 * separated by the optional separator.
 *
 * param: array : a NULL terminated array of strings to join
 *        separ : a separator or NULL.
 */
char *strjoin(const char *separ, char **array) {
        /* get array size */
        size_t siz = 0;

        /* get string count */
        while (array[siz++] != NULL);

        /* allocate string */
        char *str = NULL;
        str = malloc(siz * BUFSIZ);
        if (str == NULL)
                err(1, "malloc failed :");

        /* copy first string entry */
        strlcpy(str, array[0], BUFSIZ);

        /* concatenate the rest */
        for (size_t i = 1; array[i] != NULL && strlen(array[i]) > 0; i++) {
                if (separ != NULL) {
                        strlcat(str, separ, BUFSIZ);
                }

                strlcat(str, array[i], BUFSIZ);
        }

        str[strlen(str)] = '\0';

        return str;

}

/*
 * Safely allocate memory for arrays
 */
#ifndef __NetBSD__
int growArray(void *ptr, size_t num, size_t size) {
        int saved_errno, result;
        void *optr;
        void *nptr;

        memcpy(&optr, ptr, sizeof(ptr));
        saved_errno = errno;
        if (num == 0 || size == 0) {
                free(optr);
                nptr = NULL;
                memcpy(ptr, &nptr, sizeof(ptr));
                errno = saved_errno;
                return 0;
        }
        if ((num >= 65535 || size >= 65535) && num > SIZE_MAX / size) {
                return EOVERFLOW;
        }

        nptr = realloc(optr, num * size);
        if (nptr == NULL) {
                result = errno;
        } else {
                result = 0;
                memcpy(ptr, &nptr, sizeof(ptr));
        }
        errno = saved_errno;
        return result;
}
#else
#define growArray reallocarr
#endif
// read string from user
char *readinput(const char *prompt) {
	char line[BUFSIZ];

	printf("%s", prompt);

	fgets(line, sizeof(line), stdin);
	if (strlen(line) > 0) {
		// don't do anything if user just presses return
		if (line[0] == '\n') {
			return NULL;
		}
		// shave off the \n at the end
		line[strlen(line) - 1] = '\0';
		// copy the string safely
		char *string = NULL;
		string = strndup(line, BUFSIZ);
		return string;
	}
	return NULL;
}

// procedure to read lines from file descriptor
void ReadFD(int *fd) {
	char buf[BUFSIZ];
	FILE *file;
	file = fdopen(*fd, "r");
	if (file == NULL) {
		perror("Failed to fdopen\n");
		exit(EXIT_FAILURE);
	} else {
		while (!feof(file) &&
		    !ferror(file) &&
		    fgets(buf, sizeof(buf), file) != NULL) {
			printf("%s", buf);
		}
		if (fclose(file) == EOF) {
			perror("Failed to fclose\n");
		}
	}
}
// clean array of strings
// can be used with char * as well,
// just cast it. ex. cleanPtr((char **)str, NULL)
void *cleanPtr(char **ptr, unsigned int *count) {
	if ((count != NULL) && (*count > 0)) {
		unsigned int i;
		for (i = 0; i < *count; i++) {
			free(ptr[i]);
			ptr[i] = NULL;
		}
		*count = 0;
	}
	free(ptr);
	ptr = NULL;
	return ptr;
}

// convert string to array of strings separated by delimiters
char **stringToArray(char *string, char *delims) {
	char    *token;
	char    **array = NULL;
	unsigned int    i = 0;

	// separate the string into tokens based on the delimiters
	// and store these tokens in an array. token is set to NULL
	// when strsep is done.
	while ((token = strsep(&string, delims)) != NULL) {
		// grow array at index + 1
		int ret = growArray(array, i + 1, sizeof(char *));
		if (ret) {
			errc(1, ret, "Failed to reallocate array at index %u\n", i);
		} else {
			// allocate string in array
			ret = growArray(array[i], BUFSIZ, sizeof(char));
			if (ret) {
				errc(1, ret, "Failed to malloc array[%u]\n", i);
			} else {
				// don't copy an empty string
				if (strlen(token) > 0) {
					strlcpy(array[i], token, BUFSIZ);
					i++;
				}
			}
		}
	}

	// make sure the array of string end with NULL
	array[i] = NULL;

	// debug array content
	dumpArray(array, i);

	return array;
}

/* dumps the content of a string array with given size
 * should work with char * with casting to char ** and
 * setting the size to 0.
 */
void dumpArray(char **ptr, ssize_t size) {
        if (ptr == NULL) {
                printf("Can't dump NULL pointer\n");
                return;
        }

        unsigned int i = 0;

        // deal with arrays of characters
        if (size == 0) {
                if (*ptr == NULL) {
                        printf("NULL string.\n");
                } else {
                        size_t strSize = strlen((char *)ptr);
                        if (strSize > 0) {
                                printf("%s[%zu] = {\n", (char *)ptr, strSize);
                                for (i = 0; i < strSize; i++) {
                                        printf("\t%c, // (id. %u)\n",
                                            *((char *)ptr + i), i);
                                }
                        } else {
                                printf("Can't dump empty array\n");
                        }
                }
                printf("};\n");
                return;
        }

        // deal with arrays of arrays of characters
        printf("args[%zu] = {\n", size + 1);

        // loop through array elements
        if (size == -1) {
                for (i = 0; ptr[i] != NULL; i++) {
                        printf("\t");
                        printf("%s\n", ptr[i]);
                }
        } else {
                for (i = 0; i <= size; i++) {
                        printf("\t");
                        if (ptr[i] == NULL) {
                                printf("NULL,\n");
                        } else {
                                printf("%s, // (%zu)\n", ptr[i], strlen(ptr[i]));
                        }
                }
        }
        printf("};\n");
}
