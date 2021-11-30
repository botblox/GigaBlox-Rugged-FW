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

#ifndef __TASKDEF_H__
#define __TASKDEF_H__

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */

typedef enum {
    TASK_ID_MAIN = 0,  /* Keep main loop as first entry with index 0 */

    TASK_ID_CLI,
    TASK_ID_PHY_TIMER,
    TASK_ID_PHY,

    TASK_ID_UIP_TIMER,

    TASK_ID_CLI_TIMER,
    TASK_ID_AGEING,

    TASK_ID_WEB_TIMER,

    TASK_ID_ERROR_CHECK,
#if (WATCHDOG_PRESENT && WATCHDOG_ENABLE)
    TASK_ID_WATCHDOG,
#endif
#if TRANSIT_EEE
    TASK_ID_EEE,
#endif
#if TRANSIT_FAN_CONTROL
    TASK_ID_FAN_CONTROL,
#endif
#if TRANSIT_THERMAL
    TASK_ID_THERMAL_CONTROL,
#endif
#if TRANSIT_LOOPDETECT
    TASK_ID_LOOPBACK_CHECK,
#endif
#if TRANSIT_LACP
    TASK_ID_LACP,
    TASK_ID_LACP_TIMER,
#endif
    TASK_ID_RX_PACKET,
#if TRANSIT_LLDP
    TASK_ID_LLDP_TIMER,
#endif /* TRANSIT_LLDP */

#if TRANSIT_MAILBOX_COMM
    TASK_ID_MAILBOX_COMM,
#endif // TRANSIT_MAILBOX_COMM

    TASK_ID_TIMER_SINCE_BOOT,

    NUM_TASKS
} task_id_t;

typedef enum {
    SUB_TASK_START = NUM_TASKS - 1,
#if TRANSIT_LLDP
    SUB_TASK_ID_LLDP_RX,
    SUB_TASK_ID_LLDP_TX,
    SUB_TASK_ID_LLDP_LINK,
#endif /* TRANSIT_LLDP */
#if TRANSIT_EEE
    SUB_TASK_ID_EEE_LINK,
#endif
#if TRANSIT_LACP
    SUB_TASK_ID_LACP_RX,
    SUB_TASK_ID_LACP_LINK,
#endif
    TOT_NUM_TASKS
} sub_task_id_t;

#define TASK(TASK_ID,EXPR)     EXPR
#define MAIN_LOOP_ENTER()      {}
#define MAIN_LOOP_EXIT()       {}

#endif /* __TASKDEF_H__ */












