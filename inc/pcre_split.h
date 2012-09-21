#ifndef __GUARD_PCRE_SPLIT_H
#define __GUARD_PCRE_SPLIT_H

/*
 */

#include <stdio.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30

typedef struct split_t {
	char *string;
	char *match;
	struct split_t *next;
} split_t;

typedef struct split_t_internal {
	char *string;
	char *match;
	unsigned int back_test;
} split_t_internal;

split_t *pcre_split(char *, char *);
split_t_internal *pcre_split_internal(pcre *, char *);
int pcre_split_free(split_t *);
unsigned int pcre_split_print(split_t *);

#endif
