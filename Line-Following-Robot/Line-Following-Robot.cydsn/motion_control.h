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

#ifndef MOTION_CONTROL_H_
#define MOTION_CONTROL_H_
    
#define DONT_USE_PID

#include <project.h>
#include "usb.h"
#include "bluetooth.h"

// y = 0.0877x - 11.5
// where y = pulses on quad per 10ms
//   and x = PWM compare value

// Following constants are quad pulses per 10ms
#define STOP_MOTOR 0
#define M_FORWARD_MAX 10.85
#define M_BACKWARD_MAX (-10.85)
#define M_FORWARD 5
#define M_FORWARD_SLOW 3
#define M_BACKWARD (-5)
#define M_BACKWARD_SLOW (-3)
    
// Following defines are in mm
#define WHEELRADIUS 32    
#define GRIDSIZE 30

static volatile int16 quad_a_old;
volatile int16 quad_b_old;
volatile int16 disp_a;
volatile int16 disp_b;

volatile double InputA, OutputA, SetpointA;
volatile double InputB, OutputB, SetpointB;
volatile double ITermA, outputSumA, lastInputA;
volatile double ITermB, outputSumB, lastInputB;
double kp, ki, kd;
double outMin, outMax;
double SampleTimeInSec;

void init_motion_control();
void m_stop();
void m_straight();
void m_straight_slow();
void m_straight_fast();
void m_reverse();
void m_adjust_left_major();
void m_adjust_right_major();
void m_adjust_left_minor();
void m_adjust_right_minor();
void m_turn_left();
void m_turn_right();
void m_sleep();

void track_quadrature();
float calc_speed();

void robot_forward(uint8 value);
void robot_backward(uint8 value);
void robot_right_turn();
void robot_left_turn();

void init_pid();
void ComputeA();
void ComputeB();
void SetPIDTunings(double Kp, double Ki, double Kd);
    
#endif /* MOTION_CONTROL_H_ */

/* [] END OF FILE */
