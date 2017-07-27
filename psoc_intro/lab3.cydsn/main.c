
/* ========================================
 * Laboratory Exercise 3
 *
 * Program timer to flash LED at 1Hz, use interrupts
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <project.h>

volatile uint8 Flag;

CY_ISR(MyISR) {
    if (Flag == 0) 
        Flag = 1;
    else 
        Flag = 0;
    
    LED_Write(Flag);
}
   

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    LED_Write(0);
    Flag = 0;
    isr_TC_StartEx(MyISR);
    Timer_1_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        /* Place your application code here. */
        
        
    }
}

/* [] END OF FILE */
