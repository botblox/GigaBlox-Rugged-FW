;*
;*
;* Copyright (c) 2017 Microsemi Corporation "Microsemi".
;*
;* Permission is hereby granted, free of charge, to any person obtaining a copy
;* of this software and associated documentation files (the "Software"), to deal
;* in the Software without restriction, including without limitation the rights
;* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;* copies of the Software, and to permit persons to whom the Software is
;* furnished to do so, subject to the following conditions:
;*
;* The above copyright notice and this permission notice shall be included in all
;* copies or substantial portions of the Software.
;*
;* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;* SOFTWARE.
;*
;*
;*

$NOMOD51
$INCLUDE (REG52.INC)

NAME    H2AUX

PUBLIC  _build_phy_write_cmd

H2PROG    SEGMENT CODE

        RSEG    H2PROG


;* ************************************************************************ */
;ulong build_phy_write_cmd (ushort value, uchar reg_no, uchar phy_no) small;
_build_phy_write_cmd:
;* ------------------------------------------------------------------------ --
;* Purpose     : Build 32-bit value to be written to MIIMCMD register for
;*               a write command. written in assembler for performance reasons.
;* Remarks     : value is in r6-r7, reg_no in r5 and phy_no in r3.
;* Restrictions:
;* See also    :
;* Example     :
; * ************************************************************************ */

        ;* mov phy_no to bit 25:21, ie. bit 9:5 of most significant 16 bits
        mov     a, r3   ; get phy no
        mov     b, #020H; shift left 5 times, ie. multiply with 32
        mul     ab      ; now b,a hold 16 most significant bits except for register no.
        ; mov reg_no to bit 20:16, ie. bit 4:0 of most significant 16 bits
        orl     a, r5   ; insert reg no

        ; deliver result in r4-r7 (r6-r7 already contain value)
        mov     r4, b
        mov     r5, a
		
        RET

        END





























