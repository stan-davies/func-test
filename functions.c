#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun1(
        // Pointer to a character.
        char           *str     ,
        int             len
) {
        char *backup = calloc(len, sizeof(char));
        memcpy(backup, str, len);

        for (int i = 0; i < len; ++i) {
                // Changing underlying memory makes the changes apparent for the
                // caller, even though our pointer is actually different to
                // theirs in that the pointer is passed by value (the memory
                // address is copied into a new variable).
                str[i] = backup[(len - 1) - i];
        }

        free(backup);
}

void fun2(
        // Pointer to a constant character.
        const char     *str     ,
        int             len
) {
        char *backup = calloc(len, sizeof(char));
        // `memcpy` takes `const char *src` so this checks out fine.
        memcpy(backup, str, len);

        // Qualifiers are discarded and this is allowed. =o Gives warning.
        // memcpy(str, "what!", len);

        char *flip = calloc(len + 1, sizeof(char));

        for (int i = 0; i < len; ++i) {
                /*
                        Compiler gives:
                        `       error: read-only variable is not assignable     `
                 */
                // str[i] = backup[(len - 1) - i];

                flip[i] = backup[(len - 1) - i];
        }

        // Is permitted and causes no errors but has no impact for caller.
        str = flip;
        printf("internal: %s\n", str);

        // If ^that line were preceded by a `free` then this would seem fine and
        // keep chugging along. However, the caller would find their copy of the
        // pointer unchanged, and yet it would be pointing to freed memory. As
        // such, they would pretty quickly run into errors.

        free(backup);
}

void fun3(
        // Constant pointer to a character.
        char           *const str      ,
        int             len
) {
        char *backup = calloc(len, sizeof(char));
        memcpy(backup, str, len);

        for (int i = 0; i < len; ++i) {
                // No problem here, the character is not constant.
                str[i] = backup[(len - 1) - i];
        }

        // No problem here, we are only changing the underlying memory.
        memcpy(str, "what!", len);

        char *other = calloc(len, sizeof(char));

        /*
                Compiler gives:
                `       error: cannot assign to variable `str` with 
                               const-qualified type `char *const`       `
                for each line. We cannot change the pointer itself.
         */
        // str++;
        // str = other;

        free(backup);
}

void fun4(
        // Constant pointer to constant character.
        const char     *const str       ,
        int             len
) {
        char *backup = calloc(len, sizeof(char));
        memcpy(backup, str, len);

        /*
                Compiler gives:
                `       warning: passing `const char *const` to parameter of
                                 type `void *` discards qualifiers      `
        */
        // memcpy(str, "what!", len);

        for (int i = 0; i < len; ++i) {
                /*
                        Compiler gives:
                        `       error: cannot assign to variable `str` with 
                                       const-qualified type `char *const`       `
                 */
                // str[i] = backup[(len - 1) - i];
        }

        char *other = calloc(len, sizeof(char));

        /*
                Compiler gives:
                `       error: cannot assign to variable `str` with 
                               const-qualified type `char *const`       `
         */
        // str++;
        // str = other;

        free(backup);
}

void fun5(
        // Beyond sense.
        // ... *(*const) ... gives an error. I don't even really get what this
        // is anymore.
        const char    **const str       ,
        int             len
) {
        char *backup = calloc(len, sizeof(char));
        memcpy(backup, str, len);

        // Plants seeds for a segfault when string is printed.
        // memcpy(str, "what!", len);

        for (int i = 0; i < len; ++i) {
                // `    error: read-only variable is not assignable     `
                // (*str)[i] = backup[(len - 1) - i];

                // Seems to print out... every memory location??
                // Printed out 20 characters every line for a few thousand lines
                // which tots up to tens out thousands of memory locations.
                // Presumably reading backwards from present position to the
                // start of memory. Not good!
                // str[i] = &backup[(len - 1) - i];
        }

        // error: cannot assign to...
        // str++;
        // char *other = calloc(len, sizeof(char));
        // Do note that this is not a problem of types but of CANNOT ASSIGN.
        // str = other;

        free(backup);
}
