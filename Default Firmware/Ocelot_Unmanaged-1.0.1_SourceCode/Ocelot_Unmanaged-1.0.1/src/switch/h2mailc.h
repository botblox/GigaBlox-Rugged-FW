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

#ifndef __H2MAILC_H__
#define __H2MAILC_H__


/* The external CPU can communicate with the embedded 8051 iCPU via the 32-bit
 * internal register MAILBOX.
 * The 32-bit register value is split into three parts:
 * <conf_oper>( 2-bit) - The operation between the embedded 8051 iCPU and external CPU
 * <conf_type>( 6-bit) - Configure type.
 * <conf_data>(24-bit) - Configure data, it depends on which configured type is defined.
 */

typedef enum {
    H2MAILC_OPER_IN_PROG,  // The embedded 8051 iCPU is in progressing
    H2MAILC_OPER_READY,    // The embedded 8051 iCPU is ready for the requirement.
    H2MAILC_OPER_REQUIRE,  // A requirement is initiated by the external CPU.
    H2MAILC_OPER_REPLY     /* The embedded 8051 iCPU has done the requirement
                            * and ready for the next requirement.
                            * Notice that the return code is filled in the <conf_data>
                            * fields, 0 for successful case, otherwise, failed case.
                            */
} h2mailc_oper_t;

typedef enum {
    H2MAILC_TYPE_SYS_MAC_SET_HIGH,  // Set higher 3 bytes of the system MAC address.
    H2MAILC_TYPE_SYS_MAC_SET_LOW,   // Set lower 3 bytes of the system MAC address.
    H2MAILC_TYPE_SYS_MAC_APPLY,     // Apply the system MAC address.

#if TRANSIT_LACP
    H2MAILC_TYPE_LACP_ENABLE,       // Enable LACP and set key on specific port.
    H2MAILC_TYPE_LACP_DISABLE,      // Disable LACP on specific port.
#endif // TRANSIT_LACP

    H2MAILC_TYPE_CNT                // Total count of types
} h2mailc_type_t;


typedef union {
    struct {
#if defined(H2_LSB_FIRST)
        h2mailc_oper_t  conf_oper: 2;
        h2mailc_type_t  conf_type: 6;
#else // MSB-first
        h2mailc_type_t  conf_type: 6;
        h2mailc_oper_t  conf_oper: 2;
#endif
        union {
            // General configured data
            struct {
                uchar   data2;
                uchar   data1;
                uchar   data0;
            } general;

            // Lower 3 bytes of system MAC address
            struct {
                uchar   mac2;
                uchar   mac1;
                uchar   mac0;
            } sys_mac_l;

            // Higher 3 bytes of system MAC address
            struct {
                uchar   mac5;
                uchar   mac4;
                uchar   mac3;
            } sys_mac_h;

#if TRANSIT_LACP
            // LACP configuration: <uport>(8-bit), <key>(16-bit)
            struct {
                vtss_uport_no_t uport;
                ushort          key;
            } lacp_conf;
#endif // TRANSIT_LACP
        } conf_data;
    } reg_bit;

    ulong reg_value;
} h2mailc_conf_t;

void h2mailc_conf_set(h2mailc_conf_t comm_conf);
void h2mailc_tsk(void);

#endif // __H2MAILC_H__
