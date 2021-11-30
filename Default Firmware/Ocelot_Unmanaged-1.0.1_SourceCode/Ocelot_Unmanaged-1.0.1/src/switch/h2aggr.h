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

#ifndef __H2AGGR_H__
#define __H2AGGR_H__

#define MAX_KEY   16

void   h2_aggr_init (void);
void   h2_aggr_set_mode (uchar mode);
uchar h2_aggr_add (port_bit_mask_t i_port_mask);
uchar  h2_aggr_delete (port_bit_mask_t port_mask);
void   h2_aggr_update (void);
void   h2_aggr_setup (uchar port_no);
uchar  h2_aggr_find_group (port_bit_mask_t port_mask);
#if TRANSIT_RSTP_TRUNK_COWORK && TRANSIT_RSTP
uchar chk_staggr_member (uchar pno);
#endif

#define ERROR_AGGR_1 1
#define ERROR_AGGR_2 2
#define ERROR_AGGR_3 3
#define ERROR_AGGR_4 4

#endif
