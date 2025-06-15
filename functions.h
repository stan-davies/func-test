#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void fun1(
        char           *str     ,
        int             len
);

void fun2(
        const char     *str     ,
        int             len
);

void fun3(
        char           *const str      ,
        int             len
);

void fun4(
        const char     *const str       ,
        int             len
);

void fun5(
        const char    **const str       ,
        int             len
);

/* `    const char    **const const str `       would give:
        warning: duplicate const declaration specifier
*/

#endif
