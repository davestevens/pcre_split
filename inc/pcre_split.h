#ifndef __GUARD_PCRE_SPLIT_H
#define __GUARD_PCRE_SPLIT_H

/*
 */

#include <stdio.h>
#include <string.h>
#include <pcre.h>

typedef struct split_t {
	char *string;
	char *match;
	struct split_t *next;
} split_t;

split_t *pcre_split(char *, char *);
int pcre_split_free(split_t *);
unsigned int pcre_split_print(split_t *);

#endif
