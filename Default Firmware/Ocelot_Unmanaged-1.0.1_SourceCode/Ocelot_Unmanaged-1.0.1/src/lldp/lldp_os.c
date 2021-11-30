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

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */
#include "lldp_os.h"
#include "timer.h"
#include "vtss_common_os.h"
#include "mib_common.h"
#include "misc2.h"
#include "uartdrv.h"
#include "print.h"
#include "version.h"
#include "txt.h"
#include "txt_moredef.h"
#include "spiflash.h"
#include "lldp_sm.h"
#include "lldp.h"
#include "lldp_private.h"
#include "lldp_tlv.h"

#include "h2txrx.h"
#if TRANSIT_LLDP

/*****************************************************************************
 *
 *
 * Defines
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Typedefs and enums
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Prototypes for local functions
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Public data
 *
 *
 *
 ****************************************************************************/

/*****************************************************************************
 *
 *
 * Local data
 *
 *
 *
 ****************************************************************************/
static lldp_bool_t use_tx_shutdown_buffer = LLDP_FALSE;
static lldp_u8_t tx_shutdown_buffer[64];

static lldp_conf_t lldp_conf;


lldp_timer_t lldp_os_get_msg_tx_interval (void)
{
    return lldp_conf.msgTxInterval; // default : 10
}

lldp_timer_t lldp_os_get_msg_tx_hold (void)
{
    return lldp_conf.msgTxHold; // default : 4
}

lldp_timer_t lldp_os_get_reinit_delay (void)
{
    return lldp_conf.reInitDelay; // default : 2
}

lldp_timer_t lldp_os_get_tx_delay (void)
{
    lldp_timer_t tx_interval = lldp_os_get_msg_tx_interval();
    lldp_timer_t tx_delay = lldp_conf.txDelay;

    /* must not be larger that 0.25 * msgTxInterval*/
    if(tx_delay > (tx_interval/4)) {
        return (tx_interval/4);
    }
    return tx_delay;
}

void lldp_os_set_msg_tx_hold (lldp_timer_t val)
{
    lldp_conf.msgTxHold = val;
}

void lldp_os_set_reinit_delay (lldp_timer_t val)
{
    lldp_conf.reInitDelay = val;
}

void lldp_os_set_tx_delay (lldp_timer_t val)
{
    lldp_conf.txDelay = val;
}

lldp_admin_state_t lldp_os_get_admin_status (lldp_port_t uport)
{
    return lldp_conf.admin_state[uport - 1];
}

void lldp_os_set_admin_status (lldp_port_t uport, lldp_admin_state_t admin_state)
{
    lldp_sm_t xdata * sm;
    lldp_conf.admin_state[uport - 1] = admin_state;
    sm = lldp_get_port_sm(uport);
    sm->adminStatus = admin_state;
    lldp_sm_step(sm);
}

/* return some memory we can use to build up frame in */
lldp_u8_t xdata * lldp_os_get_frame_storage (void)
{
    if(use_tx_shutdown_buffer) {
        return tx_shutdown_buffer;
    }
    return rx_packet;
}

#if TRANSIT_THERMAL
void lldp_os_set_tx_in_progress (lldp_bool_t tx_in_progress)
{
    use_tx_shutdown_buffer = tx_in_progress;
}
#endif

#if !TRANSIT_LLDP_REDUCED
void lldp_os_get_if_descr (lldp_port_t port, lldp_u8_t xdata * dest)
{
    mib_common_get_if_descr(port, dest);
}

void lldp_os_get_system_name (lldp_u8_t xdata * dest)
{
    strcpy(dest, txt_TXT_NO_SWITCH_NAME);
}

void lldp_os_get_system_descr (lldp_u8_t xdata * dest)
{
    mib_common_get_sys_descr(dest);
}


void lldp_os_get_ip_address (lldp_u8_t xdata * dest)
{
    memset(dest, 0, 4);
}
#endif

void lldp_os_set_optional_tlv (lldp_u8_t tlv, lldp_u8_t enabled)
{
    /* perform read-modify-write operation */
    lldp_u16_t tlv_enabled = lldp_conf.tlv_optionals_enabled;

    VTSS_COMMON_TRACE(VTSS_COMMON_TRLVL_DEBUG, ("Set TLV %u to %u", (unsigned)tlv, (unsigned)enabled));

    /* adjust from TLV value to bits */
    if(tlv > LLDP_TLV_ORG_TLV)
        tlv = (tlv - LLDP_TLV_ORG_TLV + 5);
    else
        tlv -= 4;

    write_bit_16(tlv, enabled, &tlv_enabled);

    lldp_conf.tlv_optionals_enabled = tlv_enabled;
}

lldp_u8_t lldp_os_get_optional_tlv_enabled (lldp_u8_t tlv)
{
    lldp_u16_t tlv_enabled = lldp_conf.tlv_optionals_enabled;

    /* adjust from TLV value to bits */
    if(tlv > LLDP_TLV_ORG_TLV)
        tlv = (tlv - LLDP_TLV_ORG_TLV + 5);
    else
        tlv -= 4;
    return test_bit_16(tlv, &tlv_enabled);
}

#if !TRANSIT_LLDP_REDUCED
lldp_u8_t lldp_os_get_ip_enabled (void)
{
    return FALSE;
}
#endif

/* send a frame on external port number */
void lldp_os_tx_frame (lldp_port_t port_no, lldp_u8_t xdata * frame, lldp_u16_t len)
{
    h2_send_frame(port2int(port_no), frame, len);
}

lldp_u32_t lldp_os_get_sys_up_time (void)
{
    return time_since_boot_ticks();
}

void load_lldp_conf (void)
{
    const lldp_u8_t optional_tlvs[] = { LLDP_TLV_BASIC_MGMT_PORT_DESCR,
                                        LLDP_TLV_BASIC_MGMT_SYSTEM_NAME,
                                        LLDP_TLV_BASIC_MGMT_SYSTEM_DESCR,
                                        LLDP_TLV_BASIC_MGMT_SYSTEM_CAPA,
                                        LLDP_TLV_BASIC_MGMT_MGMT_ADDR
#if TRANSIT_EEE
                                        , LLDP_TLV_ORG_EEE_TLV
#endif
                                      };
    uchar port_ext;
    uchar tlv;

    static uchar lldp_conf_init = 0;
    if(!lldp_conf_init) {
        for(port_ext = 1; port_ext <= NO_OF_BOARD_PORTS; port_ext++) {
            /* initial state = rx_and_tx (=1) */
#if TRANSIT_EEE_LLDP
            lldp_conf.admin_state[port_ext - 1] = LLDP_ENABLED_RX_TX;
#if TRANSIT_BPDU_PASS_THROUGH
            h2_bpdu_t_registration(0x0E, TRUE);
#endif
#else
            lldp_conf.admin_state[port_ext - 1] = LLDP_ENABLED_RX_TX;
#if TRANSIT_BPDU_PASS_THROUGH
            h2_bpdu_t_registration(0x0E, FALSE);
#endif
#endif
        }
        /* all optional TLV from basic mgmt set enabled per default except management IP*/
        for(tlv = 0; tlv < ARRAY_LENGTH(optional_tlvs); tlv++) {
            if(optional_tlvs[tlv] == LLDP_TLV_BASIC_MGMT_MGMT_ADDR)
                lldp_os_set_optional_tlv(optional_tlvs[tlv], 0);
            else
#if !TRANSIT_EEE_LLDP
                if(optional_tlvs[tlv] == LLDP_TLV_ORG_EEE_TLV)
                    lldp_os_set_optional_tlv(optional_tlvs[tlv], 0);
                else
#endif
                    lldp_os_set_optional_tlv(optional_tlvs[tlv], 1);
        }
        lldp_os_set_reinit_delay(2);
        lldp_os_set_msg_tx_hold(4);
        lldp_os_set_tx_delay(2);

        lldp_conf.msgTxInterval = 10; /* 802.3az defined 10 seconds. */

        lldp_conf_init = 1;
    }
}

#endif


