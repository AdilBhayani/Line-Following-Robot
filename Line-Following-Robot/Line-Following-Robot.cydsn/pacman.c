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

#include "pacman.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * The static food pellets will be evenly distributed across the
 * field. There are no ghosts or rewards. This is a passive, non
 * aggressive, level and the only challenge is to complete the
 * level within the time-limit. 
 */
void play_pacman_1(){
    CyDelay(1000);
    uint8 left_sensor = 0;
    uint8 right_sensor = 0;
    uint8 center_left = 0;
    uint8 center_right = 0;
    uint8 center_front = 0;
    uint8 direction = 0;
    uint8 prio = 0;
    uint8 kodi = 0;
    while(1) {
        CyDelayUs(100);
        left_sensor = Sensor_3_Read();
        right_sensor = Sensor_5_Read();
        center_left = Sensor_1_Read();
        center_right = Sensor_2_Read();
        center_front = Sensor_4_Read();
        if ((left_sensor > 0) && (right_sensor > 0)) {
            prio = (int)(rand() % 3);
            if (prio == 2) {
                m_straight();
                kodi = 0;
            } else if (prio == 1) {
                m_adjust_right_major();
                direction = 1;
                kodi = 1;
            } else {
                m_adjust_left_major();
                direction = 0;
                kodi = 1;
            }

            if (kodi > 0) {
                CyDelay(100);
                if (direction > 0){
                    m_turn_right();
                    while(center_right == 1){
                        center_right = Sensor_2_Read();
                    }
                    CyDelay(100);
                    m_straight();
                    prio = (int)(rand() % 2);
                } else {
                    m_turn_left();
                    while(center_left == 1){
                        center_left = Sensor_1_Read();
                    }
                    CyDelay(100);
                    m_straight();
                    prio = (int)(rand() % 2);
                }
            }
        }
        if (prio > 0) {
            if (center_right > 0){
                if (center_left > 0){
                    m_straight();
                } else {
                    m_adjust_right_minor();
                }
            } else if (center_left > 0){
                m_adjust_left_minor();
            } else if (right_sensor > 0)  {
                m_adjust_right_major();
                direction = 1;
            } else if (left_sensor > 0){
                m_adjust_left_major();
                direction = 0;
            } else if (center_front == 0){
                if (direction > 0){
                    m_turn_right();
                    while(center_right == 1){
                        center_right = Sensor_2_Read();
                    }
                    CyDelay(100);
                    m_straight();
                    prio = (int)(rand() % 2);
                } else {
                    m_turn_left();
                    while(center_left == 1){
                        center_left = Sensor_1_Read();
                    }
                    CyDelay(100);
                    m_straight();
                    prio = (int)(rand() % 2);
                }
            }
        } else {
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
                    prio = (int)(rand() % 2);
                } else {
                    m_turn_left();
                    while(center_left == 1){
                        center_left = Sensor_1_Read();
                    }
                    CyDelay(100);
                    m_straight();
                    prio = (int)(rand() % 2);
                }
            }
        }
    }
    return;
}


/*
 * In this level, 5 pellets will be placed across the field. The
 * location of the pellets will be given to you as the list. The 
 * challenge is to make the Pacman plan a route from the current
 * position to first unconsumed pellet in the list. The robot’s
 * starting position will be given.
 */
void play_pacman_2(){
    int i = 0;
    //printf("Inside pacman_2()\n");
    btPutString("Inside pacman_2()\n");
    end_coordinate[0][0] = food_list[0][0]; //set x and y coordinates of first item in food list
    end_coordinate[0][1] = food_list[0][1]; 
    a_star();
    print_ret_steps();
    generate_directions();
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item
    set_start_end(1);
    print_ret_steps();
    generate_directions();
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item
    set_start_end(2);
    print_ret_steps();
    generate_directions();
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item
    set_start_end(3);
    print_ret_steps();
    generate_directions();
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item
    set_start_end(4);
    print_ret_steps();
    generate_directions();
    while(1);
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item
}

/*
* This will be discussed in class and the specifics of this test
* will be based on discussions in class.
*/
void play_pacman_3(){

}

void set_start_end(int next_pellet) {
    start_coordinate[0][0] = food_list[next_pellet - 1][0];
    start_coordinate[0][1] = food_list[next_pellet - 1][1];
    end_coordinate[0][0] = food_list[next_pellet][0];
    end_coordinate[0][1] = food_list[next_pellet][1];
    a_star();
}

void print_ret_steps() {
    int i;
    for (i = 0; i < 285; i++){ 
        if (ret_steps[i][0] != -1){
            btPutInt(ret_steps[i][0]);
            btPutString(",");
            btPutInt(ret_steps[i][1]);
            btPutString("\n");
        }
    }
}

void generate_directions() {
    int i = 0;
    while (ret_steps[i][0] != -1) {
        i++;
    }
    int a;
    for (a = 1; a < i - 1; a++) { //don't check first coordinate because we need to go straight anyways
        if (a == i - 2) { //save the second to last coordinate that the robot is in for in between particles
            prevPosition[0][0] = ret_steps[a][0];
            prevPosition[0][1] = ret_steps[a][1];
        }
        enum robotTurns turnToAdd = NO_TURN;
        if (a == 1 && firstPelletFlag == 0) { //robot needs to redirect based on where it previously was
            if (prevPosition[0][0] == ret_steps[a][0] && prevPosition[0][1] == ret_steps[a][1]) { //180 turn
                pacmanDirections[pacmanDirectionsIndex] = RIGHT;
                pacmanDirectionsIndex++;
                pacmanDirections[pacmanDirectionsIndex] = RIGHT;
                pacmanDirectionsIndex++; 
            }
            else {
                turnToAdd = convertCoordinates(ret_steps[a-1][0], ret_steps[a-1][1], ret_steps[a][0], ret_steps[a][1], ret_steps[a+1][0], ret_steps[a+1][1]);
            }
        }
        else {
            turnToAdd = convertCoordinates(ret_steps[a-1][0], ret_steps[a-1][1], ret_steps[a][0], ret_steps[a][1], ret_steps[a+1][0], ret_steps[a+1][1]);
        }
        if (turnToAdd != NO_TURN) {
            pacmanDirections[pacmanDirectionsIndex] = turnToAdd;
            pacmanDirectionsIndex++;
        }
        
        turnToAdd = NO_TURN; //reset the value of turnToAdd
        btPutString("The coordinate being considered is: ");
        btPutInt(ret_steps[a][0]);
        btPutString(", ");
        btPutInt(ret_steps[a][1]);
        btPutString("\n");
        btPutString("The converted direction is: ");
        btPutInt(turnToAdd);
        btPutString("\n");
    }
    int b;
    for(b = 0; b < pacmanDirectionsIndex; b++) {
        btPutString("The robot needs to turn: ");
        btPutInt(pacmanDirections[b]);
        btPutString("\n");
    }
    firstPelletFlag = 0;
}

enum robotTurns convertCoordinates(int prevPosRow, int prevPosCol, int currentPosRow, int currentPosCol, int nextPosRow, int nextPosCol) {
    if (nextPosCol > currentPosCol) { // column has increased
        if (prevPosRow < currentPosRow) { //if row is increasing then robot is going south, and needs to turn left
            return LEFT;
        }
        else if (prevPosRow > currentPosRow) { //if row is decreasing then robot is going north, and needs to turn right
            return RIGHT; 
        }
    }
    else if (nextPosCol < currentPosCol) { // column has decreased
        if (prevPosRow < currentPosRow) { //if row is increasing then robot is going south, and needs to turn right
            return RIGHT;
        }
        else if (prevPosRow > currentPosRow) { //if row is decreasing then robot is going north, and needs to turn left
            return LEFT;
        }
    }
    else if (nextPosRow < currentPosRow) { // row has decreased
        if (prevPosCol < currentPosCol) { //if column is increasing then robot is going east, and needs to turn left
            return LEFT;
        }
        else if (prevPosCol > currentPosCol) { //if column is decreasing then robot is going west, and needs to turn right
            return RIGHT;
        }
    }
    else if (nextPosRow > currentPosRow) { // row has increased
        if (prevPosCol < currentPosCol) { //if column is increasing then robot is going east, and needs to turn right
            return RIGHT;
        }
        else if (prevPosCol > currentPosCol) { //if column is decreasing then robot is going west, and needs to turn left
            return LEFT;
        }
    }
    return NO_TURN; //else add straight
}

void a_star(){
    //printf("Inside a_star()\n");
    //printf("start_coordinate is X: %d, Y: %d\n", start_coordinate[0][0], start_coordinate[0][1]);
    //printf("end_coordinate is X: %d, Y: %d\n", end_coordinate[0][0], end_coordinate[0][1]);
    
    int x, y;
    static int ret_visited[15][19];
    for(x = 0; x < 15; x ++) {
        for(y = 0; y < 19; y ++) ret_visited[x][y] = 1;
    }
    static int open_list[285][2];
    static int closed_list[285][2];
    open_list[0][0] = start_coordinate[0][0];
    open_list[0][1] = start_coordinate[0][1];
    closed_list[0][0] = -1;
    closed_list[0][1] = -1;
    for(x = 1; x < 285; x ++) {
        for(y = 0; y < 2; y ++) {
            open_list[x][y] = -1;
            closed_list[x][y] = -1;
        }
    }
    int open_index = 1;
    int closed_index = 0;
    static int f_values[15][19] = {{0}};
    static int g_values[15][19] = {{0}};
    static int h_values[15][19] = {{0}};
    static int parents_x[15][19] = {{0}};
    static int parents_y[15][19] = {{0}};
    h_values[start_coordinate[0][0]][start_coordinate[0][1]] = abs(end_coordinate[0][0] - start_coordinate[0][0]) * 10 + abs(end_coordinate[0][1] - start_coordinate[0][1]) * 10;
    f_values[start_coordinate[0][0]][start_coordinate[0][1]] = abs(end_coordinate[0][0] - start_coordinate[0][0]) * 10 + abs(end_coordinate[0][1] - start_coordinate[0][1]) * 10;

    while (open_index > 0){
        int lowest_f_index;
        lowest_f_index = find_lowest_f_square(f_values, open_list, open_index);
        //printf("lowest_f_index: %d\n", lowest_f_index);
        closed_list[closed_index][0] = open_list[lowest_f_index][0];
        closed_list[closed_index][1] = open_list[lowest_f_index][1];
        closed_index++;
        int square_to_check_x = closed_list[closed_index-1][0];
        int square_to_check_y = closed_list[closed_index-1][1];
        ret_visited[open_list[lowest_f_index][0]][open_list[lowest_f_index][1]] = 0;
        open_list[lowest_f_index][0] = -1;
        open_list[lowest_f_index][1] = -1;
        //printf("square_to_check_x: %d\n", square_to_check_x);
        //printf("square_to_check_y: %d\n", square_to_check_y);
        
        int closed_list_index = in_list(square_to_check_x - 1, square_to_check_y, closed_list, closed_index);
        //printf("closed_list_index top: %d\n", closed_list_index);
        if (closed_list_index == -1 && square_to_check_x > 0 && currentMap[square_to_check_x - 1][square_to_check_y] == 0){
            int open_list_index = in_list(square_to_check_x - 1, square_to_check_y, open_list, open_index);
            //printf("open_list_index top: %d\n", open_list_index);
            if (open_list_index == -1){
                //Add square
                add_square(square_to_check_x, square_to_check_y, square_to_check_x - 1, square_to_check_y, open_list, f_values, g_values, h_values, parents_x, parents_y, &open_index);
            }else{
                //Check for shorter path
                if (g_values[square_to_check_x-1][square_to_check_y] > 10 + g_values[square_to_check_x][square_to_check_y]){
                    //If so update square
                    update_square(open_list_index, square_to_check_x, square_to_check_y, square_to_check_x - 1, square_to_check_y, open_list, f_values, g_values, h_values, parents_x, parents_y);
                }
                
            }
        }
        
        closed_list_index = in_list(square_to_check_x, square_to_check_y + 1, closed_list, closed_index);
        //printf("closed_list_index right: %d\n", closed_list_index);
        if (closed_list_index == -1 && square_to_check_y < MAP_WIDTH - 1 && currentMap[square_to_check_x][square_to_check_y + 1] == 0){
            int open_list_index = in_list(square_to_check_x, square_to_check_y + 1, open_list, open_index);
            //printf("open_list_index right: %d\n", open_list_index);
            if (open_list_index == -1){
                //Add square
                add_square(square_to_check_x, square_to_check_y, square_to_check_x, square_to_check_y + 1, open_list, f_values, g_values, h_values, parents_x, parents_y, &open_index);
            }else{
                //Check for shorter path
                if (g_values[square_to_check_x][square_to_check_y + 1] > 10 + g_values[square_to_check_x][square_to_check_y]){
                    //If so update square
                    update_square(open_list_index, square_to_check_x, square_to_check_y, square_to_check_x, square_to_check_y + 1, open_list, f_values, g_values, h_values, parents_x, parents_y);
                }
            }
        }
        
        closed_list_index = in_list(square_to_check_x + 1, square_to_check_y, closed_list, closed_index);
        //printf("closed_list_index bottom: %d\n", closed_list_index);
        if (closed_list_index == -1 && square_to_check_x < MAP_HEIGHT - 1 && currentMap[square_to_check_x + 1][square_to_check_y] == 0){
            int open_list_index = in_list(square_to_check_x + 1, square_to_check_y, open_list, open_index);
            //printf("open_list_index bottom: %d\n", open_list_index);
            if (open_list_index == -1){
                //Add square
                add_square(square_to_check_x, square_to_check_y, square_to_check_x + 1, square_to_check_y, open_list, f_values, g_values, h_values, parents_x, parents_y, &open_index);
            }else{
                //Check for shorter path
                if (g_values[square_to_check_x + 1][square_to_check_y] > 10 + g_values[square_to_check_x][square_to_check_y]){
                    //If so update square
                    update_square(open_list_index, square_to_check_x, square_to_check_y, square_to_check_x + 1, square_to_check_y, open_list, f_values, g_values, h_values, parents_x, parents_y);
                }
            }
        }
        
        closed_list_index = in_list(square_to_check_x, square_to_check_y - 1, closed_list, closed_index);
        //printf("closed_list_index left: %d\n", closed_list_index);
        if (closed_list_index == -1 && square_to_check_y > 0 && currentMap[square_to_check_x][square_to_check_y - 1] == 0){
            int open_list_index = in_list(square_to_check_x, square_to_check_y - 1, open_list, open_index);
            //printf("open_list_index left: %d\n", open_list_index);
            if (open_list_index == -1){
                //Add square
                add_square(square_to_check_x, square_to_check_y, square_to_check_x, square_to_check_y - 1, open_list, f_values, g_values, h_values, parents_x, parents_y, &open_index);
            }else{
                //Check for shorter path
                if (g_values[square_to_check_x][square_to_check_y - 1] > 10 + g_values[square_to_check_x][square_to_check_y]){
                    //If so update square
                    update_square(open_list_index, square_to_check_x, square_to_check_y, square_to_check_x, square_to_check_y - 1, open_list, f_values, g_values, h_values, parents_x, parents_y);
                }
            }
        }
        
        if (closed_list[closed_index - 1][0] == end_coordinate[0][0] && closed_list[closed_index - 1][1] == end_coordinate[0][1]){
            //printf("Closed target!!!\n");
            int ret_step_index = 284;
            int current_x_pos = end_coordinate[0][0];
            int current_y_pos = end_coordinate[0][1];
            static int temp_ret_steps[285][2];
            for(x = 0; x < 285; x ++) {
                for(y = 0; y < 2; y ++){
                    temp_ret_steps[x][y] = -1;
                    ret_steps[x][y] = -1;
                } 
            }
            while (current_x_pos != start_coordinate[0][0] || current_y_pos != start_coordinate[0][1]){
                temp_ret_steps[ret_step_index][0] = current_x_pos;
                temp_ret_steps[ret_step_index][1] = current_y_pos;
                int temp_x = parents_x[current_x_pos][current_y_pos];
                int temp_y = parents_y[current_x_pos][current_y_pos];
                current_x_pos = temp_x;
                current_y_pos = temp_y;
                ret_step_index--;
            }
            temp_ret_steps[ret_step_index][0] = start_coordinate[0][0];
            temp_ret_steps[ret_step_index][1] = start_coordinate[0][1];
            int step_number = 285 - ret_step_index;
            for (int i=0; i< step_number ; i++) {
                for (int j=0; j<2; j++) {
                    ret_steps[i][j] = temp_ret_steps[ret_step_index + i][j];
                }
            }
            
            for (int i=0; i<255 ; i++) {
                for (int j=0; j<2; j++) {
                    //printf(" %d", ret_steps[i][j]);
                }
                //printf("\n");
            }
            break;
        }
    }
}

int find_lowest_f_square(int f_values[15][19], int open_list[285][2], int open_index){
    //printf("Inside find_lowest_f_square()\n");
    int j = 0;
    while(open_list[j][0] == -1){
        j++;
    }
    int lowest_f_value = f_values[open_list[j][0]][open_list[j][1]];
    //printf("lowest_f_value: %d\n", lowest_f_value);
    int lowest_f_index = j;
    for (int i = j; i < open_index; i++){
        if (open_list[i][0] != -1 && open_list[i][1] != -1 ){
            if (f_values[open_list[i][0]][open_list[i][1]] <= lowest_f_value){
                //printf("lowest_f_value old: %d\n", lowest_f_value);
                lowest_f_value = f_values[open_list[i][0]][open_list[i][1]];
                //printf("lowest_f_value new: %d\n", lowest_f_value);
                lowest_f_index = i;
            }
        }
    }
    return lowest_f_index;
}

int in_list(int x_pos, int y_pos, int list[285][2], int max_index){
    for(int i = 0; i < max_index; i++){
        if (list[i][0] == x_pos && list[i][1] == y_pos){
            return i;
        }
    }
    return -1;
}

void add_square(int parent_x, int parent_y, int x, int y, int open_list[285][2], int f_values[15][19], int g_values[15][19], int h_values[15][19], int parents_x[15][19], int parents_y[15][19], int* open_index){
    //printf("Inside add_square()\n");
    //printf("*open_index: %d\n", *open_index);
    open_list[*open_index][0] = x;
    open_list[*open_index][1] = y;
    //printf("open_index was: %d\n", *open_index);
    *open_index = *open_index + 1;
    //printf("open_index is now: %d\n", *open_index);
    parents_x[x][y] = parent_x;
    parents_y[x][y] = parent_y;
    g_values[x][y] = g_values[parent_x][parent_y] + 10;
    h_values[x][y] = abs(end_coordinate[0][0] - x) * 10 + abs(end_coordinate[0][1] - y) * 10;
    f_values[x][y] = g_values[x][y] + h_values[x][y];
}

/*
Need to check this function later.
*/
void update_square(int index, int parent_x, int parent_y, int x, int y, int open_list[285][2], int f_values[15][19], int g_values[15][19], int h_values[15][19], int parents_x[15][19], int parents_y[15][19]){
    //printf("Inside update_square()\n");
    open_list[index][0] = x;
    open_list[index][1] = y;
    parents_x[x][y] = parent_x;
    parents_y[x][y] = parent_y;
    g_values[x][y] = g_values[parent_x][parent_y] + 10;
    h_values[x][y] = abs(end_coordinate[0][0] - x) * 10 + abs(end_coordinate[0][1] - y) * 10;
    f_values[x][y] = g_values[x][y] + h_values[x][y];
}



// //printf("open_index: %d\n", open_index);
// for (int i=0; i<15; i++) {
//     for (int j=0; j<19; j++) {
//         //printf(" %d", h_values[i][j]);
//     }
//     //printf("\n");
// }

// for (int i=0; i<285; i++) {
//     for (int j=0; j<2; j++) {
//         //printf(" %d", closed_list[i][j]);
//     }
//     //printf("\n");
// }

// for (int i=0; i<15; i++) {
//     for (int j=0; j<19; j++) {
//         //printf(" %d", f_values[i][j]);
//     }
//     //printf("\n");
// }


/* [] END OF FILE */
