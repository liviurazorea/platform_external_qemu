#ifndef PDEBUG_H_
#define PDEBUG_H_	1

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define DIE_DEBUG 1

#ifdef DIE_DEBUG

    /* DIE_CONT will not halt program execution */
    #define DIE_CONT(assertion, call_description, args...)  \
        do {                                                \
            if (assertion) {                                \
                fprintf(stderr, "(%s, %d): "                \
                call_description "\n",                      \
                        __FILE__, __LINE__, ## args);       \
                fflush(stderr);                             \
            }                                               \
        } while(0)

    /* DIE will halt program execution */
    #define DIE(assertion, call_description, args...)       \
        do {                                                \
            DIE_CONT(assertion, call_description, ## args); \
            if (assertion) {                                \
                abort();                                    \
            }                                               \
        } while(0)

    #define PRINT_TRACE()                                   \
        do {                                                \
            void *array[20];                                \
            size_t size, i;                                 \
            char **strings;                                 \
                                                            \
            size = backtrace(array, 20);                    \
            strings = backtrace_symbols(array, size);       \
            if (20 == size) {                               \
                DIE(1, "ERR: the call chain is too large to be represented");   \
            }                                               \
                                                            \
            for (i = 0; i < size; i++) {                    \
                DIE_CONT(1,"bt: [%d]  %s", i, strings[i]);  \
            }                                               \
            fprintf(stderr, "-- end of backtrace ---\n");           \
        } while(0)

#else

    #define DIE(assertion, call_description)
    #define DIE_CONT(assertion, call_description)
    #define PRINT_TRACE()

#endif

#define PERROR()    DIE(1, "ERR")

#endif
