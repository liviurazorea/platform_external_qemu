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
#ifndef ARGOS_CONFIG_H
#define ARGOS_CONFIG_H

//$lv$ #include "config-host.h"

//! Memory bytemap
#define ARGOS_BYTEMAP 0
//! Memory pagemap
#define ARGOS_PAGEMAP 1
//! Memory bitmap
#define ARGOS_BITMAP  2

//! Memory tracking model
#ifdef CONFIG_USER_ONLY

//$lv$ # define ARGOS_MEMMAP ARGOS_PAGEMAP
//$lv$ # if defined(ARGOS_LOWMEM_MODE)
//$lv$ #  define ARGOS_INNER_PAGEMAP ARGOS_BITMAP
//$lv$ # else
//$lv$ #  define ARGOS_INNER_PAGEMAP ARGOS_BYTEMAP
//$lv$ # endif
//$lv$ 
//$lv$ # ifdef ARGOS_NET_TRACKER
//$lv$ #  undef ARGOS_NET_TRACKER
//$lv$ # endif

#else

# ifdef ARGOS_PAGE_MODE
//$lv$ #  define ARGOS_MEMMAP ARGOS_PAGEMAP
//$lv$ #  if defined(ARGOS_LOWMEM_MODE) && !defined(ARGOS_NET_TRACKER)
//$lv$ #   define ARGOS_INNER_PAGEMAP ARGOS_BITMAP
//$lv$ #  else 
//$lv$ #   define ARGOS_INNER_PAGEMAP ARGOS_BYTEMAP
//$lv$ #  endif
# else
#  if defined(ARGOS_LOWMEM_MODE) && !defined(ARGOS_NET_TRACKER)
//$lv$ #   define ARGOS_MEMMAP ARGOS_BITMAP
#  else
#   define ARGOS_MEMMAP ARGOS_BYTEMAP
#  endif
# endif

#endif

//$lv$ //! Enable MMX tracking
//$lv$ #define ARGOS_MMX_ENABLE
//$lv$ //! Enable debugging code
//$lv$ //#define ARGOS_DEBUG
//$lv$ //#define ARGOS_DISABLE_MEMTRACK
//$lv$ 
//$lv$ // Enable assertions for debugging purposes
//$lv$ #define ASSERTIONS_ENABLE
//$lv$ 
//$lv$ // Enable stages by setting the mask size.
//$lv$ #ifdef ARGOS_NET_TRACKER
//$lv$ #define ARGOS_STAGE_SIZE 2 // in bytes, this gives us 2^(ARGOS_STAGE_SIZE) stages we can track.
//$lv$ #endif
//$lv$ 
//$lv$ #define ARGOS_TRACKSC_LOG_FILENAME_TEMPLATE "argos.sc.%d"

#endif
