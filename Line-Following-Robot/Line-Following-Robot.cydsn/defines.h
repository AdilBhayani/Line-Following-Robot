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

// Code setup
#define USE_USB

//* ========================================
#define FALSE 0
#define TRUE 1
#define UNKNOWN 10
//* ========================================
#define TS 100 // sample time = 100kHz * TS
#define DECIMATE_TS_ENC     1000    // decimation factor for quad decoder
#define DECIMATE_TS_UPDATE  2000    // decimation factor for update action
#define DECIMATE_TS_SPEED   100
#define DECIMATE_TS_DISPLAY 1000
//* ========================================
// General Debug
#define LED_ON          LED_Write(1)
#define LED_OFF         LED_Write(0)
#define LED_TOGGLE      LED_Write(~LED_Read())

#define DB0_ON          DB0_Write(1)
#define DB0_OFF         DB0_Write(0)
#define DB0_TOGGLE_LED  DB0_Write(~DB0_Read())

#define DB1_ON          DB1_Write(1)
#define DB1_OFF         DB1_Write(0)
#define DB1_TOGGLE_LED  DB1_Write(~DB1_Read())

#define DB2_ON          DB2_Write(1)
#define DB2_OFF         DB2_Write(0)
#define DB2_TOGGLE_LED  DB2_Write(~DB2_Read())
//* ========================================
// Motor
#define COAST_OFF CONTROL_Write(0);
#define COAST_ON CONTROL_Write(0b11);

#define PWM_MAX 255     // maximum value of duty cycle
#define PWM_MIN 0       // minimum value of duty cycle
//* ========================================
// USBUART
#define BUF_SIZE 64 // USBUART fixed buffer size
#define CHAR_NULL '0'
#define CHAR_BACKSP 0x08
#define CHAR_DEL 0x7F
#define CHAR_ENTER 0x0D
#define LOW_DIGIT '0'
#define HIGH_DIGIT '9'
//* ========================================
//RF 
#define SOP 0xaa
#define PACKETSIZE 32    
#define RXSTRINGSIZE 64 // 4+3+[4+4+4]+[4+4+4+4]+[4+4+4+4]+[4+4+4+4]+delimiters, i.e. no more than 64
/* [] END OF FILE */
