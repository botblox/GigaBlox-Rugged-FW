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

#ifndef __H2MACTAB_H__
#define __H2MACTAB_H__

#if TRANSIT_UNMANAGED_MAC_OPER_SET
/* Add/Delete MAC address entry
 * Only support unicast and one port setting in port_mask parameter currently.
 */
void h2_mactab_set(const mac_tab_t xdata *mac_tab_entry_ptr, BOOL xdata is_add);
#endif // TRANSIT_UNMANAGED_MAC_OPER_SET

#if TRANSIT_UNMANAGED_MAC_OPER_GET
/* GET/GETNEXT MAC address entry
 * Return 0xFFFFFFFF when entry is invalid. Otherwize, the operation is success.
 */
ulong h2_mactab_get_next(mac_tab_t xdata *mac_tab_entry_ptr, BOOL xdata *ipmc_entry, BOOL xdata is_getnext);
#endif // TRANSIT_UNMANAGED_MAC_OPER_GET

void h2_mactab_agetime_set(void);
void h2_mactab_flush_port(vtss_cport_no_t chip_port);
void h2_mactab_age(uchar pgid_age, uchar pgid, uchar vid_age, ushort vid);
void h2_mactab_clear(void);

#endif // __H2MACTAB_H__
