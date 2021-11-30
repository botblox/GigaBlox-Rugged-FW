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

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */

#include "uartdrv.h"
#include "print.h"
#include "snmpconfig.h"
#include "txt.h"
#include "version.h"

#ifndef TRANSIT_SNMP
#define TRANSIT_SNMP 0
#endif

#if TRANSIT_SNMP || TRANSIT_LLDP
/*****************************************************************************
 *
 *
 * Defines
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Typedefs and enums
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Prototypes for local functions
 *
 *
 *
 ****************************************************************************/

#if !TRANSIT_LLDP_REDUCED
void mib_common_get_if_descr (uchar port_no, uchar xdata * dest)
{
    uart_redirect(dest);
    print_str(SNMP_IFTABLE_DESCR_PREFIX);
    print_dec(port_no);
    uart_redirect(0);
}

ulong mib_common_get_ip_if_index (void)
{
    return SNMP_IFTABLE_CPU_INDEX;
}

void mib_common_get_sys_descr (uchar xdata * dest)
{
    uart_redirect(dest);
    print_txt(TXT_NO_SWITCH_NAME);
    print_spaces(1);
    print_ch('-');
    print_spaces(1);
    print_str(SW_VERSION);
    uart_redirect(0);
}
#endif

#endif
