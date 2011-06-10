#ifndef _GUARD_PCRE_SPLIT
#define _GUARD_PCRE_SPLIT

/*
 */

#include <stdio.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30

struct split_t {
  char *string;
  char *match;
  char *back;
  struct split_t *next;
};

int pcre_split(char *, char *, struct split_t *);
int pcre_split_int(pcre *, char *, struct split_t *);
int pcre_split_free(struct split_t *);
int pcre_split_print(struct split_t *);

#endif
