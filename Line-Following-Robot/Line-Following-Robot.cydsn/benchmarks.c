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
 * Line Following ISR - FRONT 4 SENSORS ONLY
 * =======================================*/
CY_ISR(LINE_FOLLOWING){
    isr_center_left = Sensor_1_Read();
    isr_center_right = Sensor_2_Read();
    if (isr_center_left > 0){
        if (isr_center_right > 0){
            set_speed_A(desiredSpeed);
            set_speed_B(desiredSpeed);
        } else {
            set_speed_A(desiredSpeed);
            set_speed_B(desiredSpeed * 0.8);
        }
    } else if (isr_center_right > 0){
        set_speed_A(desiredSpeed * 0.8);
        set_speed_B(desiredSpeed);
    } else {
        m_sleep();
        Timer_0_Stop();
        isr_Timer0_Stop();
    }
}

/* ========================================
 * Open Loop Line Test
 * =======================================*/
void benchmark_1(){
    CyDelay(1000);
    uint8 flag;
    uint8 dist = 105 * 11.3397;
    m_straight_fast();
    
    while(flag == 0) {
        if (QuadDec_M1_GetCounter() > dist) flag = 1;
    }
    m_sleep();
    return;
}

/* ========================================
 * Straight Line Test
 * =======================================*/
void benchmark_2(){
    CyDelay(1000);
    Timer_0_Start();
    isr_Timer0_StartEx(LINE_FOLLOWING);  
    return;
}

/* ========================================
 * Curve Tracking Test
 * =======================================*/
void benchmark_3(){
    CyDelay(1000);
    uint8 left_sensor = 0;
    uint8 right_sensor = 0;
    uint8 center_left = 0;
    uint8 center_right = 0;
    uint8 center_front = 0;
    uint8 direction = 0;
    while(1) {
        CyDelayUs(100);
        left_sensor = Sensor_3_Read();
        right_sensor = Sensor_5_Read();
        center_left = Sensor_1_Read();
        center_right = Sensor_2_Read();
        center_front = Sensor_4_Read();
        if (center_left > 0){
            if (center_right > 0){
                m_straight();
            } else {
                m_adjust_left_minor();
            }
        } else if (center_right > 0){
            m_adjust_right_minor();
        } else if (left_sensor > 0)  {
            m_adjust_left_major();
            direction = 0;
        } else if (right_sensor > 0){
            m_adjust_right_major();
            direction = 1;
        } else if (center_front == 0){
            if (direction > 0){
                m_turn_right();
                while(center_right == 1){
                    center_right = Sensor_2_Read();
                }
                CyDelay(100);
                m_straight();
            } else {
                m_turn_left();
                while(center_left == 1){
                    center_left = Sensor_1_Read();
                }
                CyDelay(100);
                m_straight();
            }
        }
    }
    return;
}

/* ========================================
 * Turn Test
 * =======================================*/
void benchmark_4(){
    benchmark_3();
    return;
}

/* ========================================
 * Speed and Localisation Test
 * =======================================*/
void benchmark_5(){ 
    btPutString("-----------------------------------------------------\n");
    btPutString("------------ Technical Test 2 29/09/2017 ------------\n");
    btPutString("-----------------------------------------------------\n");
    btPutString("The maximum speed this robot is capable of is: 75cm/s\n");
    btPutString("Please enter the desired speed in cm/s: ");
    desiredSpeed = btGetInt();
    btPutString("Please enter the desired distance in cm: ");
    uint16 desiredDistance = btGetInt();
    btPutString("You entered desired speed as ");
    btPutInt(desiredSpeed);
    btPutString("cm/s and desired distance as ");
    btPutInt(desiredDistance);
    btPutString("cm.\nPlease press enter to continue.");
    char cha = BT_UART_GetChar();
    while (cha != 13) cha = BT_UART_GetChar();
    btPutString("Thank you for using the Pacman Self Service Benchmark 5 System.");
    btPutString("\nWe hope you enjoyed your service and look forward to working \nwith you again in the future.\n");
    set_speed_A(desiredSpeed * 1.0);
    set_speed_B(desiredSpeed * 1.0);
    uint8 flag = 0;
    int dist = (desiredDistance - 4) * 11.3397;
    Timer_0_Start();
    isr_Timer0_StartEx(LINE_FOLLOWING);
    startCounter = 12;
    while(flag == 0) {
        if (QuadDec_M1_GetCounter() > dist){
            flag = 1;
        }
    }
    m_sleep();
    Timer_0_Stop();
    isr_Timer0_Stop();
}

/* [] END OF FILE */