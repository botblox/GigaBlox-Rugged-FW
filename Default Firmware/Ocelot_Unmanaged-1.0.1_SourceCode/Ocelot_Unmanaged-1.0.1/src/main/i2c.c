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

#include <intrins.h>

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */

#include "vtss_api_base_regs.h"
#include "h2io.h"
#include "misc2.h"

#if TRANSIT_SFP_DETECT
#if USE_SW_TWI

#define SDA_BIT_MASK    (1UL << SDA_BIT)
#define CLK_BIT_MASK    (1UL << CLK_BIT)
#define SDA_BIT_OE_MASK (1UL << SDA_BIT_OE)
#define CLK_BIT_OE_MASK (1UL << CLK_BIT_OE)

static void scl_set () small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, CLK_BIT_MASK, CLK_BIT_MASK);
}

static void scl_reset () small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, 0, CLK_BIT_MASK);
}

static void scl_delay() small
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

static void sda_reset() small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, 0, SDA_BIT_MASK);
}

static void sda_set() small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT, SDA_BIT_MASK, SDA_BIT_MASK);
}

static void sda_dir_in () small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, 0, SDA_BIT_OE_MASK);
}

static void sda_dir_out () small
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, SDA_BIT_OE_MASK, SDA_BIT_OE_MASK);
}

static uchar sda_get () small
{
    ulong reg;
    H2_READ(VTSS_DEVCPU_GCB_GPIO_GPIO_IN, reg);
    if(test_bit_32(SDA_BIT, &reg)) {
        return 1;
    }
    return 0;
}

void  i2c_start (void)
{
    H2_WRITE_MASKED(VTSS_DEVCPU_GCB_GPIO_GPIO_OE, SDA_BIT_OE_MASK|CLK_BIT_OE_MASK , SDA_BIT_OE_MASK|CLK_BIT_OE_MASK)
    sda_set();
    scl_set();
    scl_delay();

    sda_reset();
    scl_delay();
    scl_reset();
}
void  i2c_stop (void)
{
    sda_reset();
    scl_delay();
    scl_set();
    scl_delay();
    sda_set();
}

uchar i2c_send_byte (uchar d)
{
    uchar bit_no;
    uchar ret;
    for(bit_no = 0; bit_no < 8; bit_no++) {
        if(test_bit_8((7-bit_no), &d)) {
            sda_set();
        } else {
            sda_reset();
        }
        scl_set();
        scl_delay();
        scl_reset();
        scl_delay();
    }
    sda_set();
    sda_dir_in();
    scl_set();
    scl_delay();
    ret = sda_get();
    scl_reset();
    scl_delay();
    sda_dir_out();

    return ret;
}

uchar i2c_get_byte (uchar do_ack)
{
    uchar bit_no;
    uchar ret = 0;
    sda_set();
    sda_dir_in();
    for(bit_no = 0; bit_no < 8; bit_no++) {
        scl_set();
        scl_delay();
        ret = (ret << 1) | sda_get();
        scl_reset();
        scl_delay();
    }
    sda_dir_out();
    if(do_ack) {
        sda_reset();
    } else {
        sda_set();
    }
    scl_set();
    scl_delay();
    scl_reset();
    scl_delay();

    return ret;

}
#endif /* USE_SW_TWI */
#endif /* TRANSIT_SFP_DETECT */
