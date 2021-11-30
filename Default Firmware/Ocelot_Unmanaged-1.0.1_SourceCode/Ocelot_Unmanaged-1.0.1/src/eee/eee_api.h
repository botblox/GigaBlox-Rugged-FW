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

#ifndef _EEE_API_H_
#define _EEE_API_H_

#include "h2eee.h"
#include "eee_base_api.h"

//************************************************
// Configuration definition
//************************************************

// Switch configuration (configuration that are local for a switch in the stack)
typedef struct {
    eee_port_conf_t port[NO_OF_BOARD_PORTS];
} eee_conf_t;



//************************************************
// Constants
//************************************************

extern const ushort PHY_WAKEUP_VALUE_1G;
extern const ushort PHY_WAKEUP_VALUE_100;

#if TRANSIT_EEE_LLDP
extern eee_sm_t   eee_sm[NO_OF_BOARD_PORTS];
#endif


void eee_mgmt_int (void);
void eee_mgmt (void);

uchar  read_eee_conf_mode (uchar port_ext);
ushort read_eee_conf_tx_tw (uchar port_ext);
ushort read_eee_conf_rx_tw (uchar port_ext);
uchar  read_eee_conf_fast_queues (uchar port_ext);

void write_eee_conf_mode (uchar port_ext, uchar mode);
void write_eee_conf_tx_tw (uchar port_ext, ushort time);
void write_eee_conf_rx_tw (uchar port_ext, ushort time);
void write_conf_fast_queues (uchar port_ext, uchar fast_queues);
void eee_port_mode_setup(uchar iport);
void eee_port_link_change(uchar iport, BOOL up);
void load_eee_conf (void);
void save_eee_conf (void);

#endif // _EEE_API_H_


//***************************************************************************
//  End of file.
//***************************************************************************
