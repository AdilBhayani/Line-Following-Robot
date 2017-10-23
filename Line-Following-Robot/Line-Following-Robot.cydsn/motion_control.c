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
    #ifndef DONT_USE_PID
        // Getting inputs for PID
        track_quadrature();
        InputA = ((double)disp_a / 228);
        InputB = ((double)disp_b / 228);
        
        // Computing PID calculations
        ComputeA();
        ComputeB();
    #else
        track_quadrature();
        OutputA = SetpointA;
        OutputB = SetpointB;
    #endif
    if (startCounter > 0){
        ramp_loader();
    }else{
    //Outputting PID results to Motor
        if (OutputA == 0) PWM_2_WriteCompare(131);
        else PWM_2_WriteCompare(11.43 * (InputA + OutputA) + 131.13);
        if (OutputB == 0) PWM_1_WriteCompare(131);
        else PWM_1_WriteCompare(11.34 * (InputB + OutputB) + 128.9);
    }
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
    
    quad_a_old = 0;
    quad_b_old = 0;
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    QuadDec_M1_SetInterruptMask(QuadDec_M1_COUNTER_OVERFLOW);
    QuadDec_M2_SetInterruptMask(QuadDec_M2_COUNTER_OVERFLOW);
    isr_quadA_StartEx(QuadISR_1);
    isr_quadB_StartEx(QuadISR_2);
    
    printValue = 0;
    
    init_pid();
    Timer_1_Start();
    isr_Timer1_StartEx(PID_ISR);
}

/*
 * This function ramp loads the PWM of
 * the motors to max value at a constant speed.
 */
void ramp_loader(){
        if (startCounter == 12){
            PWM_2_WriteCompare(175);
            PWM_1_WriteCompare(175);
        }else if (startCounter == 11){
            PWM_2_WriteCompare(185);
            PWM_1_WriteCompare(185);
        }else if (startCounter == 10){
            PWM_2_WriteCompare(195);
            PWM_1_WriteCompare(195);
        }else if (startCounter == 9){
            PWM_2_WriteCompare(205);
            PWM_1_WriteCompare(205);
        }else if (startCounter == 8){
            PWM_2_WriteCompare(210);
            PWM_1_WriteCompare(210);
        }else if (startCounter == 7){
            PWM_2_WriteCompare(215);
            PWM_1_WriteCompare(215);
        }else if (startCounter == 6){
            PWM_2_WriteCompare(220);
            PWM_1_WriteCompare(220);
        }else if (startCounter == 5){
            PWM_2_WriteCompare(225);
            PWM_1_WriteCompare(225);
        }else if (startCounter == 4){
            PWM_2_WriteCompare(230);
            PWM_1_WriteCompare(230);
        }else if (startCounter == 3){
            PWM_2_WriteCompare(235);
            PWM_1_WriteCompare(235);
        }else if (startCounter == 2){
            PWM_2_WriteCompare(245);
            PWM_1_WriteCompare(245);
        }else if (startCounter == 1){
            PWM_2_WriteCompare(255);
            PWM_1_WriteCompare(255);
        }
        startCounter--;
}

void m_stop(){
    SetpointA = STOP_MOTOR;
    SetpointB = STOP_MOTOR;
}

void m_straight(){
    SetpointA = M_FORWARD;
    SetpointB = M_FORWARD;
}

void m_straight_slow(){
    SetpointA = M_FORWARD_SLOW;
    SetpointB = M_FORWARD_SLOW;
}

void m_straight_fast(){
    SetpointA = M_FORWARD_MAX;
    SetpointB = M_FORWARD_MAX;
}

void m_reverse(){  
    SetpointA = M_BACKWARD;
    SetpointB = M_BACKWARD;
}

void m_adjust_left_major(){
    SetpointA = M_FORWARD;
    SetpointB = STOP_MOTOR;
}

void m_adjust_right_major(){
    SetpointA = STOP_MOTOR;
    SetpointB = M_FORWARD;
}

void m_adjust_left_minor(){
    SetpointA = M_FORWARD;
    SetpointB = M_FORWARD_SLOW;
}

void m_adjust_right_minor(){
    SetpointA = M_FORWARD_SLOW;
    SetpointB = M_FORWARD;
}

void m_turn_left(){
    SetpointA = M_FORWARD_SLOW;
    SetpointB = M_BACKWARD_SLOW;
}

void m_turn_right(){
    SetpointA = M_BACKWARD_SLOW;
    SetpointB = M_FORWARD_SLOW;
}

void m_u_turner(){
    SetpointA = M_BACKWARD_MEDIUM;
    SetpointB = M_FORWARD_MEDIUM;
}

void m_right_turner(){
    SetpointA = STOP_MOTOR;
    SetpointB = M_FORWARD_MEDIUM;
}

void m_left_turner(){
    SetpointA = M_FORWARD_MEDIUM;
    SetpointB = STOP_MOTOR;
}

void m_sleep(){
    m_stop();
    CONTROL_Write(0x03);
}

/* 
 * Keeps track of quadrature values.
 */
void track_quadrature(){
    float count_a = (QuadDec_M1_GetCounter() * 1.0);
    float count_b = (QuadDec_M2_GetCounter() * 1.0);
    disp_a = count_a - quad_a_old;
    quad_a_old = count_a;
    disp_b = count_b - quad_b_old;
    quad_b_old = count_b;
    printValue = 1;
}

/*
 * Calculates current speed of the robot over the last 30ms
 * and returns the value as a float in cm/s
 */
void calc_speed(){ 
    if (printValue == 1){
        robot_speed = disp_a * 8.81850569;
        printValue = 0;
    }
}

/*
 * Sets the current straight line speed of the robot in cm/s
 */
void set_speed_A(float speed){
    SetpointA = (double)(speed / 6.912442);
}

void set_speed_B(float speed){
    SetpointB = (double)(speed / 6.912442);
}

/*
 * Robot autonomously follows the line it is currently on until
 * the next intersection. Accepts a direction to turn to immediately
 * as a arguement. The robot will take a turn in this direction at the
 * current intersection and then continue straight to the next
 * intersection, where the robot stops moving and the function returns
 * the type of intersection that it currently faces.
 * 
 * @params Direction to take at current intersection
 * @returns Type of intersection that the robot is currently at
 */
enum intersectionType robot_follow_line(enum robotTurns turnDirection){
    uint8 left_sensor = 0;
    uint8 right_sensor = 0;
    uint8 center_left = 0;
    uint8 center_right = 0;
    uint8 extreme_right = 0;
    uint8 extreme_left = 0;

    if (turnDirection == LEFT) {
        pacman_left_turn();
        m_straight();
    } else if (turnDirection == RIGHT) {
        pacman_right_turn();
        m_straight();
    } else if (turnDirection == STRAIGHT) {
        m_straight();
        CyDelay(100);
    } else if (turnDirection == U_TURN) {
        pacman_u_turn();
        m_straight();
    }

    while(1) {
        CyDelayUs(100);
        center_left = Sensor_1_Read();
        center_right = Sensor_2_Read();
        left_sensor = Sensor_3_Read();
        right_sensor = Sensor_5_Read();
        extreme_right = Sensor_4_Read();
        extreme_left = Sensor_6_Read();
        if ((center_left > 0) || (center_right > 0)) {
            if (extreme_left > 0) {
                if (extreme_right > 0) {
                    m_stop();
                    return CROSSROADS;
                } else {
                    m_stop();
                    return LEFT_FORK;
                }
            } else if (extreme_right > 0) {
                m_stop();
                return RIGHT_FORK;
            }
        }
        if (center_left > 0) {
            if (center_right > 0) {
                m_straight();
            } else {
                m_adjust_left_minor();
            }
        } else if (center_right > 0) {
            m_adjust_right_minor();
        } else if (left_sensor > 0) {
            m_adjust_left_major();
        } else if (right_sensor > 0) {
            m_adjust_right_major();
        }
    }
}

/*
 * Robot moves forward value number of grid spaces.
 */
void robot_forward(int value, enum robotOrientation direction){  
    uint16 distance;
    if (direction == EAST || direction == WEST) distance = ((GRIDSIZE * value) - 90) * 1.13397;
    else distance = ((GRIDSIZEOTHER * value) - 90) * 1.13397;
    int16 originalCount = QuadDec_M1_GetCounter();
    m_straight();
    while (QuadDec_M1_GetCounter() < (originalCount + distance)){
        isr_center_left = Sensor_1_Read();
        isr_center_right = Sensor_2_Read();
        isr_left_sensor = Sensor_3_Read();
        isr_right_sensor = Sensor_5_Read();
        if (isr_center_left > 0){
            if (isr_center_right > 0){
                m_straight();
            } else {
                m_adjust_left_minor();
            }
        } else if (isr_center_right > 0){
            m_adjust_right_minor();
        } else if (isr_left_sensor > 0){
            m_adjust_left_major();
        } else if (isr_right_sensor > 0){
            m_adjust_right_major();
        }
    }
    CyDelay(400);
    m_stop();
}

/*
 * Robot makes a 90° turn right.
 */
void robot_right_turn(){ 
    double distance = 104 * 1.13397;
    double dist = 38 * 1.13397;
    int16 originalCount = QuadDec_M1_GetCounter();
    m_turn_right();
    isr_flag = 0;
    while (QuadDec_M1_GetCounter() < (originalCount + dist));
    while ((QuadDec_M1_GetCounter() < (originalCount + distance)) || (isr_center_right > 0)) {
        isr_center_right = Sensor_4_Read();
    }
    m_stop();
}

/*
 * Robot makes a 90° turn left.
 */
void robot_left_turn(){
    double distance = 104 * 1.13397;
    double dist = 38 * 1.13397;
    int16 originalCount = QuadDec_M2_GetCounter();
    m_turn_left();
    isr_flag = 0;
    while (QuadDec_M2_GetCounter() < (originalCount + dist));
    while ((QuadDec_M2_GetCounter() < (originalCount + distance)) || (isr_center_left > 0)) {
        isr_center_left = Sensor_3_Read();
    }
    m_stop();
}

/*
 * Robot makes a 180° turn.
 */
void robot_turn(){
    double distance = 192 * 1.13397;
    int16 originalCount = QuadDec_M1_GetCounter();
    m_turn_right();
    while (QuadDec_M1_GetCounter() > (originalCount + distance));
    m_stop();    
    
}

void pacman_right_turn(){
    CyDelay(50);
    uint8 center_left = 0;
    uint8 center_right = 0;
    m_right_turner();
    CyDelay(500);
    m_stop();
    CyDelay(50);
    m_right_turner();
    uint8 flag_right = 0;
    center_left = Sensor_1_Read();
    center_right = Sensor_2_Read();
    while(center_right == 0 || center_left == 0){
        center_left = Sensor_1_Read();
        center_right = Sensor_2_Read() || flag_right;
        if (center_right > 0){
            flag_right = 1;   
        }
    }
    CyDelay(10);
    m_stop();
    CyDelay(200);
    if (Sensor_4_Read() > 0 || Sensor_6_Read() > 0){
        m_reverse();
        CyDelay(150);
        m_stop();
    }
}

void pacman_left_turn(){
    CyDelay(50);
    uint8 center_left = 0;
    uint8 center_right = 0;
    m_left_turner();
    CyDelay(500);
    m_stop();
    CyDelay(50);
    m_left_turner();
    uint8 flag_left = 0;
    center_left = Sensor_1_Read();
    center_right = Sensor_2_Read();
    while(center_left == 0 || center_right == 0){
        center_left = Sensor_1_Read() || flag_left;
        center_right = Sensor_2_Read();
        if (center_left > 0){
            flag_left = 1;   
        }
    }
    CyDelay(10);
    m_stop();
    CyDelay(200);
    if (Sensor_4_Read() > 0 || Sensor_6_Read() > 0){
        m_reverse();
        CyDelay(150);
        m_stop();
    }
}

void pacman_u_turn(){
    CyDelay(50);
    uint8 center_right = 0;
    m_u_turner();
    CyDelay(1000);
    m_stop();
    CyDelay(50);
    m_u_turner();
    center_right = Sensor_2_Read();
    while(center_right == 0){
        center_right = Sensor_2_Read();
    }
    CyDelay(10);
    m_stop();
    CyDelay(200);
    m_right_turner();
    while (Sensor_4_Read() > 0);
    CyDelay(15);
    m_stop();
}

/*
 * Initializes two PID systems, one for
 * each motor of the robot.
 */
void init_pid(){      
    InputA = 0;
    InputB = 0;
    ITermA = 0;
    ITermB = 0;
    lastErrorA = 0;
    lastErrorB = 0;
    
    kpa = 0.95;
    kpb = 0.95;
    ki = 0.000025 * SampleTimeInSec;
    kd = 2 / SampleTimeInSec;
}

void ComputeA(){
    
    // Compute all the working errors
    double error = SetpointA - InputA;
    ITermA += (ki * error);
    if (ITermA > M_FORWARD_MAX) ITermA = M_FORWARD_MAX;
    else if (ITermA < M_BACKWARD_MAX) ITermA = M_BACKWARD_MAX;
    double dInput = (error - lastErrorA);

    // Compute the PID Output
    OutputA = kpa * error + ITermA - kd * dInput;
    if (OutputA > M_FORWARD_MAX) OutputA = M_FORWARD_MAX;
    else if (OutputA < M_BACKWARD_MAX) OutputA = M_BACKWARD_MAX;

    // Store for next time
    lastErrorA = error;
}

void ComputeB(){
    // Compute all the working errors
    double error = SetpointB - InputB;
    ITermB += (ki * error);
    if (ITermB > M_FORWARD_MAX) ITermB = M_FORWARD_MAX;
    else if (ITermB < M_BACKWARD_MAX) ITermB = M_BACKWARD_MAX;
    double dInput = (error - lastErrorB);

    // Compute the PID Output
    OutputB = kpb * error + ITermB - kd * dInput;
    if (OutputB > M_FORWARD_MAX) OutputB = M_FORWARD_MAX;
    else if (OutputB < M_BACKWARD_MAX) OutputB = M_BACKWARD_MAX;

    // Store for next time
    lastErrorB = error;
}

void robot_random_1(){
    while (1){
        uint8 intersection = check_if_intersection();
        if (check_u_turn() == 1){
            m_stop();
            pacman_u_turn();
        }else if (intersection > 0){
            m_stop();
            CyDelay(300);
            uint8 random_number = rand()%4;
            uint8 going_forward = 0;
            if (random_number >= 2){
                if (check_execute_forward_path() == 1){
                    going_forward = 1;
                }
            }
            if (intersection == 3 && going_forward == 0){
                if (random_number == 0){
                    pacman_left_turn();
                }else{
                    pacman_right_turn();
                }
            }else if (intersection == 2 && going_forward == 0){
                pacman_left_turn();
            }else if (going_forward == 0){
                pacman_right_turn();
            }
        }else{
            CyDelay(200);
            while(Sensor_4_Read() == 0 && Sensor_6_Read() == 0){
                if (check_u_turn()){
                    m_stop();
                    pacman_u_turn();
                    break;
                }
                isr_center_left = Sensor_1_Read();
                isr_center_right = Sensor_2_Read();
                isr_left_sensor = Sensor_3_Read();
                isr_right_sensor = Sensor_5_Read();
                if (isr_center_left > 0){
                    if (isr_center_right > 0){
                        m_straight();
                    } else {
                        m_adjust_left_minor();
                    }
                } else if (isr_center_right > 0){
                    m_adjust_right_minor();
                }else{
                    m_straight();
                }
            }
        }
    }
    
}

uint8 check_execute_forward_path(){
    m_stop();
    m_straight();
    CyDelay(125);
    m_stop();
    CyDelay(50);
    if (Sensor_1_Read() > 0 || Sensor_2_Read() > 0){
        return 1;
    }else{
        m_reverse();
        CyDelay(175);
        m_stop();
    }
    return 0;
}

uint8 check_u_turn(){
    if (Sensor_1_Read() == 0 && Sensor_2_Read() == 0 && Sensor_3_Read() == 0 && Sensor_4_Read() == 0 && Sensor_5_Read() == 0 && Sensor_6_Read() == 0){
        return 1;
    }
    return 0;
}

uint8 check_if_intersection(){
    if (Sensor_4_Read() > 0){
        if (Sensor_6_Read() > 0 ){
            return 3;
        }else{
            return 1;
        }
    }else{
        if (Sensor_6_Read() > 0){
           return 2; 
        }else{
            return 0;
        }
    }
}

void forward_deadend(){
    CyDelay(100);
    while (check_u_turn() == 0){
        isr_center_left = Sensor_1_Read();
        isr_center_right = Sensor_2_Read();
        isr_left_sensor = Sensor_3_Read();
        isr_right_sensor = Sensor_5_Read();
        if (isr_center_left > 0){
            if (isr_center_right > 0){
                m_straight();
            } else {
                m_adjust_left_minor();
            }
        } else if (isr_center_right > 0){
            m_adjust_right_minor();
        }else{
            m_straight();
        }
    }
    m_stop();
}

/* [] END OF FILE */