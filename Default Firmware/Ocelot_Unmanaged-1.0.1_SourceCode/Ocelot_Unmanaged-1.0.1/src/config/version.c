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

#include "version.h"
#include "code_revision.c"


/* 
 * Local Definition
 */
/* Software version suffix string */
#if defined(PROJ_OPT)
    #if (PROJ_OPT == 0)
        #define VER_SUFFIX_TXT      " - Engineer Developed"
    #elif (PROJ_OPT == 99998)
        #define VER_SUFFIX_TXT      " Ocelot-REL_Unmanaged"
    #elif (PROJ_OPT == 99999)
        #define VER_SUFFIX_TXT      " Ocelot-REL_Unmanaged_LACP"
    #endif
#else
    #define VER_SUFFIX_TXT          ""
#endif


/* 
 * Local Variables
 */
const char code *SW_COMPILE_DATE = __DATE__ " " __TIME__;

/* Notice that text 'TEST-N' should be excluded from the software version string */
const char code *SW_VERSION =
#if defined(LUTON26_L25)
    "Luton25 3.08a"
#elif defined(LUTON26_L16)
    "Luton16e 3.08a"
#elif defined(LUTON26_L10)
    "Luton10 3.08a"
#elif defined(FERRET_F11)
    "Ferret_F11" VER_SUFFIX_TXT
#elif defined(FERRET_F10P)
    "Ferret_F10P" VER_SUFFIX_TXT
#elif defined(FERRET_F5)
    "Ferret_F5" VER_SUFFIX_TXT
#elif defined(FERRET_F4P)
    "Ferret_F4P" VER_SUFFIX_TXT
#else
    "Uknown version"
#endif
;
