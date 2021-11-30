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
#include "sysutil.h"
#include "event.h"

#include "interrupt.h"
#include "hwport.h"
#include "spiflash.h"
#include "timer.h"
#include "uartdrv.h"
#include "phytsk.h"
#include "print.h"
#include "clihnd.h"
#include "phydrv.h"
#include "phymap.h"
#include "phy_family.h"
#include "phy_base.h"
#include "h2.h"
#include "h2txrx.h"

#include "misc2.h"
#include "i2c_h.h"
#if UNMANAGED_PORT_STATISTICS_IF
#include "h2stats.h"
#endif

#include "taskdef.h"

#if TRANSIT_FAN_CONTROL
#include "fan_api.h"
#endif

#if TRANSIT_SNMP
#include "snmp.h"
#include "traps.h"
#endif /* TRANSIT_SNMP */

#if TRANSIT_LLDP
#include "lldp.h"
#endif /* TRANSIT_LLDP */

#if TRANSIT_EEE
#include "eee_api.h"
#include "eee_base_api.h"
#endif

#if TRANSIT_LOOPDETECT
#include "loopdet.h"
#endif

#if TRANSIT_POE
#include "poetsk.h"
#endif /* TRANSIT_POE */

#if TRANSIT_POE_LLDP
#include "poe_os.h"
#endif

#if FRONT_LED_PRESENT
#include "ledtsk.h"
#endif

#include "main.h"
#include "stdio.h"


#include "vtss_ocelot_regs_devcpu_gcb.h"
#include "vtss_ocelot_regs_icpu_cfg.h"
#include "vtss_ocelot_regs_uart.h"
#include "vtss_ocelot_regs_hsio.h"
#include "h2io.h"
void vtss_sd6g65_mcb_transfer (u32 addr) {

  u32 value;

  CSR_WR(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG,
         VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(addr) |
         VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT(1),
         VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR |
         VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT);

  do {
    CSR_RD(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG, &value);
  } while (VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT(value) == 1);
}

void vtss_sd6g65_mcb_readback (u32 addr) {

  u32 value;

  CSR_WR(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG,
         VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(addr) |
         VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT(1),
         VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR |
         VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT);

  do {
    CSR_RD(VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG, &value);
  } while (VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT(value) == 1);
}


/*****************************************************************************************/
/* vtss_ferret_sd6g_cfg_sgmii (SD6G setup function) expects that sd6g ib-calibration has */
/* already been executed (use vtss_ferret_sd6g_ib_cal for purpose of sd6g ib-cal)        */
/*****************************************************************************************/

vtss_rc vtss_ferret_sd6g_cfg_sgmii(u32 addr)
{
  vtss_rc status = VTSS_RC_OK;
  u32     value;

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE(1) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(1),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(7),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(2) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(48),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(5),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(6),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(7) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ(13),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(3),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(60),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  vtss_sd6g65_mcb_transfer (addr);

  VTSS_MSLEEP(2);

  vtss_sd6g65_mcb_readback (addr);

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_NOT_DONE is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_OUT_OF_RANGE_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(0),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL);

  vtss_sd6g65_mcb_transfer (addr);

  return status;
}

/*****************************************************************************************/
/* vtss_ferret_sd6g_cfg_qsgmii (SD6G setup function) expects that sd6g ib-calibration has */
/* already been executed (use vtss_ferret_sd6g_ib_cal for purpose of sd6g ib-cal)        */
/*****************************************************************************************/

vtss_rc vtss_ferret_sd6g_cfg_qsgmii(u32 addr)
{
  vtss_rc status = VTSS_RC_OK;
  u32     value;

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE(1) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(1),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(5) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(48),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(5),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(6),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(7) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ(13),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(3),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(120),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(3) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  vtss_sd6g65_mcb_transfer (addr);

  VTSS_MSLEEP(2);

  vtss_sd6g65_mcb_readback (addr);

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_NOT_DONE is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_OUT_OF_RANGE_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(0),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL);

  vtss_sd6g65_mcb_transfer (addr);

  return status;
}

/*****************************************************************************************/
/* vtss_ferret_sd6g_cfg_xaui (SD6G setup function) expects that sd6g ib-calibration has */
/* already been executed (use vtss_ferret_sd6g_ib_cal for purpose of sd6g ib-cal)        */
/*****************************************************************************************/

static vtss_rc vtss_ferret_sd6g_cfg_xaui(u32 addr)
{
  vtss_rc status = VTSS_RC_OK;
  u32     value;

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(0) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE(1) |
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(1),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE |
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(5) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(48),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(5),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(6),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(7) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ(13),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(3),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4 |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(48),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(1) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(1),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA);

  vtss_sd6g65_mcb_transfer (addr);

  VTSS_MSLEEP(2);

  vtss_sd6g65_mcb_readback (addr);

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_NOT_DONE is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_OUT_OF_RANGE_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_RD(VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS, &value);
  if (VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR(value) != 0) {
    VTSS_E("HSIO::SERDES6G_PLL_STATUS.PLL_CAL_ERR is not 0!");
    status = VTSS_RC_ERROR;
  };

  CSR_WR(VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG,
         VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(0),
         VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST);

  vtss_sd6g65_mcb_transfer (addr);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP);

  CSR_WR(VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG,
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(0) |
         VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(0),
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI |
         VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL);

  vtss_sd6g65_mcb_transfer (addr);

  return status;
}
