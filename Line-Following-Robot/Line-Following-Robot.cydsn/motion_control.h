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

#include <project.h>
#include "timer.h"
    
#define STOP_MOTOR 128

#define M_FORWARD_MAX 255
#define M_BACKWARD_MAX 0

#define M1_FORWARD 190
#define M2_FORWARD 190

#define M1_FORWARD_SLOW 170
#define M2_FORWARD_SLOW 170

#define M1_BACKWARD 64
#define M2_BACKWARD 64
    
#define WHEELRADIUS 32

volatile uint16 quad_a_old;
volatile uint16 quad_b_old;
volatile uint16 disp_a;
volatile uint16 disp_b;

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
    
#endif /* MOTION_CONTROL_H_ */

/* [] END OF FILE */
