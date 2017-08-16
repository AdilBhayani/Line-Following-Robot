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

#ifndef RF_H_
#define RF_H_

#include <project.h>

#define SOP 0xaa
#define PACKETSIZE 32

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

volatile uint8 counter;
volatile uint8 start;
volatile char buffer[PACKETSIZE];
volatile char packet;

CY_ISR(MyRxISR);
void init_rf();

#endif /* RF_H_ */

/* [] END OF FILE */
