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

#ifndef __LEDTSK_H__
#define __LEDTSK_H__

#include "common.h"     /* Always include common.h at the first place of user-defined herder files */
#include "h2gpios.h"

#define LED_MODE_DEFAULT_TIME   30

typedef enum {
    VTSS_LED_MODE_NORMAL,               /* Normal mode (control by led tower mode) */
    VTSS_LED_MODE_OFF,                  /* OFF mode */
    VTSS_LED_MODE_ON_GREEN,             /* ON (green) mode */
    VTSS_LED_MODE_BLINK_GREEN,          /* BLINK (green) mode */
    VTSS_LED_MODE_LINK_ACTIVITY_GREEN,  /* Link activity (green) mode */
    VTSS_LED_MODE_ON_YELLOW,            /* ON (yellow) mode */
    VTSS_LED_MODE_BLINK_YELLOW,         /* BLINK (yellow) mode */
    VTSS_LED_MODE_LINK_ACTIVITY_YELLOW, /* Link activity (yellow) mode */
    VTSS_LED_MODE_ON_RED,               /* ON (red) mode */
    VTSS_LED_MODE_BLINK_RED,            /* BLINK (red) mode */
    VTSS_LED_MODE_TYPE_END
} vtss_led_mode_type_t;

typedef enum {
    VTSS_LED_EVENT_LED,             /* LED itself */
    VTSS_LED_EVENT_PORT_LOOP,       /* Port loop */
    VTSS_LED_EVENT_PHY_OVERHEAT,    /* PHY over heat */
    VTSS_LED_EVENT_VERIPHY_ERR,     /* Alias: Cable diagnostic */

    /* Add new events before here */
    VTSS_LED_EVENT_END
} vtss_led_event_type_t;

#if FRONT_LED_PRESENT
extern uchar led_mode_timer;
#endif

void led_init(void);
void led_tsk(void);
void led_update_system(vtss_led_mode_type_t mode);
void led_1s_timer(void);
void led_refresh(void);

#if (TRANSIT_VERIPHY || TRANSIT_LOOPDETECT)
/* The API is used to upper layer application */
void led_port_event_set(vtss_iport_no_t iport, vtss_led_event_type_t event, vtss_led_mode_type_t mode);
#endif // TRANSIT_VERIPHY || TRANSIT_LOOPDETECT

#endif /* __LEDTSK_H__ */
