/* ========================================
 *
 * Copyright (c) 2017, Alex Andela, Adil Bhayani, Vaishnavi Muppavaram, சகாயன் சிற்சபேசன்
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

extern int16 speedL, speedR;
extern int16 posL, posR;


void get_position(void);
void get_speed(void);

//------------------------------------------------------
void get_position()
{
    int pl, pr;

    pl = QuadDec_M1_GetCounter();
    pr = QuadDec_M2_GetCounter();

    posL = pl;
    posR = pr;
}
//------------------------------------------------------
void get_speed()
{
    int16 pl, pr;
    
    // get current position.
    pl = QuadDec_M1_GetCounter();
    pr = QuadDec_M2_GetCounter();
    
    speedL = pl - posL;
    speedR = pr - posR;
    posL = pl;
    posR = pr;
    
    
//    // Speed of Motor 1
//    state = QuadDec_M1_GetEvents();
//    speed = pl - posL;
//    if ((state & QuadDec_M1_COUNTER_OVERFLOW) != 0x00)
//        speed += 32767;
//    
//    if ((state & QuadDec_M1_COUNTER_UNDERFLOW) != 0x00)
//        speed += -32768;
//    speedL = speed;
//    posL = pl;
//    
//    // Speed of Motor 2
//    state = QuadDec_M2_GetEvents();
//    speed = pr - posR;
//    if ((state & QuadDec_M2_COUNTER_OVERFLOW) != 0x00)
//        speed += 32767;
//    
//    if ((state & QuadDec_M2_COUNTER_UNDERFLOW) != 0x00)
//        speed += -32768;
//    speedR = speed;    
//    posR = pr;
}
//------------------------------------------------------
/* [] END OF FILE */
