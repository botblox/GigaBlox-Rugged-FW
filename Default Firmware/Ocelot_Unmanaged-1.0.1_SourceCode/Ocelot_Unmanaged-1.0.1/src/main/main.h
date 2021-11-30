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

#ifndef __MAIN_H__
#define __MAIN_H__
#include "vtss_api_base_regs.h"

/*
 * Power up error codes.
 */
#define POWER_UP_ERROR_FLASH_CHECKSUM 4
#define POWER_UP_ERROR_PHY            5
#define POWER_UP_ERROR_H2             6

/*
 * Run-time error codes.
 */
#define ERROR_RX_BUF_OVERRUN          1
#define ERROR_UART_FRAMING            3
#define ERROR_FATAL                   7

#define CSR_RD(reg, value) (*(value) = reg_rd(reg))
#define CSR_WR(reg, value, mask) reg_wrm(reg, value, mask)
#define DEV(i) (VTSS_TO_DEV_0 + (0x10000*(i)))

u32 reg_rd(u32 reg) ;
void reg_wr(u32 reg, u32 value) ;
void reg_wrm(u32 reg, u32 value, u32 mask) ;

#if 0 //Jmaes
#define VTSS_E(x) printf("Error: " x)
//#define VTSS_E printf
void vtss_sd6g65_mcb_transfer (u32 addr);
void vtss_sd6g65_mcb_readback (u32 addr);
vtss_rc vtss_ferret_sd6g_ib_cal(void);
vtss_rc vtss_ferret_sd6g_cfg_qsgmii(u32 addr);
vtss_rc vtss_ferret_sd6g_cfg_sgmii(u32 addr);
#endif
#endif

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
