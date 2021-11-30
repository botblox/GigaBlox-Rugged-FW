#ifndef _VTSS_API_BASE_REGS_H_
#define _VTSS_API_BASE_REGS_H_

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

#if defined(VTSS_ARCH_OCELOT)
#include "vtss_ocelot_reg.h"
#include "vtss_ocelot_regs.h"
#include "vtss_ocelot_regs_dev.h"
#include "vtss_ocelot_regs_twi.h"
#include "vtss_ocelot_regs_hsio.h"
#include "vtss_ocelot_regs_icpu_cfg.h"

#elif defined(VTSS_ARCH_LUTON26)
#include "vtss_luton26_reg.h"
#include "vtss_luton26_regs.h"
#include "vtss_luton26_regs_dev.h"
#include "vtss_luton26_regs_twi.h"
#include "vtss_luton26_regs_icpu_cfg.h"
#endif // VTSS_ARCH_OCELOT

#endif // __VTSS_API_BASE_REGS_H__
