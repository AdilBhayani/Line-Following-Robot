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

#include "battery_management.h"
#include "benchmarks.h"
#include "bluetooth.h"
#include "motion_control.h"
#include "rf.h"
#include "usb.h"

void switch_mode(){
    if (Switch_1_Read() > 0) {
        benchmark_2();
    } else if (Switch_2_Read() > 0) {
        benchmark_3();        
    } else if (Switch_3_Read() > 0) {
        benchmark_4();
    } else if (Switch_4_Read() > 0) {        
        benchmark_5();
    } else {
        benchmark_1();
    }
}

void DebugLEDs(){
    if (Sensor_1_Read() > 0) LED_1_Write(1);
    else LED_1_Write(0);
    if (Sensor_2_Read() > 0) LED_2_Write(1);
    else LED_2_Write(0);
    if (Sensor_3_Read() > 0) LED_3_Write(1);
    else LED_3_Write(0);
    if (Sensor_4_Read() > 0) LED_4_Write(1);
    else LED_4_Write(0);
    if (Sensor_5_Read() > 0) LED_5_Write(1);
    else LED_5_Write(0);
    if (Sensor_6_Read() > 0) LED_6_Write(1);
    else LED_6_Write(0);
}

int main()
{
    //init_battery_management();
    init_motion_control();
    CYGlobalIntEnable;
    init_rf();
    switch_mode();
    while(1){
        DebugLEDs();
        CyDelay(100);
    }
}

/* [] END OF FILE */
