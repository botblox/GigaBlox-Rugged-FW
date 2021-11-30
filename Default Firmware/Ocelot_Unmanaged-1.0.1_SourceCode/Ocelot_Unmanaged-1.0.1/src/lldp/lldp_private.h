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

#ifndef LLDP_PRIVATE_H
#define LLDP_PRIVATE_H

#include "lldp_os.h"

lldp_sm_t xdata * lldp_get_port_sm (lldp_port_t port);
void lldp_tx_initialize_lldp (lldp_sm_t xdata * sm);
void lldp_construct_info_lldpdu(lldp_port_t port_no);
void lldp_construct_shutdown_lldpdu(lldp_port_t port_no);
void lldp_tx_frame(lldp_port_t port_no);
void lldp_rx_initialize_lldp (lldp_port_t port);
void lldp_rx_process_frame (lldp_sm_t xdata * sm);
#endif



