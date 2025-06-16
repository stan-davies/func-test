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

void print_vec(
        int            *vec     ,
        int             size
) {
        printf("(  ");
        for (int i = 0; i < size; ++i) {
                printf("%d  ", vec[i]);
        }
        printf(")\n");
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



        int *vec1 = calloc(3, sizeof(int));
        int *vec2 = calloc(3, sizeof(int));
        for (int i = 0; i < 3; ++i) {
                vec1[i] = i + 1;
                vec2[i] = 3 - i;
        }

        // This doesn't seem to kick up a ruckus but it also defeats the point.
        // I guess it is just makes errors more possible and irritating.
//        int *vec2 = vec1;

        int *vec3 = calloc(3, sizeof(int));

        fun6(vec3, vec1, vec2, 3);

        print_vec(vec1, 3);
        print_vec(vec2, 3);
        print_vec(vec3, 3);

        return 0;
}
