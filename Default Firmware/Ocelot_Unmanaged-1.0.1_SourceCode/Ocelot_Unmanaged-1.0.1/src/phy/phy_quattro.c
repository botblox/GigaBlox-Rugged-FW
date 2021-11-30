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
#include "timer.h"
#include "print.h"

#include "phydrv.h"
#include "phy_base.h"
#include "phy_family.h"

#define PHY_DEBUG (0)

#if VTSS_QUATTRO

/****************************************************************************
 *
 *
 * Defines
 *
 *
 ****************************************************************************/

/****************************************************************************
 *
 *
 * Typedefs and enums
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
 * Local data
 *
 *
 *
 ****************************************************************************/


/*****************************************************************************
 *
 *
 * PHY initialization sequences
 *
 *
 *
 ****************************************************************************/

/*
** Initialization sequence for 8224/8244 PHYs
*/
vtss_rc init_seq_8224(
    vtss_port_no_t          port_no,
    phy_id_t                *phy_id
) {
    phy_page_tp(port_no);
    phy_write(port_no,  8, 0x0212);

    phy_page_tr(port_no);
    phy_write(port_no, 16, 0xafa4);
    phy_write(port_no, 18, 0x000f);
    phy_write(port_no, 17, 0x492a);
    phy_write(port_no, 16, 0x8fa4);

    phy_page_tp(port_no);
    phy_write(port_no,  8, 0x0012);

    phy_page_tp(port_no);
    phy_write(port_no,  8, 0x0212);

    phy_page_tr(port_no);
    phy_write(port_no, 18, 0x0004);
    phy_write(port_no, 17, 0x0671);
    phy_write(port_no, 16, 0x8fae);

    phy_page_tp(port_no);
    phy_write(port_no,  8, 0x0012);

    phy_page_std(port_no);
    phy_write(port_no, 18, 0x0049);

    phy_page_tp(port_no);
    phy_write(port_no,  3, 0xf082);
    phy_write(port_no,  3, 0xf082);

    phy_page_std(port_no);

    vtss_phy_enab_smrt_premphasis(port_no);

    phy_id = 0; /* fix compiler wanring */

    return VTSS_RC_OK;
}

#endif

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
