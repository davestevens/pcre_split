#pcre_split#

Implementation of perl split() command in C using pcre.

perl split - http://perldoc.perl.org/functions/split.html
pcre - http://www.pcre.org/

##Compile##
```
Make
```
of
```
gcc -Wall -Wextra -pedantic -lpcre src/main.c src/pcre_split.c -Iinc -o PCRE_SPLIT
```

src/main.c contains a  main function which will run the split command with a couple of examples.

##Usage##
```C
#include "pcre_split.h"
```

```C
split_t *pcre_split(char *regex, char *string);

```
Provided pointes Regular Expression and a string to search the pcre_split() function returns a pointer to a linked list of split_t structures. These structures contain pointers to a string, match and pointer to following matches. Where *string is the portion of the provided string before any found match, *match is the section of the provided string which matched the provided regular expression and next points to the following split_t structure containing the remained of the data.
See the pcre_split_print() function for an example of accessing the split_t data.

```C
int pcre_split_free(split_t *pcre_split);
```
Frees the memory alloceted during the creation of the pcre_split.


##Dependencies##
Mac - download and install pcre from the link above
Ubuntu - I had issues with libraries not being found when installing from source. Use 'apt-get install libpcre3 libpcre3-dev' to install.
