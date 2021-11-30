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

#ifndef __PHYMAP_H__
#define __PHYMAP_H__

#if 0   // Uncalled function
uchar phy_map_coma_mode_disable (vtss_port_no_t port_no) small;
#endif  // Uncalled function
uchar phy_map_miim_no           (vtss_port_no_t port_no) small;
uchar phy_map_phy_no            (vtss_port_no_t port_no) small;
bool  phy_map                   (vtss_port_no_t port_no) small;
uchar phy_map_serdes            (vtss_port_no_t port_no) small;

// Update serdes interface mode when sfp_detect(chip_port) != phy_map_miim_no(chip_port)
void  phy_map_serdes_if_update  (vtss_port_no_t port_no, uchar mac_if) small;

// Restore serdes interface mode (when serdes interface mode is configured as Auto selection via SFP info.
// The value is 0xa (See the definition of CPORT_MAPTO_MIIMBUS in src/config/phyconf.h)
void phy_map_serdes_if_restore(vtss_cport_no_t chip_port) small;

#endif

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
