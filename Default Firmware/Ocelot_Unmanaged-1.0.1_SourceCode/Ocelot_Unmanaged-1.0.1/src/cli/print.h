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

#ifndef __PRINT_H__
#define __PRINT_H__


#include "common.h"         // For port_bit_mask_t
#include "txt_moredef.h"


/* Define DEBUG_PRINTF_ENABLE to enable the debug_printf() API */
//#define DEBUG_PRINTF_ENABLE


void print_str (const char *s);
void println_str (const char *s); // Print string and ending with a new line
void print_binary_32(ulong value);
void print_parse_info_32(ulong reg_val);
void print_hex_b (uchar value);
void print_hex_w (ushort value);
void print_hex_dw (ulong value);
void print_dec (ulong value);
void print_hex_prefix (void);
void print_cr_lf (void);
void print_ch (uchar ch);
void print_spaces (uchar count);
void print_dec_right (ulong value);
void print_dec_nright (ulong value, uchar fieldwidth);
void print_dec_16_right (ushort value, uchar width);
void print_ip_addr (const uchar xdata *ip_addr);
void print_line (uchar width);
void print_mac_addr (const uchar *mac_addr);
void print_port_mac_addr (uchar port_no);
void print_dec_8_right_2 (uchar value);
void print_n_str (const char *s,uchar nchar_width);

#if TRANSIT_FTIME
void print_uptime(void);

/**
 * Print the delta time of consecutive checks.
 *
 * @param check Supply 0 to record current time and does not print any thing.
 *              Supply 1-9 to print the delta time from previous check.
 */
void print_delta(uchar check);
#endif

#if defined(DEBUG_PRINTF_ENABLE)
/* Not implement all format types, only the following types is supported:
 * 
 * %%       - print '%'
 * %c       - character
 * %s       - string
 * %d, %u   - decimal integer
 * %x       - hex integer
 */
void debug_printf(const char *fmt, ...);
#endif // DEBUG_PRINTF_ENABLE

#if TRANSIT_UNMANAGED_MAC_OPER_GET
void print_port_list(port_bit_mask_t port_mask);
#endif // TRANSIT_UNMANAGED_MAC_OPER_GET

#endif /* __PRINT_H__*/

