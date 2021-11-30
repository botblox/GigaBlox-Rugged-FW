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
#ifndef __MISC2_H__
#define __MISC2_H__

ushort bytes2ushort (uchar lsb, uchar msb) small;
ulong  ushorts2ulong (ushort lsw, ushort msw) small;
ushort high_w (ulong ul) small;
ulong  bit_mask_32 (uchar bit_no) small;
ushort bit_mask_16 (uchar bit_no) small;
uchar  bit_mask_8 (uchar bit_no) small;

void write_bit_8 (uchar bit_no, uchar value, uchar *dst_ptr) small;
void write_bit_16 (uchar bit_no, uchar value, ushort *dst_ptr) small;
void write_bit_32 (uchar bit_no, uchar value, ulong *dst_ptr) small;

bit test_bit_8 (uchar bit_no, uchar *src_ptr) small;
bit test_bit_16 (uchar bit_no, ushort *src_ptr) small;
bit test_bit_32 (uchar bit_no, ulong *src_ptr) small;

#endif
