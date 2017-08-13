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
    start_adc();
    adc_val = 0;
}

/*
 * Starts freerunning conversion of the ADC.
 */
void start_adc(){
    ADC_SAR_1_StartConvert();
}

/*
 * Stops freerunning conversion of the ADC.
 */
void stop_adc(){
    ADC_SAR_1_StopConvert();
}

/*
 * Calculates the current Voltage level of 
 * the battery and returns it as a float.
 */
float get_v_bat(){
    return (((float)adc_val) * 0.002441406);
}

/*
 * Called by the timer every 60 seconds to
 * check that the battery values are not too
 * low. If they are, the motors, adc & interupts
 * are stopped and processor is left to idle.
 *
 * 2250 / 4096 => 2.74V on ADC terminal
 *      => 5.49V on battery pack
 *      => 0.915V for each battery
 */
void check_battery_status(){
    if (adc_val > 2250) {
        return;
    } else {
        m_stop();
        m_sleep();
        stop_adc();
        CYGlobalIntDisable
        flag = 0;
        while(1);
    }
}

/* [] END OF FILE */
