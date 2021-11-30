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

#ifndef __H2SDCFG_H__
#define __H2SDCFG_H__

/** \brief Serdes macro mode */
typedef enum
{
    VTSS_SERDES_MODE_DISABLE,       /**< Disable serdes */
    VTSS_SERDES_MODE_XAUI_12G,      /**< XAUI 12G mode  */
    VTSS_SERDES_MODE_XAUI,          /**< XAUI 10G mode  */
    VTSS_SERDES_MODE_RXAUI,         /**< RXAUI 10G mode */
    VTSS_SERDES_MODE_RXAUI_12G,     /**< RXAUI 12G mode */
    VTSS_SERDES_MODE_2G5,           /**< 2.5G mode      */
    VTSS_SERDES_MODE_QSGMII,        /**< QSGMII mode    */
    VTSS_SERDES_MODE_SGMII,         /**< SGMII mode     */
    VTSS_SERDES_MODE_100FX,         /**< 100FX mode     */
    VTSS_SERDES_MODE_1000BaseX,     /**< 1000BaseX mode */
    VTSS_SERDES_MODE_SFI,           /**< LAN/10G mode   */
    VTSS_SERDES_MODE_SFI_DAC,       /**< LAN/10G DAC(CU)*/
    VTSS_SERDES_MODE_SFI_SR,        /**< Short Range > */
    VTSS_SERDES_MODE_SFI_ZR,        /**< ZR with APC hardware algorithm > */
    VTSS_SERDES_MODE_SFI_BP,        /**< Backplane > */
    VTSS_SERDES_MODE_SFI_B2B,       /**< Bord to Board > */
    VTSS_SERDES_MODE_SFI_PR_NONE,   /**< No preset > */
    VTSS_SERDES_MODE_IDLE,          /**< Send idles (port appears as down for LP) */
    VTSS_SERDES_MODE_TEST_MODE,     /**< Send fixed test pattern (port appears as up for LP, but no frame rx/tx) */
    VTSS_SERDES_MODE_PCIE           /**< PCIE mode */
} vtss_serdes_mode_t;

void h2_sd6g_write(ulong addr);
void h2_sd6g_read(ulong addr);
void h2_sd6g_cfg(vtss_serdes_mode_t mode, ulong addr);

void h2_serdes_macro_config (void);
void h2_sd6g_cfg_change(vtss_serdes_mode_t mode, ulong addr);
uchar h2_serdes_macro_phase_loop_locked (void);

void h2_sd1g_write(ulong addr);
void h2_sd1g_read(ulong addr);
void h2_sd1g_cfg(vtss_serdes_mode_t mode, ulong addr);

#endif  // __H2SDCFG_H__
