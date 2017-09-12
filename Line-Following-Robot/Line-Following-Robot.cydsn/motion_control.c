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
    m_stop();
}

/*
 * Quadrature sensor overflow interrupt.
 * Stops motors and puts them to sleep.
 */
CY_ISR(QuadISR_2) {
    m_stop();
}

/*
 * PID interrupt. Gets inputs, compute 
 * new PID values, and outputs to PWM.
 */
CY_ISR(PID_ISR){    
    // Getting inputs for PID
    track_quadrature();
    InputA = disp_a;
    InputB = disp_b;
    
    // Computing PID calculations
    ComputeA();
    ComputeB();
    
    // Outputting PID results to Motor
    PWM_1_WriteCompare(11.4 * OutputA + 131.13);
    PWM_2_WriteCompare(11.4 * OutputB + 131.13);
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
    
    Timer_1_Start();
    isr_Timer1_StartEx(PID_ISR);
    
    quad_a_old = 0;
    quad_b_old = 0;
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    isr_quadA_StartEx(QuadISR_1);
    isr_quadB_StartEx(QuadISR_2);
    QuadDec_M1_SetInterruptMask(QuadDec_M1_COUNTER_OVERFLOW);
    QuadDec_M2_SetInterruptMask(QuadDec_M2_COUNTER_OVERFLOW);
}

void m_stop(){
    SetpointA = STOP_MOTOR;
    SetpointB = STOP_MOTOR;
}

void m_straight(){
    SetpointA = M1_FORWARD;
    SetpointB = M2_FORWARD;
}

void m_straight_slow(){
    SetpointA = M1_FORWARD_SLOW;
    SetpointB = M2_FORWARD_SLOW;
}

void m_straight_fast(){
    SetpointA = M_FORWARD_MAX;
    SetpointB = M_FORWARD_MAX;
}

void m_reverse(){  
    SetpointA = M1_BACKWARD;
    SetpointB = M2_BACKWARD;
}

void m_adjust_left_major(){
    SetpointA = M1_FORWARD;
    SetpointB = STOP_MOTOR;
}

void m_adjust_right_major(){
    SetpointA = STOP_MOTOR;
    SetpointB = M2_FORWARD;
}

void m_adjust_left_minor(){
    SetpointA = M1_FORWARD;
    SetpointB = M2_FORWARD_SLOW;
}

void m_adjust_right_minor(){
    SetpointA = M1_FORWARD_SLOW;
    SetpointB = M2_FORWARD;
}

void m_turn_left(){
    SetpointA = M1_FORWARD;
    SetpointB = M2_BACKWARD;
}

void m_turn_right(){
    SetpointA = M1_BACKWARD;
    SetpointB = M2_FORWARD;
}

void m_sleep(){
    m_stop();
    CONTROL_Write(0x03);
}

/* 
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
 * Calculates current speed of the robot over the last 10ms
 * and returns the value as a float in mm/s
 */
float calc_speed(){
    return disp_a * 2.75578 * WHEELRADIUS; // 4 * 3 * 19 * 100 * 2 * pi
}

/*
 * Robot moves forward value number of grid spaces.
 */
void robot_forward(uint8 value){ 
    uint16 distance = ((GRIDSIZE*value)/(6.2831853*WHEELRADIUS))*3*4*19;
    QuadDec_M1_SetCounter(32767-distance);
    m_straight_fast();
    while (SetpointA != 0);
}

/*
 * Robot moves backward value number of grid spaces.
 */
void robot_backward(uint8 value){
    uint16 distance = ((GRIDSIZE*value)/(6.2831853*WHEELRADIUS))*3*4*19;
    QuadDec_M1_SetCounter(-(32767-distance));
    m_reverse();
    while (SetpointA != 0);
}

/*
 * Robot makes a 90° turn right.
 */
void robot_right_turn(){ 
    double distance = (32*1.570796327/(6.2831853*WHEELRADIUS))*3*4*19; 
    QuadDec_M2_SetCounter(32767-distance);
    m_turn_right();
    while (SetpointB != 0);
}

/*
 * Robot makes a 90° turn left.
 */
void robot_left_turn(){
    double distance = (45*1.570796327/(6.2831853*WHEELRADIUS))*3*4*19;
    QuadDec_M1_SetCounter(-(32767-distance));
    m_turn_left();
    while (SetpointA != 0);
}

/*
 * Initializes two PID systems, one for
 * each motor of the robot.
 */
void init_pid(){
    outMin = 11;
    outMax = -11;
    
    SampleTimeInSec = 0.01;
    
    lastInputA = InputA;
    lastInputB = InputB;
    outputSumA = OutputA;
    outputSumB = OutputB;

    if (outputSumA > outMax) outputSumA = outMax;
    else if (outputSumB < outMin) outputSumB = outMin;
    if (outputSumA > outMax) outputSumA = outMax;
    else if (outputSumB < outMin) outputSumB = outMin;

    SetPIDTunings(0.8, 0.2, 0.0);
}

void ComputeA(){
    // Compute all the working errors
    double error = SetpointA - InputA;
    ITermA += (ki * error);
    if (ITermA > outMax) ITermA = outMax;
    else if (ITermA < outMin) ITermA = outMin;
    double dInput = (InputA - lastInputA);

    // Compute the PID Output
    OutputA = kp * error + ITermB - kd * dInput;
    if (OutputA > outMax) OutputA = outMax;
    else if (OutputA < outMin) OutputA = outMin;

    // Store for next time
    lastInputA = InputA;
}

void ComputeB(){
    // Compute all the working errors
    double error = SetpointB - InputB;
    ITermB += (ki * error);
    if (ITermB > outMax) ITermB = outMax;
    else if (ITermB < outMin) ITermB = outMin;
    double dInput = (InputB - lastInputB);

    // Compute the PID Output
    OutputB = kp * error + ITermB - kd * dInput;
    if (OutputB > outMax) OutputB = outMax;
    else if (OutputB < outMin) OutputB = outMin;

    // Store for next time
    lastInputB = InputB;
}
  
void SetPIDTunings(double Kp, double Ki, double Kd){
    kp = Kp;
    ki = Ki * SampleTimeInSec;
    kd = Kd / SampleTimeInSec;
}

/* [] END OF FILE */