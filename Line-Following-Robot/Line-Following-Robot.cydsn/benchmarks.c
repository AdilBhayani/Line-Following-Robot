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

#include "benchmarks.h"

/* ========================================
 * Open Loop Line Test
 * =======================================*/
void benchmark_1(){
    CyDelay(1000);
    QuadDec_M1_SetCounter(31293);
    m_straight_fast();
    return;
}

/* ========================================
 * Straight Line Test
 * =======================================*/
void benchmark_2(){
    CyDelay(1000);
    uint8 left_sensor = 0;
    uint8 right_sensor = 0;
    uint8 left_count = 0;
    uint8 right_count = 0;
    while(1) {
        CyDelayUs(100);
        left_sensor = Sensor_5_Read();
        right_sensor = Sensor_4_Read();
        if (left_sensor > 0){
            if (right_sensor > 0){
                m_stop();
                m_sleep();                
            } else {
                left_count = 0;
                right_count++;
                if (right_count >= DAMPING_FACTOR) m_adjust_right_minor();
            }
        } else {
            if (right_sensor > 0){
                right_count = 0;
                left_count++;
                if (left_count >= DAMPING_FACTOR) m_adjust_left_minor();
            } else {
                m_straight_fast();
                left_count = 0;
                right_count = 0;
            }
        }
    }
    return;
}

/* ========================================
 * Curve Tracking Test
 * =======================================*/
void benchmark_3(){
    benchmark_2();
    return;
}

/* ========================================
 * Turn Test
 * =======================================*/
void benchmark_4(){
    benchmark_2();
    return;
}

/* ========================================
 * Speed and Localisation Test
 * =======================================*/
void benchmark_5(){
    return;
}

/* [] END OF FILE */