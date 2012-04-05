#ifndef PDEBUG_H_
#define PDEBUG_H_	1

#include <stdio.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): " 			\
			call_description "\n",				\
					__FILE__, __LINE__);		\
			fflush(stderr);					\
		}							\
	} while(0)

#endif
