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
#ifndef ARGOS_BYTEMAP_H
#define ARGOS_BYTEMAP_H

//$lv$ #include "argos-config.h"
//$lv$ #include "argos-tag.h"
//$lv$ #include <string.h>
//$lv$ 
//$lv$ //#define BYTEMAP_DEBUG
//$lv$ 
//$lv$ #ifdef BYTEMAP_DEBUG
//$lv$ # include "argos-debug.h"
//$lv$ # define dprintf(...) argos_printf(__VA_ARGS__)
//$lv$ #else
//$lv$ # define dprintf(...)
//$lv$ #endif
//$lv$ 
//$lv$ 
//$lv$ 
//$lv$ #ifndef ARGOS_NET_TRACKER
//$lv$ 
//$lv$ #define ARGOS_BYTEMAP_LD_OP(opsfx, type)				\
//$lv$ static inline void							\
//$lv$ glue(argos_bytemap_ld, opsfx)						\
//$lv$ (argos_bytemap_t *map, unsigned long maddr, unsigned long paddr, 	\
//$lv$  						argos_rtag_t *tag)	\
//$lv$ {									\
//$lv$ 	if (*(type *)(map + maddr) == 0)				\
//$lv$ 		argos_tag_clear(tag);					\
//$lv$ 	else								\
//$lv$ 		argos_tag_set(tag, paddr);				\
//$lv$ }
//$lv$ ARGOS_BYTEMAP_LD_OP(b, uint8_t)
//$lv$ ARGOS_BYTEMAP_LD_OP(w, uint16_t)
//$lv$ ARGOS_BYTEMAP_LD_OP(l, uint32_t)
//$lv$ ARGOS_BYTEMAP_LD_OP(q, uint64_t)
//$lv$ 
//$lv$ 
//$lv$ #define ARGOS_BYTEMAP_ST_OP(opsfx, type)				    \
//$lv$ static inline void							    \
//$lv$ glue(argos_bytemap_st, opsfx)						    \
//$lv$ (argos_bytemap_t *map, unsigned long maddr, const argos_rtag_t *tag)	    \
//$lv$ {									    \
//$lv$ 	*(type *)(map + maddr) = (argos_tag_isdirty(tag))? ~(type)0 : (type)0;\
//$lv$ }
//$lv$ ARGOS_BYTEMAP_ST_OP(b, uint8_t)
//$lv$ ARGOS_BYTEMAP_ST_OP(w, uint16_t)
//$lv$ ARGOS_BYTEMAP_ST_OP(l, uint32_t)
//$lv$ #if HOST_LONG_BITS > 32
//$lv$ ARGOS_BYTEMAP_ST_OP(q, uint64_t)
//$lv$ #else
//$lv$ static inline void
//$lv$ argos_bytemap_stq(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		const argos_rtag_t *tag)
//$lv$ {
//$lv$ 	if (argos_tag_isdirty(tag)) {
//$lv$ 		*(uint32_t *)(map + maddr) = 0xff;
//$lv$ 		*(uint32_t *)(map + maddr + 4) = 0xff;
//$lv$ 	} else {
//$lv$ 		*(uint32_t *)(map + maddr) = 0;
//$lv$ 		*(uint32_t *)(map + maddr + 4) = 0;
//$lv$ 	}
//$lv$ #if 0
//$lv$ 	argos_bytemap_stl(map, maddr, t);
//$lv$ 	argos_bytemap_stl(map, maddr + 4, t);
//$lv$ #endif
//$lv$ }
//$lv$ #endif
//$lv$ 
//$lv$ 
//$lv$ #define ARGOS_BYTEMAP_CLR_OP(opsfx, type)				 \
//$lv$ static inline void							 \
//$lv$ glue(argos_bytemap_clr, opsfx)(argos_bytemap_t *map, unsigned long maddr)\
//$lv$ {									 \
//$lv$ 	*(type *)(map + maddr) = (type)0;				 \
//$lv$ }
//$lv$ ARGOS_BYTEMAP_CLR_OP(b, uint8_t)
//$lv$ ARGOS_BYTEMAP_CLR_OP(w, uint16_t)
//$lv$ ARGOS_BYTEMAP_CLR_OP(l, uint32_t)
//$lv$ ARGOS_BYTEMAP_CLR_OP(q, uint64_t)
//$lv$ 
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrdq(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	argos_bytemap_clrq(map, maddr);
//$lv$ 	argos_bytemap_clrq(map, maddr + 8);
//$lv$ }
//$lv$ 
//$lv$ #define ARGOS_BYTEMAP_MOV_OP(opsfx, type)				  \
//$lv$ static inline void							  \
//$lv$ glue(argos_bytemap_mov, opsfx)(argos_bytemap_t *map, unsigned long daddr,  \
//$lv$ 		unsigned long saddr)					  \
//$lv$ {									  \
//$lv$ 	*(type *)(map + daddr) = *(type *)(map + saddr);		  \
//$lv$ }
//$lv$ ARGOS_BYTEMAP_MOV_OP(b, uint8_t)
//$lv$ ARGOS_BYTEMAP_MOV_OP(w, uint16_t)
//$lv$ ARGOS_BYTEMAP_MOV_OP(l, uint32_t)
//$lv$ ARGOS_BYTEMAP_MOV_OP(q, uint64_t)
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movdq(argos_bytemap_t *map, unsigned long daddr, 
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ 	argos_bytemap_movq(map, saddr, daddr);
//$lv$ 	argos_bytemap_movq(map, saddr + 8, daddr + 8);
//$lv$ }
//$lv$ 
//$lv$ 
//$lv$ #else // ifndef ARGOS_NET_TRACKER
//$lv$ 
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_ldb(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		unsigned long paddr, argos_rtag_t *tag)
//$lv$ {
//$lv$ 	if (map[maddr])
//$lv$ 		argos_tag_set(tag, paddr, map[maddr]);
//$lv$ 	else
//$lv$ 		argos_tag_clear(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_ldw(argos_bytemap_t *map, unsigned long maddr,
//$lv$ 		unsigned long paddr, argos_rtag_t *tag)
//$lv$ {
//$lv$ 	if (map[maddr] || map[maddr + 1])
//$lv$ 		argos_tag_set(tag, paddr, (map[maddr])? map[maddr] : 
//$lv$ 				map[maddr + 1]);
//$lv$ 	else
//$lv$ 		argos_tag_clear(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_ldl(argos_bytemap_t *map, unsigned long maddr,
//$lv$ 		unsigned long paddr, argos_rtag_t *tag)
//$lv$ {
//$lv$ #if 0
//$lv$ 	if (map[maddr] || map[maddr + 1] || map[maddr + 2] || map[maddr + 3])
//$lv$ 	{
//$lv$ #endif
//$lv$ 	int i;
//$lv$ 	for (i = 0; i < 4; i++)
//$lv$ 		if (map[maddr + i]) {
//$lv$ 			argos_tag_set(tag, paddr, map[maddr + i]);
//$lv$ 			return;
//$lv$ 		}
//$lv$ #if 0
//$lv$ 	}
//$lv$ 	else
//$lv$ #endif
//$lv$ 	argos_tag_clear(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_ldq(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		unsigned long paddr, argos_rtag_t *tag)
//$lv$ {
//$lv$ #if 0
//$lv$ 	if (map[maddr] || map[maddr + 1] || map[maddr + 2] || map[maddr + 3] || 
//$lv$ 			map[maddr + 4] || map[maddr + 5] || map[maddr + 6] ||
//$lv$ 			map[maddr + 7])
//$lv$ 	{
//$lv$ #endif
//$lv$ 	int i;
//$lv$ 	for (i = 0; i < 8; i++)
//$lv$ 		if (map[maddr + i]) {
//$lv$ 			argos_tag_set(tag, paddr, map[maddr + i]);
//$lv$ 			return;
//$lv$ 		}
//$lv$ #if 0
//$lv$ 	}
//$lv$ 	else
//$lv$ #endif
//$lv$ 	argos_tag_clear(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_stb(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		const argos_rtag_t *tag)
//$lv$ {
//$lv$ 	//map[maddr] = (argos_tag_isdirty(tag))? argos_tag_netidx(tag) : 0;
//$lv$ 	map[maddr] = argos_tag_netidx(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_stw(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		const argos_rtag_t *tag)
//$lv$ {
//$lv$ #if 0
//$lv$ 	map[maddr + 1] = map[maddr] = (argos_tag_isdirty(tag))? 
//$lv$ 		argos_tag_netidx(tag) : 0;
//$lv$ #endif
//$lv$ 	map[maddr + 1] = map[maddr] = argos_tag_netidx(tag);
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_stl(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		const argos_rtag_t *tag)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 4; i++)
//$lv$ 		map[maddr + i] = argos_tag_netidx(tag);
//$lv$ #if 0
//$lv$ 	map[maddr + 3] = map[maddr + 2] = map[maddr + 1] = map[maddr] = 
//$lv$ 			(argos_tag_isdirty(tag))? argos_tag_netidx(tag) : 0;
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_stq(argos_bytemap_t *map, unsigned long maddr, 
//$lv$ 		const argos_rtag_t *tag)
//$lv$ {
//$lv$ 	int i;
//$lv$ 	//argos_netidx_t idx = (argos_tag_isdirty(tag))? argos_tag_netidx(tag):0;
//$lv$ 
//$lv$ 	for (i = 0; i < 8; i++)
//$lv$ 		//map[maddr + i] = idx;
//$lv$ 		map[maddr + i] = argos_tag_netidx(tag);
//$lv$ #if 0
//$lv$ 	map[maddr + 7] = map[maddr + 6] = map[maddr + 5] = map[maddr + 4] = 
//$lv$ 			map[maddr + 3] = map[maddr + 2] = map[maddr + 1] = 
//$lv$ 			map[maddr] = (argos_tag_isdirty(tag))?
//$lv$ 			argos_tag_netidx(tag) : 0;
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrb(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	map[maddr] = 0;
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrw(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	map[maddr + 1] = map[maddr] = 0;
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrl(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 4; i++)
//$lv$ 		map[maddr + i] = 0;
//$lv$ 	//map[maddr + 3] = map[maddr + 2] = map[maddr + 1] = map[maddr] = 0;
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrq(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 8; i++)
//$lv$ 		map[maddr + i] = 0;
//$lv$ #if 0
//$lv$ 	map[maddr + 7] = map[maddr + 6] = map[maddr + 5] = map[maddr + 4] =
//$lv$ 			map[maddr + 3] = map[maddr + 2] = map[maddr + 1] = 
//$lv$ 			map[maddr] = 0;
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clrdq(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 16; i++)
//$lv$ 		map[maddr + i] = 0;
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movb(argos_bytemap_t *map, unsigned long daddr,
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ 	map[daddr] = map[saddr];
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movw(argos_bytemap_t *map, unsigned long daddr,
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ 	map[daddr] = map[saddr];
//$lv$ 	map[daddr + 1] = map[saddr + 1];
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movl(argos_bytemap_t *map, unsigned long daddr,
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ #if 0
//$lv$ 	argos_bytemap_movw(map, daddr, saddr);
//$lv$ 	argos_bytemap_movw(map, daddr + 2, saddr + 2);
//$lv$ #endif
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i< 4; i++)
//$lv$ 		map[daddr + i] = map[saddr + i];
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movq(argos_bytemap_t *map, unsigned long daddr,
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 8; i++)
//$lv$ 		map[daddr + i] = map[saddr + i];
//$lv$ #if 0
//$lv$ 	argos_bytemap_movl(map, daddr, saddr);
//$lv$ 	argos_bytemap_movl(map, daddr + 4, saddr + 4);
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_movdq(argos_bytemap_t *map, unsigned long daddr, 
//$lv$ 		unsigned long saddr)
//$lv$ {
//$lv$ 	int i;
//$lv$ 
//$lv$ 	for (i = 0; i < 16; i++)
//$lv$ 		map[daddr + i] = map[saddr + i];
//$lv$ 	//memmove(map + daddr, map + saddr, 16 * sizeof(argos_netidx_t));
//$lv$ #if 0
//$lv$ 	argos_bytemap_movq(map, saddr, daddr);
//$lv$ 	argos_bytemap_movq(map, saddr + 8, daddr + 8);
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline argos_netidx_t *
//$lv$ argos_bytemap_ntdata(argos_bytemap_t *map, target_ulong paddr)
//$lv$ {
//$lv$ 	return (map + paddr);
//$lv$ }
//$lv$ 
//$lv$ #endif // ARGOS_NET_TRACKER
//$lv$ 
//$lv$ // Common
//$lv$ 
//$lv$ static inline int
//$lv$ argos_bytemap_istainted(argos_bytemap_t *map, unsigned long maddr)
//$lv$ {
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ 	return (ARGOS_GET_NETIDX(map[maddr]) == 0)?0:1;
//$lv$ #else
//$lv$ 	return (map[maddr] == 0)? 0 : 1;
//$lv$ #endif
//$lv$ }
//$lv$ 
//$lv$ static inline void
//$lv$ argos_bytemap_clear(argos_bytemap_t *map, unsigned long maddr, size_t len)
//$lv$ {
//$lv$ 	//int i;
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ 	len *= 4;
//$lv$ #endif
//$lv$ 	dprintf("[BYTEMAP] Clear base 0x%08x, len %u\n", maddr, len);
//$lv$ 	/*
//$lv$ 	for (i = 0; i < len; i++)
//$lv$ 		map[maddr + i] = 0;
//$lv$ 	*/
//$lv$ 	memset(map + maddr, 0, len);
//$lv$ }


argos_bytemap_t *argos_bytemap_create(size_t len);
argos_bytemap_t *argos_bytemap_createz(size_t len);
//$lv$ void argos_bytemap_reset(argos_bytemap_t *map, size_t len);
//$lv$ void argos_bytemap_destroy(argos_bytemap_t *map, size_t len);
//$lv$ 
//$lv$ #undef dprintf
#endif
