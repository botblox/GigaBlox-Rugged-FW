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

/**
 * This file contains the macros for the LACP protocol module
 * that must be adapted for the operating environment.
 *
 * This is the version for the switch_app environment.
 */

#ifndef _VTSS_LACP_OS_H_
#define _VTSS_LACP_OS_H_ 1

#include "vtss_common_os.h"

#define VTSS_LACP_MAX_PORTS             (NO_OF_BOARD_PORTS) /* Number of port in switch */

#if TRANSIT_LACP

#define VTSS_LACP_AUTOKEY               ((vtss_lacp_key_t)0) /* Generate key from speed */

/* Convert LACP portnumber (1 - MAX) to 8051 extern portnumber */
#define LACP2OSEXT(PORTNO)              (PORTNO)
/* Convert LACP portnumber (1 - MAX) to 8051 internal (GMII) portnumber (MIN_PORT - MAX_PORT) */
#define LACP2OSINT(PORTNO)              uport2cport(LACP2OSEXT(PORTNO))
/* Convert OS extern portnumber to LACP portnumber (1 - MAX_PORT) */
#define OSEXT2LACP(PORTNO)              (PORTNO)
/* Convert OS internal (GMII) portnumber (MIN_PORT - MAX_PORT to LACP portnumber (1 - MAX_PORT) */
#define OSINT2LACP(PORTNO)              OSEXT2LACP(cport2uport(PORTNO))

#include "print.h"
// Ferret TODO #include "confutil.h"
#include "uartdrv.h"
#include "h2txrx.h"

#ifdef VTSS_COMMON_NDEBUG
#define VTSS_LACP_NDEBUG 1
#endif

#define VTSS_LACP_TRLVL_ERROR           VTSS_COMMON_TRLVL_ERROR
#define VTSS_LACP_TRLVL_WARNING         VTSS_COMMON_TRLVL_WARNING
#define VTSS_LACP_TRLVL_DEBUG           VTSS_COMMON_TRLVL_DEBUG
#define VTSS_LACP_TRLVL_NOISE           VTSS_COMMON_TRLVL_NOISE

#define VTSS_LACP_TRACE(LVL, ARGS)      VTSS_COMMON_TRACE(LVL, ARGS)
#define VTSS_LACP_ASSERT(EXPR)          VTSS_COMMON_ASSERT(EXPR)

#if defined(VTSS_ARCH_OCELOT)
#define VTSS_LACP_LACPMAC               (VTSS_LACP_MULTICAST_MACADDR)
#else
#define VTSS_LACP_LACPMAC               (mac_addr_lacp)
#endif
extern void lacp_timer_check(void);

#else
#define VTSS_LACP_NOT_WANTED            1
#endif /* TRANSIT_LACP */

#endif /* _VTSS_LACP_OS_H__ */
