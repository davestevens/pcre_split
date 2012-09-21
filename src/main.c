#include <stdio.h>
#include "pcre_split.h"

int main(void)
{
	printf("\nTest 1\n");
	{
		split_t *test_1;
		char *regex = "\\d+";
		char *string = "hello1world22this333is4444a5555test666666.";
		/* Pass RegEx and string as char pointers */
		/* This example splits at multiple 0-9 */
		test_1 = pcre_split(regex, string);
		pcre_split_print(test_1);
		pcre_split_free(test_1);
	}

	printf("\nTest 2\n");
	{
		split_t *test_2;
		char *regex = "%[\\+#-]?(\\d+|\\*)?\\.?\\d*([hlLzjt]|[hl]{2})?([csuxXfFeEpgGdionz])";
		char *string = "printf(\"%04x\\n\", variable);";
		/* Pass RegEx and string as char pointers */
		/* This example splits at valid printf format variables */
		test_2 = pcre_split(regex, string);
		pcre_split_print(test_2);
		pcre_split_free(test_2);
	}
	return 0;
}
