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


#ifndef __H2E2ETC_H__
#define __H2E2ETC_H_

#include "common.h"

#if TRANSIT_E2ETC
/** \brief EEE port configuration */
typedef struct
{
    BOOL              e2etc_ena;           /**< PTP enabled */
    ushort            ingress_latency;     /**< Expected delay at ingress */
    ushort            egress_latency;      /**< Expected delay at egress  */
} e2etc_conf_t;

/**
 * \brief  Initialize PTP 
 * \return None.
 **/

 void h2_e2etc_init(void);

/**
 * \brief  Set E2E TC configuration
 *
 * \param cport_no [IN]  Chip Port number.
 *
 * \param conf [IN]     New configuration for the port.
 *
 * \return None.
 **/
void h2_e2etc_conf_set(const uchar cport_no, const e2etc_conf_t * const conf);

/**
 * \brief  Set ingress and egress latencies according to speed 
 *
 * \param cport_no [IN]  Chip Port number.
 *
 * \return None.
 **/

void e2etc_latency_set(const uchar chip_port);
#endif
#endif /* __H2_E2ETC_H__ */

