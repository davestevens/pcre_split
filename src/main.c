/* quick hack to get a split command sort of working
 */

#include <stdio.h>
#include "pcre_split.h"

int main(void) {
  split_t *mine;
  /*  mine = pcre_split("(\\d+)", "hello123world333thisx2is1a616test");
  pcre_split_print(mine);
  pcre_split_free(mine);*/

  mine = pcre_split("(\\.)", "192.168.0.1");
  pcre_split_print(mine);
  pcre_split_free(mine);

  return 0;
}
