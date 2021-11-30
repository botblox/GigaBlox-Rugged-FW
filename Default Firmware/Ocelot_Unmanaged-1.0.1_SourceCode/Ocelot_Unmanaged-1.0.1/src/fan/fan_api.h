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

#ifndef _FAN_API_H_
#define _FAN_API_H_

//************************************************
// Configuration definition
//************************************************

// Global configuration (configuration that are shared for all switches in the stack)
typedef struct {
    uchar   t_max; // The temperature were fan is running a full speed
    uchar   t_on;  // The temperature were cooling is needed (fan is started)
} fan_conf_t;


// Switch status (local status for a switch in the stack)
typedef struct {
    ushort chip_temp;              // Chip temperature ( in C.)
    uchar  fan_speed_setting_pct; // The fan speed level at which it is set to (in %).
    ulong  fan_speed;             // The speed the fan is currently running (in RPM)
} fan_local_status_t;



//************************************************
// Constants
//************************************************

// Defines chip temperature range (Select to be within a u8 type)
#define FAN_TEMP_MAX 255
#define FAN_TEMP_MIN 0

//************************************************
// Functions
//************************************************
void  fan_spec_init (void);
void  fan_control (void);
void  fan_init (void);

void  fan_get_local_status(fan_local_status_t *status);

uchar read_fan_conf_t_max (void);
uchar read_fan_conf_t_on  (void);
void  write_fan_conf_t_max (uchar t_max);
void  write_fan_conf_t_on  (uchar t_on);

void  load_fan_conf (void);
void  save_fan_conf (void);

#endif // _FAN_API_H_


//***************************************************************************
//  End of file.
//***************************************************************************
