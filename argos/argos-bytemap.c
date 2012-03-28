//$lv$ /* Copyright (c) 2006, Georgios Portokalidis
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
#include <string.h>
//$lv$ #include <stdio.h>
//$lv$ #include <stdlib.h>
//$lv$ 
//$lv$ #include "argos-config.h"
#include "../target-arm/cpu.h"
#include "argos.h"
#include "argos-bytemap.h"


argos_bytemap_t *
argos_bytemap_create(size_t len)
{
	argos_bytemap_t *map;
#ifdef ARGOS_NET_TRACKER
	len = len * 4;
#endif
	map = (argos_bytemap_t *)qemu_vmalloc(len);
	if (!map) {
		qemu_fprintf(stderr, "[ARGOS] Not enough memory\n");
		exit(1);
	}
	return map;
}


argos_bytemap_t *
argos_bytemap_createz(size_t len)
{
	argos_bytemap_t *map;
#ifdef ARGOS_NET_TRACKER
	len = len * 4;
#endif
	map = (argos_bytemap_t *)qemu_vmalloc(len);
	if (!map) {
		qemu_fprintf(stderr, "[ARGOS] Not enough memory\n");
		exit(1);
	}
	memset(map, 0, len);
	return map;
}

//$lv$ void
//$lv$ argos_bytemap_reset(argos_bytemap_t *map, size_t len)
//$lv$ {
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ 	len = len * 4;
//$lv$ #endif
//$lv$ 	memset(map, 0, len);
//$lv$ }
//$lv$ 
//$lv$ void
//$lv$ argos_bytemap_destroy(argos_bytemap_t *map, size_t len)
//$lv$ {
//$lv$ 	qemu_vfree(map);
//$lv$ }
