/* quick hack to get a split command sort of working
 */

#include <stdio.h>
#include "pcre_split.h"

int main(void) {
  struct split_t *mine = calloc(sizeof(struct split_t), 1);

  /* testing the input */
  if(pcre_split("(\\d+)", "hello123world333thisx2is1a616test", mine) == -1)
    printf("Error\n");
  else {
    pcre_split_print(mine);
    pcre_split_free(mine);
  }

  mine = calloc(sizeof(struct split_t), 1);
  if(pcre_split("(\\.)", "192.168.0.1", mine) == -1)
    printf("Error\n");
  else {
    pcre_split_print(mine);
    pcre_split_free(mine);
  }

  return 0;
}
