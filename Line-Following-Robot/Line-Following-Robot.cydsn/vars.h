/* ========================================
 *
 * Copyright (c) 2017, Alex Andela, Adil Bhayani, Vaishnavi Muppavaram, Sakayan Sitsabesan
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ========================================
*/

#include <project.h>
#include "defines.h"
//* ========================================
uint8 ts = 0;
uint16 ts_enc = 0;
uint16 ts_update = 0;
uint16 ts_speed = 0;
uint16 ts_display = 0;

uint8 flag_ts_enc = 0;
uint8 flag_ts_update = 0;
uint8 flag_ts_speed = 0;
uint8 flag_ts_display = 0;


uint8 flag_rx = 0;
uint8 flag_packet = 0;
uint8 flag_KB_string = 0;

uint8 dataready_flag =0;

uint8 flag_rf_transmission_active = UNKNOWN; // [TRUE if receieving data, FALSE is not, UNKNOWN at startup]

//* ========================================
char displaystring[BUF_SIZE] = "CS301 2016\n";
char line[BUF_SIZE], entry[BUF_SIZE];
uint8 usbBuffer[BUF_SIZE];
//* ========================================
typedef struct data_main {
	int8            rssi;	
    uint8           index;			// index number of packet. incremented number
	int16			robot_xpos;	 	// 
	int16			robot_ypos;		//
    int16         robot_orientation;
	int16			g0_xpos;		//
	int16			g0_ypos;		//
	int16			g0_speed;		//
	int16		g0_direction;	//
	int16			g1_xpos;		//
	int16			g1_ypos;		//
	int16			g1_speed;		//
    int16		g1_direction;	//
    int16			g2_xpos;		//
    int16			g2_ypos;		//
    int16			g2_speed;		//
    int16		g2_direction;	//
} vtype1;    
struct data_main system_state;
//* ========================================


//* ========================================
/* [] END OF FILE */
