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
#include <string.h>

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */
#include "misc1.h"
#include "misc2.h"
#include "misc3.h"
#include "hwport.h"

#if !defined(BRINGUP)
#if TRANSIT_LLDP
/* ************************************************************************ */
uchar xmemcmp(const uchar xdata *dst, const uchar xdata *src, ushort length)
/* ------------------------------------------------------------------------ --
 * Purpose     : Compare two memory blocks
 * Remarks     :
 * Restrictions:
 * See also    :
 * Example     :
 ****************************************************************************/
{
    uchar xdata *p_dst;
    uchar xdata *p_src;
    ushort count;
    uchar  ret;
    p_dst = dst;
    p_src = src;
    count = length;

    ret = 0;
    while(ret == 0 && count != 0) {
        if(count > 255) {
            ret = mem_cmp(p_dst, p_src, 255);
            p_dst += 255;
            p_src += 255;
            count -= 255;
        } else {
            ret = mem_cmp(p_dst, p_src, count);
            count -= count;
        }
    }
    return ret;
}
#endif // TRANSIT_LLDP
#endif /* !BRINGUP */

#ifndef NO_DEBUG_IF
/* ************************************************************************ */
uchar ascii_to_hex_nib (uchar ch)
/* ------------------------------------------------------------------------ --
 * Purpose     : Convert an ASCII hex digit to a hex digit.
 * Remarks     :
 * Restrictions:
 * See also    :
 * Example     :
 ****************************************************************************/
{
    ch = conv_to_upper_case(ch);

    if (('0' <= ch) && (ch <= '9')) {
        return (ch - '0');
    } else if (('A' <= ch) && (ch <= 'F')) {
        return (ch - 'A' + 10);
    } else {
        return 0xff;
    }
}

/* ************************************************************************ */
uchar hex_to_ascii_nib (uchar nib)
/* ------------------------------------------------------------------------ --
 * Purpose     : Convert a hex nibble in binary (0-f) to ASCII.
 * Remarks     : nib holds nibble to convert (must be in range 0-f).
 * Restrictions:
 * See also    :
 * Example     :
 ****************************************************************************/
{
    if (nib < 10) {
        return nib + '0';
    } else {
        return (nib - 10) + 'a';
    }
}

/* ************************************************************************ */
char conv_to_upper_case (char ch)
/* ------------------------------------------------------------------------ --
 * Purpose     : Convert a char to upper case.
 * Remarks     :
 * Restrictions:
 * See also    :
 * Example     :
 ****************************************************************************/
{
    if (('a' <= ch) && (ch <= 'z')) {
        return (ch - 0x20);
    } else {
        return ch;
    }
}

#endif
