#ifndef _ARGOS_TYPES_H_
#define _ARGOS_TYPES_H_

#include "argos-config.h"
#include "argos-tag.h"

//! Argos bytemap data type
#ifdef ARGOS_NET_TRACKER
typedef uint32_t argos_netidx_t;
typedef argos_netidx_t argos_bytemap_t;
#else
typedef unsigned char argos_bytemap_t;
#endif

//! Argos pagemap data types
typedef argos_bytemap_t argos_pagemap_inner_t;
typedef argos_pagemap_inner_t *argos_pagemap_t;

//! Argos bitmap data types
typedef unsigned char argos_bitmap_t;


#if ARGOS_MEMMAP == ARGOS_BYTEMAP
typedef argos_bytemap_t argos_memmap_t;
#elif ARGOS_MEMMAP == ARGOS_PAGEMAP
typedef argos_pagemap_t argos_memmap_t;
#elif ARGOS_MEMMAP == ARGOS_BITMAP
typedef argos_bitmap_t argos_memmap_t;
#endif

#endif /* _ARGOS_TYPES_H_ */
