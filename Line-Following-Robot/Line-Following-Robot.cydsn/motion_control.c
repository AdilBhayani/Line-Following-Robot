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

/*
 * Quadrature sensor overflow interrupt.
 * Stops motors and puts them to sleep.
 */
CY_ISR(QuadISR_1) {
    LED_Write(1);
    m_stop();
    flag = 0;
    m1_flag = 1;
}

CY_ISR(QuadISR_2) {
    LED_Write(1);
    m_stop();
    flag = 0;
    m2_flag = 1;
}

/*
 * Initializes the motors and quadrature
 * decoders for operation. Sets and enables
 * the overflow interupt on the quadrature
 * decoder. Starts the motor and leaves them
 * in standby.
 *
 * M1 is the RIGHT MOTOR
 * M2 is the  LEFT MOTOR
 */
void init_motion_control() {
    PWM_1_Start();
    PWM_2_Start();
    m_stop();
    quad_a_old = 0;
    quad_b_old = 0;
    m1_flag = 0;
    m2_flag = 0;
    quad_isr_1_StartEx(QuadISR_1);
    quad_isr_2_StartEx(QuadISR_2);
    QuadDec_M1_SetInterruptMask(QuadDec_M1_COUNTER_OVERFLOW);
    QuadDec_M2_SetInterruptMask(QuadDec_M2_COUNTER_OVERFLOW);
    QuadDec_M1_Start();
    QuadDec_M2_Start();
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

void m_straight_fast(){
    PWM_1_WriteCompare(M_FORWARD_MAX);
    PWM_2_WriteCompare(M_FORWARD_MAX);
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

void m_sleep(){
    CONTROL_Write(0x03);
}

/* 
 * Called every one second by the timer.
 * Keeps track of quadrature values.
 */
void track_quadrature(){
    uint16 count_a = QuadDec_M1_GetCounter();
    uint16 count_b = QuadDec_M2_GetCounter();
    disp_a = count_a - quad_a_old;
    disp_b = count_b - quad_b_old;
    quad_a_old = count_a;
    quad_b_old = count_b;
}

/*
 * Calculates current speed of the robot over the last second
 * and returns the value as a float in mm/s
 */
float calc_speed(){
    float disp = (disp_a + disp_b) / 456; // 456 == 2 * 4 * 3 * 19
    return disp * 6.2831853 * WHEELRADIUS; // 2 * pi
}

/*
 * Robot moves forward value number of grid spaces.
 */
void robot_forward(uint8 value){ 
    init_motion_control();
    uint16 distance = ((GRIDSIZE*value)/(6.2831853*WHEELRADIUS))*3*4*19;
    CyDelay(1000);
    QuadDec_M1_SetCounter(32767-distance);
    m_straight_fast();
    while (m1_flag != 1) {
    }
    m1_flag = 0;
}

/*
 * Robot moves backward value number of grid spaces.
 */
void robot_backward(uint8 value){
    init_motion_control();
    uint16 distance = ((GRIDSIZE*value)/(6.2831853*WHEELRADIUS))*3*4*19;
    CyDelay(1000);
    QuadDec_M1_SetCounter(-(32767-distance));
    m_reverse();
    while (m1_flag != 1) {
    }
    m1_flag = 0;
}

/*
 * Robot makes a 90° turn right.
 */
void robot_right_turn(){ 
    init_motion_control();
    uint16 distance = (32*1.570796327/(6.2831853*WHEELRADIUS))*3*4*19; 
    CyDelay(1000);
    QuadDec_M1_SetCounter(32767-distance);
    m_turn_left();
    while (m1_flag != 1) {
    }
    m1_flag = 0;
}

/*
 * Robot makes a 90° turn left.
 */
void robot_left_turn(){
    init_motion_control();
    uint16 distance = (45*1.570796327/(6.2831853*WHEELRADIUS))*3*4*19;
    CyDelay(1000);
    QuadDec_M1_SetCounter(-(32767-distance));
    m_turn_right();
    while (m1_flag != 1) {
    }
    m1_flag = 0;
}

/* [] END OF FILE */