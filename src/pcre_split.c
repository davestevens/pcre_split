#include "pcre_split.h"

#define OVECCOUNT 30

typedef struct split_t_internal {
	char *string;
	char *match;
	unsigned int length;
} split_t_internal;

split_t_internal *pcre_split_internal(pcre *, char *);

/* Initialise the RegEx */
split_t *pcre_split(char *pattern, char *string)
{
	pcre *re;
	const char *error;
	int erroffset;
	split_t_internal *si;
	split_t *curr = NULL;
	split_t *head = NULL;

	/*
	  Make a local copy of pattern and string
	*/
	char *s = string;

	/*
	  Setup RegEx
	*/
	re = pcre_compile(pattern, 0, &error, &erroffset, NULL);

	/*
	  Check if compilation was successful
	*/
	if(re == NULL) {
		printf("Error: PCRE compilation failed at offset %d: %s\n", erroffset, error);
		return (split_t *)NULL;
	}

	/*
	  Loop thorough string
	*/
	do {
		if(head == NULL) {
			curr = head = (split_t *)calloc(sizeof(split_t), 1);
		}
		else {
			curr->next = (split_t *)calloc(sizeof(split_t), 1);
			curr = curr->next;
		}
		if(!curr) {
			fprintf(stderr, "Error allocating memory for split_t\n");
			return NULL;
		}

		/* Return first occurence of match of RegEx */
		si = pcre_split_internal(re, s);

		/* Copy pointers of string and match */
		curr->string = si->string;
		curr->match = si->match;

		/* Increment string pointer to skip previous match */
		s += si->length;

		free(si);
	} while(curr->match);

	/*
	  Free locally allocated memory
	 */
	pcre_free(re);
	return head;
}

split_t_internal *pcre_split_internal(pcre *re, char *string)
{

	int rc;
	int ovector[OVECCOUNT];
	int length;
	split_t_internal *s = (split_t_internal *)calloc(1, sizeof(split_t_internal));

	length = (int)strlen(string);

	rc = pcre_exec(re, NULL, string, length, 0, 0, ovector, OVECCOUNT);

	/* check for matches */
	if(rc < 0) {
		switch(rc) {
			case PCRE_ERROR_NOMATCH:
				s->string = (char *)calloc(strlen(string) + 1, sizeof(char));
				strncpy(s->string, string, strlen(string));
				s->match = NULL;
				return s;
				break;
			default:
				printf("Error: Matching error: %d\n", rc);
				return (split_t_internal *)NULL;
				break;
		}
	}

	/* check if output vector was large enough */
	if(rc == 0) {
		rc = OVECCOUNT/3;
		fprintf(stderr, "Warning: ovector only has room for %d captured substrings\n", rc-1);
	}

	s->string = calloc(sizeof(char) * (ovector[0] + 1), 1);
	strncpy(s->string, string, ovector[0]);

	s->match = calloc(sizeof(char) * ((ovector[1] - ovector[0]) + 1), 1);
	strncpy(s->match, (char *)(string + ovector[0]), (ovector[1] - ovector[0]));

	s->length = ovector[1];

	return (split_t_internal *)s;
}

int pcre_split_free(split_t *split)
{
	if(split == NULL) {
		/* Nothing to free */
		return -1;
	}
	else {
		split_t *mine = NULL;
		do {
			mine = split;

			if(mine->string) {
				free(mine->string);
			}
			if(mine->match) {
				free(mine->match);
			}

			split = split->next;
			free(mine);
		} while(split);
		
	}
	return 0;
}

unsigned int pcre_split_print(split_t *split)
{
	if(split == NULL) {
		printf("Error: Nothing to print\n");
		return 0;
	}
	else {
		unsigned int count = 0;
		do {
			if(split->string) {
				printf("string: %s\n", split->string);
			}
			if(split->match) {
				printf("match : %s\n", split->match);
			}
			++count;
			split = split->next;
		} while(split);

		return count;
	}
	return 0;
}
