#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void print_str(
        char           *str     ,
        int             len
) {
        for (int i = 0; i < len; ++i) {
                printf("'%c'  ", str[i]);
        }
        printf("\n");
}

// Doing this taught me that this is apparently the 'correct' syntax for this.
// Doesn't *really* make a difference but still interesting to learn!
int main(void) {
        int len = 6;
        char *str = calloc(len, sizeof(char));
        memcpy(str, "hello", len);

        print_str(str, len);

        // Qualifiers discarded warning.
        fun5(&str, len - 1);

        print_str(str, len);

        free(str);

        return 0;
}
