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

#ifndef LLDP_TLV_H
#define LLDP_TLV_H

#include "lldp_os.h"

#define LLDP_CHASSIS_ID_SUBTYPE_MAC_ADDRESS 4
#define LLDP_PORT_ID_SUBTYPE_LOCAL 7

typedef enum {
    LLDP_TLV_BASIC_MGMT_END_OF_LLDPDU      = 0,
    LLDP_TLV_BASIC_MGMT_CHASSIS_ID         = 1,
    LLDP_TLV_BASIC_MGMT_PORT_ID            = 2,
    LLDP_TLV_BASIC_MGMT_TTL                = 3,
    LLDP_TLV_BASIC_MGMT_PORT_DESCR         = 4,
    LLDP_TLV_BASIC_MGMT_SYSTEM_NAME        = 5,
    LLDP_TLV_BASIC_MGMT_SYSTEM_DESCR       = 6,
    LLDP_TLV_BASIC_MGMT_SYSTEM_CAPA        = 7,
    LLDP_TLV_BASIC_MGMT_MGMT_ADDR          = 8,
    LLDP_TLV_ORG_TLV                       = 127,
    LLDP_TLV_ORG_EEE_TLV                   = 128
} lldp_tlv_t;


lldp_u16_t lldp_tlv_add(lldp_u8_t xdata * buf, lldp_u16_t cur_len, lldp_tlv_t tlv, lldp_port_t port);
lldp_u16_t lldp_tlv_add_zero_ttl (lldp_u8_t xdata * buf, lldp_u16_t cur_len);
lldp_u32_t lldp_tlv_mgmt_addr_len (void);

#define lldp_tlv_get_port_id_subtype() LLDP_PORT_ID_SUBTYPE_LOCAL
#define lldp_tlv_get_port_descr(p,b) lldp_os_get_if_descr(p,b)
#define lldp_tlv_get_chassis_id_subtype() LLDP_CHASSIS_ID_SUBTYPE_MAC_ADDRESS
#define lldp_tlv_get_system_name(b) lldp_os_get_system_name(b)
#define lldp_tlv_get_system_descr(b) lldp_os_get_system_descr(b)
lldp_u8_t lldp_tlv_get_local_port_id (lldp_port_t port, lldp_u8_t xdata* port_str);

#endif


