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

#ifndef __PHYTSK_H__
#define __PHYTSK_H__

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */

/**
 * Tick PHY timers. To be called every 10 msec (approximately).
 *
 * @note    Don't call this from timer interrupt function.
 */
void   phy_timer_10                 (void);

/**
 * Do run-time check on all PHYs.
 * Return 0 when no error occurred.
 */
uchar  phy_check_all                (void);


void   phy_restart                  (vtss_cport_no_t chip_port);

void   phy_state_to_setup           (vtss_cport_no_t chip_port);

#if defined(UNMANAGED_FLOW_CTRL_IF)
void phy_flowcontrol_set(vtss_cport_no_t port_no, BOOL mode_enabled);
#endif // UNMANAGED_FLOW_CTRL_IF

/* Get myself flow control configured mode */
BOOL phy_flowcontrol_get(vtss_cport_no_t chip_port);

/**
 * Init PHY and data used by phy task (actually 'port' task).
 * Return 0 when the operation success
 */
uchar  phy_tsk_init                 (void);

/**
 * Activate state machine for each port/PHY. This is the 'port task' which is
 * performing the port status detection and handles link up / down events.
 */
void   phy_tsk                      (void);

/**
 * Get port current link mode. (from software database)
 */
uchar port_link_mode_get(vtss_cport_no_t chip_port);

/**
 * Get (software) link state (up/down) for specified port.
 *
 * @return TRUE     If link is up.
 * @return FALSE    Otherwise.
 */
BOOL is_port_link(vtss_cport_no_t chip_port);


/**
 * Get link state (up/down) for all chip ports.
 *
 * @retval  Return bit mask where each bit represents a chip port.
 */
port_bit_mask_t linkup_cport_mask_get(void);


#if TRANSIT_VERIPHY


/**
 * Run veriphy on all ports.
 *
 * @todo Run only on PHY ports.
 */
void   phy_veriphy_all              (void);
#endif /* TRANSIT_VERIPHY */

#if TRANSIT_ACTIPHY
/* Set ActiPHY mode operation */
void phy_actiphy_set(BOOL mode_enabled);
#endif /* TRANSIT_ACTIPHY */

#if TRANSIT_FAN_CONTROL || TRANSIT_THERMAL
ushort phy_get_sys_temp             (void);
#endif /* TRANSIT_FAN_CONTROL || TRANSIT_THERMAL */


#if TRANSIT_THERMAL
/**
 * State machine for temperature monitor. Monitor and set up switch port.
 */
void phy_handle_temperature_protect (void);


void phy_temperature_timer_1sec     (void);


#endif /* TRANSIT_THERMAL */


#endif /* __PHYTSK_H__ */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
