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

#ifndef __SWCONF_H__
#define __SWCONF_H__

#ifndef __INCLUDE_CONFIGS__
#error "swconf.h is for common.h only"
#endif

#if defined(PROJ_OPT)
    #if defined(FERRET_F11) || defined(FERRET_F10P) || defined(FERRET_F5) || defined(FERRET_F4P)
        #if (PROJ_OPT == 99998)
            #include "proj_opt_ferret_release.h"
        #elif (PROJ_OPT == 99999)
            #include "proj_opt_ferret_release_lacp.h"
        #else
            #include "proj_opt_ferret_develop.h"
        #endif
    #endif
#endif // PROJ_OPT

/* Default configuration */
#include "swconf_def.h"

#endif /* __SWCONF_H__ */
