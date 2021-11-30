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
#include "main.h"
#include "timer.h"
#include "vtss_api_base_regs.h"
#include "h2io.h"
#include "h2vlan.h"
#include "misc2.h"
#ifndef NDEBUG
#include "print.h"
#endif

/*****************************************************************************
 *
 *
 * Defines
 *
 *
 *
 ****************************************************************************/

/* VLAN table commands */
#define VLAN_TAB_IDLE  0
#define VLAN_TAB_READ  1
#define VLAN_TAB_WRITE 2
#define VLAN_TAB_CLEAR 3

/*****************************************************************************
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
static void _h2_vlan_do_command(ulong aces_value);

/*****************************************************************************
 *
 *
 * Local data
 *
 *
 *
 ****************************************************************************/

/* ************************************************************************ */
void h2_vlan_clear_tab (void)
/* ------------------------------------------------------------------------ --
 * Purpose     : Clear vlan table in switch chip.
 * Remarks     :
 * Restrictions:
 * See also    :
 * Example     :
 ****************************************************************************/
{
    _h2_vlan_do_command(VTSS_F_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(VLAN_TAB_CLEAR));
}

static void _h2_vlan_do_command(ulong aces_value)
{
    ulong cmd;

    H2_WRITE(VTSS_ANA_ANA_TABLES_VLANACCESS, aces_value);

    start_timer(MSEC_1000);
    do {
        H2_READ(VTSS_ANA_ANA_TABLES_VLANACCESS, cmd);
    } while (VTSS_X_ANA_ANA_TABLES_VLANACCESS_VLAN_TBL_CMD(cmd) != VLAN_CMD_IDLE && !timeout());

#ifndef NDEBUG
    if (timeout()) {
        println_str("%% Timeout when calling _h2_vlan_do_command()");
    }
#endif
}
