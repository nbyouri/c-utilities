#include <string.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

void dumpArray(char **ptr, ssize_t size);
char **stringToArray(char *string,char *delims);
void *cleanPtr(char **ptr,unsigned int *count);
void ReadFD(int *fd);
char *readinput(const char *prompt);
#if !defined(__NetBSD__)
int growArray(void *ptr,size_t num,size_t size);
#endif
char *strjoin(const char *separ,char **array);
