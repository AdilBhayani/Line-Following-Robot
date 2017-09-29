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

/*
 * One Second timer interupt routine. Every 60
 * seconds this checks the battery levels are
 * not too low, if they are the motors, adc
 * & interupts are stopped and processor is
 * left to idle.
 *
 * 2700 / 4096 => 3.30V on ADC terminal
 *      => 6.60V on battery pack
 *      => 1.10V for each battery
 */
CY_ISR(TimerOneSecISR) {  
    isr_count++;

    DebugLEDs();

    if (isr_count > 9){
        if (adc_val < 2700){
            m_sleep();
            ADC_SAR_1_StopConvert();
            CYGlobalIntDisable    
            while(1);
            LED_6_Write(1);
        }
    }
}

/*
 * ADC End of Conversion Interupt service routine.
 * Takes adc value and stores it in a variable.
 */
CY_ISR(adc_isr){
    adc_val = ADC_SAR_1_GetResult16();
}

/*
 * Initializes the battery management system.
 * Turns on the SAR ADC 1 and starts the end
 * of conversion interrupt.
 */
void init_battery_management(){
    isr_eoc_StartEx(adc_isr);
    ADC_SAR_1_IRQ_Enable();
    ADC_SAR_1_Start();
    ADC_SAR_1_SetPower(3);
    ADC_SAR_1_StartConvert();
    adc_val = 0;
    Timer_0_Start();
    isr_Timer0_StartEx(TimerOneSecISR);
}

/*
 * Calculates the current Voltage level of 
 * the battery and returns it as a float.
 */
float get_v_bat(){
    return (((float)adc_val) * 0.002441406);
}

/* [] END OF FILE */
