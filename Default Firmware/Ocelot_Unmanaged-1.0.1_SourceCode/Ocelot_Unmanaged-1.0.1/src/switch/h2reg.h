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

#ifndef __H2REG_H__
#define __H2REG_H__

/*****************************************************************************
 *
 *
 * Switch chip blocks
 *
 *
 *
 ****************************************************************************/

/* (For performance optimization shift block ids in position used in register
   interface) */
#define PORT       (1 << 5)
#define ANALYZER   (2 << 5)
#define MIIM       (3 << 5)
#define CAPTURE    (4 << 5)
#define ARBITER    (5 << 5)
#define SYSTEM     (7 << 5)

/*****************************************************************************
 *
 *
 * Memory initialization
 *
 *
 *
 ****************************************************************************/

#define MEMINIT    (3 << 5)

#define MEMINIT_SUBBLK  2






/*****************************************************************************
 *
 *
 * Register addresses
 *
 *
 *
 ****************************************************************************/

/* system registers */
#define SYS_CPUMODE             0x00
#define SYS_SIPAD               0x01
#define SYS_PIWIDTH             0x02
#define SYS_GLORESET            0x14
#define SYS_CHIPID              0x18
#define SYS_TIMECMP             0x24
#define SYS_SLOWDATA            0x2C
#define SYS_INTCTRL             0x30 /* Alias SYS_CPUCTRL */
#define SYS_CPUCTRL             0x30 /* Alias SYS_INTCTRL */
#define SYS_GPIO                0x34

/* MIIM registers */
#define MIIMSTAT                0x00
#define MIIMCMD                 0x01
#define MIIMDATA                0x02
#define MIIMPRES                0x03
#define MIIMSCAN                0x04
#define MIIMSRES                0x05

/* ANALYZER registers */


#define ANA_IFLODMASK           0x04
#define ANA_ANMOVED             0x08
#define ANA_ANAGEFIL            0x09
#define ANA_ANEVENTS            0x0A
#define ANA_ANCNTMSK            0x0B
#define ANA_ANCNTVAL            0x0C
#define ANA_LERNMASK            0x0D
#define ANA_UFLODMSK            0x0E
#define ANA_MFLODMSK            0x0F
#define ANA_RECVMASK            0x10
#define ANA_AGGRCNTL            0x20
#define ANA_AGGRMSKS            0x30
#define ANA_DSTMASKS            0x40
#define ANA_SRCMASKS            0x80
#define ANA_MACHDATA            0x06
#define ANA_MACLDATA            0x07
#define ANA_MACACCES            0xB0
#define ANA_MACTINDX            0xC0
#define ANA_VLANACES            0xD0
#define ANA_VLANINDX            0xE0
#define ANA_AGENCNTL            0xF0

/*  ARBITER registers */
#define ARBEMPTY                0x0C
#define ARBDISC                 0x0E

/*  CPU CAPTURE registers */
#define CAPREADP                0x00

/* MAC registers */
#define PORT_MACCONF            0x00
#define PORT_MACHDXGAP          0x02
#define PORT_FCTXCONF           0x04
#define PORT_FCMACHI            0x08
#define PORT_FCMACLO            0x0C
#define PORT_MAXLEN             0x10
#define PORT_ADVPORTM           0x19
#define PORT_TXUPDCFG           0x24
#define PORT_CFIDROP            0x25


/* Shared FIFO registers */
#define PORT_CPUTXDAT           0xC0
#define PORT_MISCFIFO           0xC4
#define PORT_MISCSTAT           0xC8
#define PORT_POOLCFG            0xCC
#define PORT_DROPCNT            0xD4
#define PORT_FREEPOOL           0xD8
#define PORT_DBQHPRX            0xE8
#define PORT_DBQLPRX            0xEC
#define PORT_DBQHPTX            0xF0
#define PORT_DBQLPTX            0xF4

/* Categorizer registers */

/* Statistics registers */

/* Detailed Statistics registers */
#define PORT_C_RXOCT            0x50
#define PORT_C_TXOCT            0x51

/* MEMINIT registers */
#define MEMINIT_MEMINIT         0x00
#define MEMINIT_MEMRES          0x01


/*****************************************************************************
 *
 *
 * Bit mapping
 *
 *
 *
 ****************************************************************************/


/* Port SRCMASKS register */
#define CPU_COPY_BIT          27
#define MIRROR_BIT            26

/* Analyzer AGENCNTL register */
#define MIRROR_PORT_MASK      0x0001F

/* Tx header for port CPUTXDAT register */
#define CPU_FRAME_LENGTH_BIT  16
#define CPU_FRAME_LENGTH_MASK 0x3fff

/* Analyzer MACTINDX register */
#define BUCKET_BIT            11


/* GPIO bits */
#define GPIO_4_BIT    0
#define GPIO_3_BIT    1
#define GPIO_2_BIT    2
#define GPIO_1_BIT    3
#define GPIO_0_BIT    4
#define GPIO_OE_4_BIT 5
#define GPIO_OE_3_BIT 6
#define GPIO_OE_2_BIT 7
#define GPIO_OE_1_BIT 8
#define GPIO_OE_0_BIT 9



/* Port (MAC) reset mask (for MACCONF register) */
#define MAC_RESET_MASK 0x20000030


/*****************************************************************************
 *
 *
 * Miscellaneous
 *
 *
 *
 ****************************************************************************/

/*
** Chip id
*/
/*
** Maximum number of ports in a link aggregation group
*/


#if defined(LUTON26_L25)
#define MAX_NO_OF_AGGR_PORTS 16
#elif defined(LUTON26_L10) || defined(LUTON26_L16)
#define MAX_NO_OF_AGGR_PORTS 10
#elif defined(FERRET_F11) || defined(FERRET_F10P)
#define MAX_NO_OF_AGGR_PORTS 10
#elif defined(FERRET_F5) || defined(FERRET_F4P)
#define MAX_NO_OF_AGGR_PORTS 4
#else
#error "Not defined yet: MAX_NO_OF_AGGR_PORTS"
#endif




#endif











