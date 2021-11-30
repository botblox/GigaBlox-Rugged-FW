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
#ifndef __MISC3_H__
#define __MISC3_H__

char mac_cmp (uchar xdata *mac_addr_1, uchar xdata *mac_addr_2) small;
char ip_cmp (uchar xdata *ip_addr_1, uchar xdata *ip_addr_2) small;
void mac_copy (uchar xdata *mac_addr_dst, uchar xdata *mac_addr_src);
void ip_copy (uchar xdata *dst_ip_addr, uchar xdata *src_ip_addr) small;

uchar mem_cmp(uchar xdata *dst_mem_addr, uchar xdata *src_mem_addr, uchar size) small;
uchar mem_copy(uchar xdata *dst_mem_addr, uchar xdata *src_mem_addr, uchar size) small;
uchar mem_set(uchar xdata *dst_mem_addr, uchar value, uchar size) small;
#endif
