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
 * \file eee_base_custom.h
 * \brief For being able to support multiple hardware and software platforms 
 * data and functions that are platform specific are defined in this file.
 * 
 */



#ifndef _EEE_BASE_CUSTOM_H_
#define _EEE_BASE_CUSTOM_H_


//
// Defines for 8051 Platform
//

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */
#include "h2eee.h"
#include "eee_api.h"
#include "lldp.h"
#include "phydrv.h"



#if TRANSIT_EEE_LLDP
    #define EEE_BASE_ENABLE  1
#else
    #define EEE_BASE_ENABLE  0
#endif

#if TRANSIT_EEE
    #define VTSS_FEATURE_EEE 1
#endif 

//#if TRANSIT_EEE && !TRANSIT_LLDP
//    #error "TRANSIT_LLDP must be 1"
//#endif

//  Define the number of ports
#define EEE_NO_OF_PORTS NO_OF_BOARD_PORTS

/*
 * Trace not supported
 * Developer needs manully update code if needs 
 * T_D_PORT
 * T_I_PORT
 */
#include "print.h"

// Define the port number type
#define eee_vtss_port_no_t uchar


// In eee_base the ports are expected to start from port zero. If that is not the case for the platform the
// ports is converted using eee_iport2uport
#define eee_iport2uport(x) (x+1)

#define vtss_eee_port_conf_t eee_port_conf_t



// Define the function for setting the configuration in the API
#define eee_api_conf_set(iport, conf) h2_eee_port_conf_set(iport2cport(iport), conf);

//Define function for getting link partner auto negotiation result
#define eee_link_partner_advertisements_get(iport, lp_advertisement) vtss_phy_eee_link_partner_advertisements_get(iport2cport(iport), lp_advertisement)

// Define speed value for 1G mode.
#define EEE_SPEED_1G 1000


#endif //


//***************************************************************************
//  End of file.
//***************************************************************************
