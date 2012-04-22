#ifndef PDEBUG_H_
#define PDEBUG_H_	1

#include <stdio.h>
#include <stdlib.h>

#define DIE(assertion, call_description)    \
    do {                                    \
        if (assertion) {                    \
            fprintf(stderr, "(%s, %d): "    \
            call_description "\n",          \
                    __FILE__, __LINE__);    \
            fflush(stderr);                 \
            abort();                        \
        }                                   \
    } while(0)

/* DIE_CONT will not halt program execution */
#define DIE_CONT(assertion, call_description)   \
    do {                                        \
        if (assertion) {                        \
            fprintf(stderr, "(%s, %d): "        \
            call_description "\n",              \
                    __FILE__, __LINE__);        \
            fflush(stderr);                     \
        }                                       \
    } while(0)

#endif
