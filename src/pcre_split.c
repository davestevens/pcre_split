#include "pcre_split.h"

/* initialise the regex */
int pcre_split(char *pattern, char *string, struct split_t *split) {
  pcre *re;
  const char *error;
  int erroffset;
  int ret = 0;

  printf("pattern: %s\n", pattern);
  printf("string : %s\n", string);

  /* setup regex */
  re = pcre_compile(
		    pattern,
		    0,
		    &error,
		    &erroffset,
		    NULL);

  /* check if compilation was successful */
  if(re == NULL) {
    printf("Error: PCRE compilation failed at offset %d: %s\n", erroffset, error);
    return -1;
  }

  /* loop until there are no more matches (or an error) */
  do {
    ret = pcre_split_int(re, string, split);
    switch(ret) {
    case -1:
      printf("Error\n");
      break;
      /*case 0:
      printf("No more matches\n");
      printf("split (1): %p\n", (void *)split);
      break;*/
    default:
      /*printf("lets go round again\n");*/
      if(split->next != NULL)
	split = split->next;
      /*printf("split (1): %p\n", (void *)split);*/
      if(split->back != NULL) {
	/*printf("BBBBBAAAAACCCCK: %s\n", split->back);*/
	string = split->back;
      }
      break;
    }
  } while(ret > 0);

  pcre_free(re);

  return 0;
}

int pcre_split_int(pcre *re, char *string, struct split_t *split) {

  int rc;
  int ovector[OVECCOUNT];
  int length;
  char *front, *back, *match;

  /*printf("pcre_split_int; %s\n", string);*/
  length = (int)strlen(string);


  rc = pcre_exec(
		 re,
		 NULL,
		 string,
		 length,
		 0,
		 0,
		 ovector,
		 OVECCOUNT);

  /* check for matches */
  if(rc < 0) {
    switch(rc) {
    case PCRE_ERROR_NOMATCH:
      /*printf("No Match\n");*/
      if(split->string != NULL) {
	/*printf("not null\n");*/
	split->next = calloc(sizeof(struct split_t), 1);
	split = split->next;
      }
      split->string = string;
      split->match = NULL;
      split->back = NULL;
      split->next = NULL;
      /*printf("split->string: %s\n", split->string);
	printf("split: %p\n", (void *)split);*/
      return 0;
      break;
    default:
      printf("Error: Matching error: %d\n", rc);
      return -1;
      break;
    }
    pcre_free(re);
  }

  /* check if output vector was large enough */
  if(rc == 0) {
    rc = OVECCOUNT/3;
    printf("Warning: ovector only has room for %d captured substrings\n", rc-1);
  }

  front = malloc(sizeof(char) * (ovector[0] + 1));
  /*printf("front size: %d\n", ovector[0]);*/
  strncpy(front, string, ovector[0]);

  match = malloc(sizeof(char) * ((ovector[1] - ovector[0]) + 1));
  /*printf("match szie: %d\n", (ovector[1] - ovector[0]));*/
  strncpy(match, (char *)(string + ovector[0]), (ovector[1] - ovector[0]));

  back = malloc(sizeof(char) * ((length - ovector[1]) + 1));
  /*printf("back size: %d\n", (length - ovector[1]));*/
  strncpy(back, (char *)(string + ovector[1]), (length - ovector[1]));

  /*printf("front: %s\n", front);
  printf("back : %s\n", back);
  printf("match: %s\n", match);*/

  if(split->string != NULL) {
    /*printf("not null\n");*/
    split->next = calloc(sizeof(struct split_t), 1);
    split = split->next;
  }
  split->string = front;
  split->match = match;
  split->back = back;
  /*printf("split->string: %s\n", split->string);
    printf("split: %p\n", (void *)split);*/

  return 1;
}

int pcre_split_free(struct split_t *split) {
  struct split_t *mine;

  while(split->next != NULL) {
    mine = split;
    split = split->next;

    free(mine->string);
    free(mine->match);
    free(mine->back);
    free(mine);
  }
  return 0;
}

int pcre_split_print(struct split_t *split) {

  if(split == NULL)
    printf("Error: Nothing to print\n");
  else {
    do {
      printf("string: %s\n", split->string);
      printf("match : %s\n", split->match);
    } while((split = split->next) != NULL);
  }

  return 0;
}
