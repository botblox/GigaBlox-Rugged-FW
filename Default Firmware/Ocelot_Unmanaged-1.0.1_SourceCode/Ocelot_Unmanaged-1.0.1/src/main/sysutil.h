/*

 Copyright (c) 2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*/

#ifndef __SYSUTIL_H__
#define __SYSUTIL_H__

#include "common.h"

/*
 * System assert event
 */
typedef enum {
    SYS_ASSERT_EVENT_OK = 0, // Don't change the value

    SYS_ASSERT_EVENT_OS,            // Operation system
    SYS_ASSERT_EVENT_CHIP_FAMILY,   // Wrong chip family
    SYS_ASSERT_EVENT_H2_INIT,       // Hardware L2 feature initialization failed
    SYS_ASSERT_EVENT_H2_POST_RESET, // Hardware L2 feature post reset process failed
    SYS_ASSERT_EVENT_PHY,           // PHY error

    SYS_ASSERT_EVENT_CNT
} sys_assert_event_t;

void    sysutil_reboot                          (void);
void    sysutil_hang                            (void);

void sysutil_assert_event_set(sys_assert_event_t err_id);
sys_assert_event_t sysutil_assert_event_get(void);

// Backward compatible
#define sysutil_set_fatal_error(x) sysutil_assert_event_set(x)
#define sysutil_get_fatal_error() sysutil_assert_event_get()

/**
 * Set suspend flag.
 *
 * @see sysutil_get_suspend().
 */
void    sysutil_set_suspend                     (BOOL enable);

/**
 * Return suspend flag.
 *
 * @see sysutil_set_suspend().
 */
BOOL    sysutil_get_suspend                     (void);

void sysutil_show_compile_date(void);
void sysutil_show_chip_id(void);
void sysutil_show_sw_ver(void);
void sysutil_show_hw_ver(void);

#endif /* __SYSUTIL_H__ */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
