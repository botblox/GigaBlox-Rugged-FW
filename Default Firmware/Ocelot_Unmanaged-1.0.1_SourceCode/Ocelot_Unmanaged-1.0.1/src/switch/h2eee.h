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

/**
 * \file h2eee.h
 * \brief Luton26 EEE API
 * \details This header file describes Luton26 eee functions.
 */

#ifndef __H2_EEE_H__
#define __H2_EEE_H__

/** \brief EEE port configuration */
typedef struct
{
    BOOL              eee_ena;           /**< EEE enabled */
    uchar             eee_fast_queues;   /**< Queues set in this mask will activate egress path as soon as any data is avaiable. */
    ushort            tx_tw;             /**< Time from path is activated until frame transmission restarted.*/
    ushort            rx_tw;
    uchar             lp_advertisement;  /**  Link partner EEE advertisement. Bit 0 = Link partner advertises 100BASE-T capability. Bit 1 = Link partner advertises 1000BASE-T capability. */
} eee_port_conf_t;

/**
 * \brief  Set EEE configuration
 *
 * \param port_no [IN]  Port number.
 *
 * \param conf [IN]     New configuration for the port.
 *
 * \return None.
 **/
void h2_eee_port_conf_set(const vtss_cport_no_t chip_port, const eee_port_conf_t * const conf);

#endif /* __H2_EEE_H__ */










