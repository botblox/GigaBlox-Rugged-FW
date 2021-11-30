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

#ifndef LLDP_H
#define LLDP_H

#include "lldp_os.h"

#define LLDP_ETHTYPE 0x88CC

/* IEEE 802.3 OUI */
extern const uchar ieee_802_3_oui_header[3];

#if TRANSIT_LLDP
extern const mac_addr_t xdata mac_addr_lldp;
#endif /* TRANSIT_LLDP */

void lldp_init (void);
void lldp_set_port_enabled (lldp_port_t port, lldp_u8_t enabled);
void lldp_1sec_timer_tick (void);
void lldp_frame_received (lldp_port_t port_no, lldp_u8_t xdata * frame, lldp_u16_t len);
void lldp_pre_port_disabled (lldp_port_t port_no);
void lldp_set_timing_changed (void);

#if TRANSIT_UNMANAGED_SYS_MAC_CONF || defined(TRANSIT_WEB)
void lldp_something_changed_local (void);
#endif /* TRANSIT_UNMANAGED_SYS_MAC_CONF || defined(TRANSIT_WEB) */

lldp_counter_t lldp_get_tx_frames (lldp_port_t port);
lldp_counter_t lldp_get_rx_total_frames (lldp_port_t port);
lldp_counter_t lldp_get_rx_error_frames (lldp_port_t port);
lldp_counter_t lldp_get_rx_discarded_frames (lldp_port_t port);
lldp_counter_t lldp_get_TLVs_discarded (lldp_port_t port);
lldp_counter_t lldp_get_TLVs_unrecognized (lldp_port_t port);
lldp_counter_t lldp_get_TLVs_org_discarded (lldp_port_t port);
lldp_counter_t lldp_get_ageouts (lldp_port_t port);
#endif


