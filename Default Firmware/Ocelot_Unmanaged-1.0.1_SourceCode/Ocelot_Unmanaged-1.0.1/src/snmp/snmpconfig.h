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

#if !defined (__SNMPCONFIG_H__)
#define __SNMPCONFIG_H__


/****************************************************************************
 * Defines
 *
 *
 ************************************************************************** */

/* ---------------- UDP configuration -------------------*/
#define VTSS_SNMP_MAX_DGRAM_SIZE (1500)  /* max supported length of UDP datagrams */
#define SNMP_UDP_PORT (161)              /* listening port for SNMP requests. */

/* ---------------- General SNMP configuration -------------------*/
#define VTSS_SNMP_MAX_COMMUNITY_LENGTH (20)

/* Value for traps is either default value to use for configuration or defined value
   to insert in traps if configuraion of community strings is not enabled */
#define COMMUNITY_STRING_TRAPS "public"

/* ---------------- MIB - 2 Configuration ------------------ */
/* ifTable variables */
#define SNMP_IFTABLE_IFTYPE       (6)        /* ifType 6 = csmd-cd */
#define SNMP_IFTABLE_MTU          (1500)

/* System group variables */
#define SNMP_SYSTEM_SERVICES (3)    /* 1 = physical (e.g., repeaters), 2 = datalink/subnetwork (e.g., bridges) */
#define SNMP_SYSTEM_SYSOBJID {0, 0}


/* default values for read/write variables */
#define SNMP_SYSTEM_CONTACT ("SYSTEM CONTACT")
#define SNMP_SYSTEM_LOCATION ("SYSTEM LOCATION")
/* SNMP_SYSTEM_NAME is read from eeprom */

/* IP Group */
#define SNMP_IP_IPFORWARDING (2)


/* --------------- Include or exclude Microsemi Private MIB -------*/
#define SNMP_INCLUDE_VTSS_PRIVATE_MIB 0

/* ---------------- BRIDGEMIB Configuration ------------------ */
#define DOT1DBASETYPE (2) /* 2 = transparent-only  */

/* number of entries in MAC shadow table */
#define NUMBER_OF_SHADOW_ENTRIES (128)

/* ---------------- TRAPS configuration ----------------------- */
#define SNMP_INCLUDE_TRAP_SUPPORT 1 /* 1 = include trap support */

#define USE_V2_TRAPS 0  /* if defined to 1 the agent will use v2c
                           traps, otherwise it will use v1 traps */

#define TRAP_PORT (162)
#if defined(WIN32) || defined(LINUX)
#define TRAP_DEST ("10.10.130.19")
#else
/* 100th's of a second to wait before transmitting the very first trap */
/* any trap before this time is discarded.
   Shouldn't be set to a value so low, that links are not up before
   trying to transmit the first trap*/
#define EARLIEST_TRAP_TIME 500
#endif

/* ---------------- Interfaces configuration ----------------------- */
#if !defined(__C51__)
/* for WIN32 and Linux: for a generic application, simulate 12 ports */
#define MIN_PORT 0
#define MAX_PORT 12
#define NO_OF_BOARD_PORTS 12
#endif

/* port numbers to report over SNMP */
#define SNMP_IFINDEX_PORT_START  (5000)
#define SNMP_IFINDEX_PORT_NO_LOW (1+ SNMP_IFINDEX_PORT_START)
#define SNMP_IFINDEX_PORT_NO_HI  (   SNMP_IFINDEX_PORT_START + NO_OF_BOARD_PORTS)

/* speed, until able to read from device */
#define SNMP_IFTABLE_IFSPEED (1000000000)

/* ifTable variables */
#define IFTABLE_ENTRY_MAX_DESCRIPTION_LEN (10)
#define SNMP_IFTABLE_DESCR_PREFIX ("Port #")

/* the ifTable index IP protocol for the processor */
#define SNMP_IFTABLE_CPU_INDEX 1
#define SNMP_IFTABLE_CPU_DESCRIPTION ("IP Interface")

/* interface specific ifSpecific */
#define SNMP_IFTABLE_IFSPECIFIC {0,0}

/* ---------------- RMON MIB configuration ----------------------- */
#define SNMP_RMON_ETHERSTATS_OWNER ("")

/****************************************************************************
 * Typedefs and enums
 *
 *
 ************************************************************************** */

/****************************************************************************
 * Prototypes
 *
 *
 ************************************************************************** */

#endif
