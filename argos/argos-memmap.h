//$lv$ /* Copyright (c) 2006-2008, Georgios Portokalidis
//$lv$    All rights reserved.
//$lv$ 
//$lv$    Redistribution and use in source and binary forms, with or without
//$lv$    modification, are permitted provided that the following conditions
//$lv$    are met:
//$lv$ 
//$lv$     * Redistributions of source code must retain the above copyright
//$lv$       notice, this list of conditions and the following disclaimer.
//$lv$     * Redistributions in binary form must reproduce the above
//$lv$       copyright notice, this list of conditions and the following
//$lv$       disclaimer in the documentation and/or other materials provided
//$lv$       with the distribution.
//$lv$     * Neither the name of the Vrije Universiteit nor the names of its
//$lv$       contributors may be used to endorse or promote products derived
//$lv$       from this software without specific prior written permission.
//$lv$ 
//$lv$    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//$lv$    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//$lv$    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//$lv$    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//$lv$    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//$lv$    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//$lv$    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//$lv$    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//$lv$    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//$lv$    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//$lv$    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
//$lv$    OF THE POSSIBILITY OF SUCH DAMAGE.
//$lv$ */
#ifndef ARGOS_MEMMAP_H
#define ARGOS_MEMMAP_H

#include "argos-config.h"
#include "argos-bytemap.h"
//$lv$ #include "argos-bitmap.h"

//$lv$ extern uint8_t *phys_ram_base;
//$lv$ 
//$lv$ #define ARGOS_OFFSET(p) ((unsigned long)((uint8_t *)(long)(p) - (unsigned long)phys_ram_base))
//$lv$ #define ARGOS_ENVMAP_OFFSET(p) ((uint8_t *)(p) - (uint8_t *)(env))
//$lv$ 
//$lv$ #define ARGOS_MEMMAP_CLRb(p) argos_memmap_clrb(ARGOS_OFFSET(p))
//$lv$ #define ARGOS_MEMMAP_CLRw(p) argos_memmap_clrw(ARGOS_OFFSET(p))
//$lv$ #define ARGOS_MEMMAP_CLRl(p) argos_memmap_clrl(ARGOS_OFFSET(p))
//$lv$ #define ARGOS_MEMMAP_CLRq(p) argos_memmap_clrq(ARGOS_OFFSET(p))
//$lv$ 
//$lv$ #define ARGOS_MEMMAP_LDb(p, tag) argos_memmap_ldb(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_LDw(p, tag) argos_memmap_ldw(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_LDl(p, tag) argos_memmap_ldl(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_LDq(p, tag) argos_memmap_ldq(ARGOS_OFFSET(p), tag)
//$lv$ 
//$lv$ #define ARGOS_MEMMAP_STb(p, tag) argos_memmap_stb(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_STw(p, tag) argos_memmap_stw(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_STl(p, tag) argos_memmap_stl(ARGOS_OFFSET(p), tag)
//$lv$ #define ARGOS_MEMMAP_STq(p, tag) argos_memmap_stq(ARGOS_OFFSET(p), tag)
//$lv$ 
//$lv$ #define ARGOS_MEMMAP_CLEAR(p, len) argos_memmap_clear(ARGOS_OFFSET(p), len)

#ifdef ARGOS_DISABLE_MEMTRACK
//$lv$ #include "argos-tag.h"
//$lv$ 
//$lv$ #define argos_memmap_ldb(addr, tag) argos_tag_clear(tag)
//$lv$ #define argos_memmap_ldw(addr, tag) argos_tag_clear(tag)
//$lv$ #define argos_memmap_ldl(addr, tag) argos_tag_clear(tag)
//$lv$ #define argos_memmap_ldq(addr, tag) argos_tag_clear(tag)
//$lv$ 
//$lv$ #define argos_memmap_stb(addr, tag)
//$lv$ #define argos_memmap_stw(addr, tag)
//$lv$ #define argos_memmap_stl(addr, tag)
//$lv$ #define argos_memmap_stq(addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_clrb(addr)
//$lv$ #define argos_memmap_clrw(addr)
//$lv$ #define argos_memmap_clrl(addr)
//$lv$ #define argos_memmap_clrq(addr)
//$lv$ 
//$lv$ #define argos_memmap_clear(addr, len)
//$lv$ 
//$lv$ #define argos_memmap_istainted(addr)	0

#define argos_memmap_create(len)	1
#define argos_memmap_createz(len)	1
//$lv$#define argos_memmap_reset(map, len)
//$lv$#define argos_memmap_destroy(map, len)
//$lv$#define argos_memmap_ntdata(addr)	0

#else // ARGOS_DISABLE_MEMTRACK

#if ARGOS_MEMMAP == ARGOS_BYTEMAP
//$lv$ #define argos_memmap_ldb(addr, tag) 			\
//$lv$ 	argos_bytemap_ldb(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldw(addr, tag)			\
//$lv$ 	argos_bytemap_ldw(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldl(addr, tag)			\
//$lv$ 	argos_bytemap_ldl(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldq(addr, tag)			\
//$lv$ 	argos_bytemap_ldq(argos_memmap, addr, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_stb(addr, tag) argos_bytemap_stb(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stw(addr, tag) argos_bytemap_stw(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stl(addr, tag) argos_bytemap_stl(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stq(addr, tag) argos_bytemap_stq(argos_memmap, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_clrb(addr) argos_bytemap_clrb(argos_memmap, addr)
//$lv$ #define argos_memmap_clrw(addr) argos_bytemap_clrw(argos_memmap, addr)
//$lv$ #define argos_memmap_clrl(addr) argos_bytemap_clrl(argos_memmap, addr)
//$lv$ #define argos_memmap_clrq(addr) argos_bytemap_clrq(argos_memmap, addr)
//$lv$ 
//$lv$ #define argos_memmap_clear(addr, len) 			\
//$lv$ 	argos_bytemap_clear(argos_memmap, addr, len)
//$lv$ 
//$lv$ #define argos_memmap_istainted(addr)			\
//$lv$ 	argos_bytemap_istainted(argos_memmap, addr)

#define argos_memmap_create(len)	argos_bytemap_create(len)
#define argos_memmap_createz(len)	argos_bytemap_createz(len)
//$lv$ #define argos_memmap_reset(map, len)	argos_bytemap_reset(len)
//$lv$ #define argos_memmap_destroy(map, len)	argos_bytemap_destroy(len)
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ #define argos_memmap_ntdata(addr)	argos_bytemap_ntdata(argos_memmap, addr)
//$lv$ #endif

// ARGOS_BYTEMAP
#elif ARGOS_MEMMAP == ARGOS_PAGEMAP
//$lv$ #include "argos-pagemap.h"
//$lv$ 
//$lv$ #define argos_memmap_ldb(addr, tag) 			\
//$lv$ 	argos_pagemap_ldb(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldw(addr, tag)			\
//$lv$ 	argos_pagemap_ldw(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldl(addr, tag)			\
//$lv$ 	argos_pagemap_ldl(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldq(addr, tag)			\
//$lv$ 	argos_pagemap_ldq(argos_memmap, addr, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_stb(addr, tag) argos_pagemap_stb(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stw(addr, tag) argos_pagemap_stw(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stl(addr, tag) argos_pagemap_stl(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stq(addr, tag) argos_pagemap_stq(argos_memmap, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_clrb(addr) argos_pagemap_clrb(argos_memmap, addr)
//$lv$ #define argos_memmap_clrw(addr) argos_pagemap_clrw(argos_memmap, addr)
//$lv$ #define argos_memmap_clrl(addr) argos_pagemap_clrl(argos_memmap, addr)
//$lv$ #define argos_memmap_clrq(addr) argos_pagemap_clrq(argos_memmap, addr)
//$lv$ 
//$lv$ #define argos_memmap_clear(addr, len) 			\
//$lv$ 	argos_pagemap_clear(argos_memmap, addr, len)
//$lv$ 
//$lv$ #define argos_memmap_istainted(addr)			\
//$lv$ 	argos_pagemap_istainted(argos_memmap, addr)

#define argos_memmap_create(len)	argos_pagemap_create(len)
#define argos_memmap_createz(len)	argos_pagemap_createz(len)
//$lv$ #define argos_memmap_reset(map, len)	argos_pagemap_reset(map, len)
//$lv$ #define argos_memmap_destroy(map, len)	argos_pagemap_destroy(map, len)
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ #define argos_memmap_ntdata(addr)	argos_pagemap_ntdata(argos_memmap, addr)
//$lv$ #endif

// ARGOS_PAGEMAP
#elif ARGOS_MEMMAP == ARGOS_BITMAP

//$lv$ #define argos_memmap_ldb(addr, tag) 			\
//$lv$ 	argos_bitmap_ldb(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldw(addr, tag)			\
//$lv$ 	argos_bitmap_ldw(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldl(addr, tag)			\
//$lv$ 	argos_bitmap_ldl(argos_memmap, addr, addr, tag)
//$lv$ #define argos_memmap_ldq(addr, tag)			\
//$lv$ 	argos_bitmap_ldq(argos_memmap, addr, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_stb(addr, tag) argos_bitmap_stb(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stw(addr, tag) argos_bitmap_stw(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stl(addr, tag) argos_bitmap_stl(argos_memmap, addr, tag)
//$lv$ #define argos_memmap_stq(addr, tag) argos_bitmap_stq(argos_memmap, addr, tag)
//$lv$ 
//$lv$ #define argos_memmap_clrb(addr) argos_bitmap_clrb(argos_memmap, addr)
//$lv$ #define argos_memmap_clrw(addr) argos_bitmap_clrw(argos_memmap, addr)
//$lv$ #define argos_memmap_clrl(addr) argos_bitmap_clrl(argos_memmap, addr)
//$lv$ #define argos_memmap_clrq(addr) argos_bitmap_clrq(argos_memmap, addr)
//$lv$ 
//$lv$ #define argos_memmap_clear(addr, len) 			\
//$lv$ 	argos_bitmap_clear(argos_memmap, addr, len)
//$lv$ 
//$lv$ #define argos_memmap_istainted(addr)			\
//$lv$ 	argos_bitmap_istainted(argos_memmap, addr)

#define argos_memmap_create(len)	argos_bitmap_create(len)
#define argos_memmap_createz(len)	argos_bitmap_createz(len)
//$lv$ #define argos_memmap_reset(map, len)	argos_bitmap_reset(len)
//$lv$ #define argos_memmap_destroy(map, len)	argos_bitmap_destroy(len)
//$lv$ 
//$lv$ // ARGOS_BITMAP
//$lv$ #endif
//$lv$ #endif // ARGOS_DISABLE_MEMTRACK
//$lv$ 
//$lv$ #include "argos-memop.h"

#endif
