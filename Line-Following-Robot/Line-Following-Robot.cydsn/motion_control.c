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

#include "motion_control.h"

void init_motion_control() {
    PWM_1_Start();
    PWM_2_Start();
}

void m_stop(){
    PWM_1_WriteCompare(STOP_MOTOR);
    PWM_2_WriteCompare(STOP_MOTOR);
}

void m_straight(){
    PWM_1_WriteCompare(M1_FORWARD);
    PWM_2_WriteCompare(M2_FORWARD);
}

void m_straight_slow(){
    PWM_1_WriteCompare(M1_FORWARD_SLOW);
    PWM_2_WriteCompare(M2_FORWARD_SLOW);
}

void m_reverse(){
    PWM_1_WriteCompare(M1_BACKWARD);
    PWM_2_WriteCompare(M2_BACKWARD);
}

void m_adjust_left_major(){
    PWM_1_WriteCompare(M1_FORWARD);
    PWM_2_WriteCompare(STOP_MOTOR);
}

void m_adjust_right_major(){
    PWM_1_WriteCompare(STOP_MOTOR);
    PWM_2_WriteCompare(M2_FORWARD);
}

void m_adjust_left_minor(){
    PWM_1_WriteCompare(M1_FORWARD);
    PWM_2_WriteCompare(M2_FORWARD_SLOW);
}

void m_adjust_right_minor(){
    PWM_1_WriteCompare(M1_FORWARD_SLOW);
    PWM_2_WriteCompare(M2_FORWARD);
}

void m_turn_left(){
    PWM_1_WriteCompare(M1_FORWARD);
    PWM_2_WriteCompare(M2_BACKWARD);
}

void m_turn_right(){
    PWM_1_WriteCompare(M1_BACKWARD);
    PWM_2_WriteCompare(M2_FORWARD);
}

/* [] END OF FILE */
