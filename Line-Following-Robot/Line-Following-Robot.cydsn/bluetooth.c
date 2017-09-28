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

#include "bluetooth.h"

/*
 * Initializes the Bluetooth UART and sends welcome message.
 */
void init_bluetooth() {
    BT_UART_Start();
    btPutString("CS301 2017 Group 7\n");
}

/*
 * Outputs given string to the Bluetooth UART console.
 */
void btPutString(char *s) {
    BT_UART_PutString(s);
}

/*
 * Outputs given char to the Bluetooth UART console.
 */
void btPutChar(char c) {
    BT_UART_PutChar(c);
}

/*
 * Outputs given integer to the Bluetooth UART console.
 */
void btPutInt(int value) {
    char buffer_text[BUF_SIZE];
    sprintf(buffer_text,"%d",value);
    btPutString(buffer_text);
}

/*
* Gets char from Bluetooth UART.
*/
char btGetChar() {    
    return BT_UART_GetChar();
}

/*
* Gets integer from Bluetooth UART.
*/
uint16 btGetInt() {
    char cha;
    uint16 enn;
    cha = BT_UART_GetChar();
    while ((cha > 57) || (cha < 48)) cha = BT_UART_GetChar();
    enn = cha - 48;
    cha = BT_UART_GetChar();
    while ((cha > 57) || ((cha < 48) && (cha > 13)) || (cha < 13)) cha = BT_UART_GetChar();
    // Single digit number returns here
    if (cha == 13) return enn;
    
    enn = (enn * 10) + (cha - 48);
    cha = BT_UART_GetChar();
    while ((cha > 57) || ((cha < 48) && (cha > 13)) || (cha < 13)) cha = BT_UART_GetChar();
    // Double digit number returns here
    if (cha == 13) return enn;
    enn = (enn * 10) + (cha - 48);
    cha = BT_UART_GetChar();
    while (cha != 13) cha = BT_UART_GetChar();
    return enn;    

}

/* [] END OF FILE */
