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

#ifndef __UARTDRV_H__
#define __UARTDRV_H__

#define IIR_INTERRUPT_ID_MASK 0x0F
#define IIR_RX_AVAIL		  0x04
#define IIR_RX_CHAR_TIMEOUT	  0x0C
#define IIR_TX_EMPTY		  0x02

extern bit uart_rx_buf_overrun;

void  uart_init (void) small;
void  uart_interrupt (void) small;
void  uart_redirect (uchar xdata *ptr) small;
void  uart_interrupt (void) small;
bool  uart_byte_ready (void) small;
uchar uart_get_byte (void) small;
void  uart_put_byte (uchar ch) small;


#endif /* __UARTDRV_H__ */
