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

#ifndef LLDP_SM_H
#define LLDP_SM_H

/* import of lldp types */
#include "lldp_os.h"

typedef struct {
    /* Transmission counters */
    lldp_counter_t statsFramesOutTotal;

    /* Reception counters */
    lldp_counter_t statsAgeoutsTotal;
    lldp_counter_t statsFramesDiscardedTotal;
    lldp_counter_t statsFramesInErrorsTotal;
    lldp_counter_t statsFramesInTotal;
    lldp_counter_t statsTLVsDiscardedTotal;
    lldp_counter_t statsTLVsUnrecognizedTotal;

    /* Special counter for this implementation, counting unprocessed
    ** opganizationally defined TLVs */
    lldp_counter_t statsOrgTVLsDiscarded;
} lldp_statistics_t;

typedef struct {
    /* Transmit timers */
    lldp_timer_t txShutdownWhile;
    lldp_timer_t txDelayWhile;
    lldp_timer_t txTTR;
} lldp_timers_t;

typedef struct {

    enum {
        TX_INVALID_STATE,
        TX_LLDP_INITIALIZE,
        TX_IDLE,
        TX_SHUTDOWN_FRAME,
        TX_INFO_FRAME,
    } state;

    lldp_bool_t somethingChangedLocal;
    lldp_timer_t txTTL;

    lldp_bool_t re_evaluate_timers;
} lldp_tx_t;


typedef struct {

    enum {
        RX_INVALID_STATE,
        LLDP_WAIT_PORT_OPERATIONAL,
        DELETE_AGED_INFO,
        RX_LLDP_INITIALIZE,
        RX_WAIT_FOR_FRAME,
        RX_FRAME,
        DELETE_INFO,
        UPDATE_INFO,
    } state;

    lldp_bool_t badFrame;
    lldp_bool_t rcvFrame;
    lldp_bool_t rxChanges;
    lldp_bool_t rxInfoAge;
    lldp_timer_t rxTTL;
    lldp_bool_t somethingChangedRemote;
} lldp_rx_t;


typedef struct {
    lldp_tx_t tx;
    lldp_rx_t rx;
    lldp_timers_t timers;
    lldp_statistics_t stats;

    lldp_admin_state_t adminStatus;
    lldp_bool_t portEnabled;
    lldp_bool_t initialize;
    lldp_port_t port_no;
} lldp_sm_t;


void lldp_sm_step (lldp_sm_t xdata * sm);
void lldp_sm_init (lldp_sm_t xdata * sm, lldp_port_t port);
void lldp_port_timers_tick(lldp_sm_t xdata *sm);
#endif

