#ifndef PDEBUG_H_
#define PDEBUG_H_	1

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define DIE_DEBUG 1

#ifdef DIE_DEBUG
    #define PWARNING(call_description, args...)             \
        do {                                                \
            fprintf(stderr, "(%s, %d): WARNING "            \
                            call_description "\n",          \
                            __FILE__, __LINE__, ## args);   \
            fflush(stderr);                                 \
        } while(0)

    #define PERROR(call_description, args...)               \
        do {                                                \
            fprintf(stderr, "(%s, %d): ERROR "              \
                            call_description "\n",          \
                            __FILE__, __LINE__, ## args);   \
            fflush(stderr);                                 \
            abort();                                        \
        } while(0)

#else

    #define PWARNING(call_description, args...)
    #define PERROR(call_description, args...)

#endif


#endif
