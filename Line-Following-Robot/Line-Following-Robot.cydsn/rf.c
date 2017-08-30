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

#include "rf.h"
#include "usb.h"
#include "string.h"
#include <stdlib.h>

/* RX interupt on UART. Takes byte and stores in temp variable
 * 'packet'. Checks if this is SOP, if so prepares for receiving
 * the rest of the data. Keeps track of how many bytes have been
 * received and stores them in the array buffer. Once whole packet
 * has been received, then the raw bytes are copied over to the C
 * struct system_state and counters reset.
 */
CY_ISR(MyRxISR) {
    packet = UART_GetByte();
    if (packet == SOP) {
        start++;
    }
    else if (start > 1) {
        buffer[counter] = packet;
        counter++;
        if (counter > 32) {
            counter = 0;
            start = 0;
            //memcpy(&system_state, buffer, PACKETSIZE);
            system_state = *(vtype1 *)buffer;
        }
    }
}

/*
 * Initializes the UART system for sending/receiving data
 * from the server. Sets up a RX interupt to be triggered.
 * Sets start bit counter and current byte counter to 0.
 */
void init_rf(){
    UART_Start();
    isrRF_RX_StartEx(MyRxISR);
    counter = 0;
    start = 0;
}

uint8 asciiMethod() {
    char cha;
    int firstValue[3] = {0, 0, 0};
    cha = UART_GetChar();
    if (cha != 0){
        if (cha == '#'){
            static char streamArray[96];
            int index = 0;
            int flag = 0;
            while(flag == 0){  
                cha = UART_GetChar();
                firstValue[index] = cha - 48;
                if (cha == 10 || cha == 13){
                    break;   
                }
                while (cha != ','){
                    //usbPutChar(cha)
                    index++;
                    cha = UART_GetChar();
                    firstValue[index] = cha - 48;
                    //append to something
                    if (cha == '#'){
                        break;
                    }
                }
                flag = 1;
            }
            if (flag == 1) {
                int i;
                for (i = 0; i < 3; i++) {
                    CyDelay(1000);
                    usbPutInt(firstValue[i]);
                    //usbPutInt(12);
                }
                return 1;
            }
            
        }
    }
    return 1;
}

/* [] END OF FILE */
