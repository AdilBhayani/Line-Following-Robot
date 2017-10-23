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
    int x;
    
    for (x = 0; x < 50; x++) {
        numOfIntersectionsToDeadEndArray[x] = 0;
    }
    
    end_coordinate[0] = 0;
    end_coordinate[1] = 0;
    dfs();
    generate_directions_1();
    
    //print_ret_steps_dfs();
    if (numOfIntersectionsToDeadEndArray[0] > 0) { 
        for (x = 0; x < intersectionBeforeDeadEndIndex; x++) {
            generate_movements_1(numOfIntersectionsToDeadEndArray[x]);
        }
        generate_movements_last();
    } else {
       generate_movements_last();
    }
    
    /*int i;
    for (i = 0; i < intersectionBeforeDeadEndIndex; i++) {
        usbPutString("Number of intersections beofre dead end are: ");
        usbPutInt(numOfIntersectionsToDeadEndArray[i]);
        usbPutString("\n");
    }*/
    /*for (i = 0; i < intersectionBeforeDeadEndIndex; i++) {
        usbPutString("Coordinates of dead end are: ");
        usbPutInt(prevPosBeforeDeadEndArray[i][0]);
        usbPutString(", ");
        usbPutInt(prevPosBeforeDeadEndArray[i][1]);
        usbPutString("\n");
    }
    for (i = 0; i < intersectionBeforeDeadEndIndex; i++) {
        usbPutString("Orientation to turn at dead end is: ");
        usbPutInt(intersectionOrientation[i]);
        usbPutString("\n");
    }
    */
    /*int v;
    for (v = 0; v < pacmanDirectionsIndex; v++) {
        usbPutString("Turns in the turn array in order are: ");
        usbPutInt(pacmanDirections[v]);
        usbPutString("\n");
    }
    for (v = 0; v < intersectionArrayIndex; v++) {
        usbPutString("Intersection in the intersection array are: ");
        usbPutInt(intersectionArray[v]);
        usbPutString("\n");
    }*/
    
    //Same drill as Astar movements to go here
    
}

void dfs(){
    //printf("Inside dfs()\n");
    int x, y;
    static int ret_visited[15][19];
    for(x = 0; x < 15; x ++) {
        for(y = 0; y < 19; y ++) ret_visited[x][y] = 1;
    }
    int steps_index = 1;
    ret_steps_dfs[0][0] = start_coordinate[0];
    ret_steps_dfs[0][1] = start_coordinate[1];
    for(x = 1; x < DFS_RET_STEPS_SIZE; x ++) {
        for(y = 0; y < 2; y ++) {
            ret_steps_dfs[x][y] = -1;
        }
    }
    
    static int popping_array[285][2];
    int popping_index = 1;
    popping_array[0][0] = start_coordinate[0];
    popping_array[0][1] = start_coordinate[1];
    for(x = 1; x < 285; x ++) {
        for(y = 0; y < 2; y ++) {
            popping_array[x][y] = -1;
        }
    }
    
    static int current_location[2];
    current_location[0] = start_coordinate[0];
    current_location[1] = start_coordinate[1]; 
    
    ret_visited[current_location[0]][current_location[1]] = 0;

    static int target_location[2];
    target_location[0] = 0;
    target_location[1] = 0;
    
    int iteration = DFS_RET_STEPS_SIZE;
    while (iteration > 0 && popping_index > 0 && (current_location[0] != target_location[0] || current_location[1] != target_location[1])){
    if (check_intersection(ret_visited, current_location) > 1){
        //printf("Inside check_intersection if statement at %d %d\n", current_location[0], current_location[1]);
        //Add to popping_array
        popping_array[popping_index][0] = current_location[0];
        popping_array[popping_index][1] = current_location[1];
        popping_index++;
    }
    if (current_location[0] > 0 && currentMap[current_location[0] - 1][current_location[1]] == 0 && ret_visited[current_location[0] - 1][current_location[1]] == 1){
        current_location[0] -= 1;
    }else if (current_location[1] < (MAP_WIDTH - 1) && currentMap[current_location[0]][current_location[1] + 1] == 0 && ret_visited[current_location[0]][current_location[1] + 1] == 1){
        current_location[1] += 1;
    }else if (current_location[0] < (MAP_HEIGHT - 1) && currentMap[current_location[0] + 1][current_location[1]] == 0 && ret_visited[current_location[0] + 1][current_location[1]] == 1){
        current_location[0] += 1;
    }else if (current_location[1] > 0 && currentMap[current_location[0]][current_location[1] - 1] == 0 && ret_visited[current_location[0]][current_location[1] - 1] == 1){
        current_location[1] -= 1;
    }else{
        //printf("Starting backtrack\n");
        int k = 0;
        int last_valid_k = -1;
        while (k < popping_index){
            if (popping_index > k && popping_array[k][0] != -1){
                int temp_current_location[2];
                temp_current_location[0] = popping_array[k][0];
                temp_current_location[1] = popping_array[k][1];
                //printf("Test check\n");
                if (check_intersection(ret_visited,temp_current_location) < 1){
                    popping_array[k][0] = -1;
                    popping_array[k][1] = -1;
                }else{
                    last_valid_k = k;
                }
            }
            k++;
        }
        //printf("last_valid_k is: %d\n", last_valid_k);
        if (last_valid_k != -1){
            start_coordinate[0] = current_location[0];
            start_coordinate[1] = current_location[1];
            end_coordinate[0] = popping_array[last_valid_k][0];
            end_coordinate[1] = popping_array[last_valid_k][1];
            a_star();
            int index = 1;
            while (ret_steps[index][0] != -1){
                ret_steps_dfs[steps_index][0] = ret_steps[index][0];
                ret_steps_dfs[steps_index][1] = ret_steps[index][1];
                steps_index++;
                index++;
            }
            ret_steps_dfs[steps_index][0] = -1;
            ret_steps_dfs[steps_index][1] = -1;
            steps_index--;
            current_location[0] = popping_array[last_valid_k][0];
            current_location[1] = popping_array[last_valid_k][1];
        }else{
            break;
        }
    }
    ret_steps_dfs[steps_index][0] = current_location[0];
    ret_steps_dfs[steps_index][1] = current_location[1];
    steps_index++;
    ret_visited[current_location[0]][current_location[1]] = 0;
    iteration--;
    }
}

int check_intersection(int ret_visited[15][19], int current_location[2]){
    //printf("Inside check_intersection() at %d %d\n", current_location[0], current_location[1]);
    int count = 0;
    if (current_location[0] > 0 && currentMap[current_location[0] - 1][current_location[1]] == 0 && ret_visited[current_location[0] - 1][current_location[1]] == 1){
        //printf("North\n");
        count++;
    }
    if (current_location[1] < (MAP_WIDTH - 1) && currentMap[current_location[0]][current_location[1] + 1] == 0 && ret_visited[current_location[0]][current_location[1] + 1] == 1){
        //printf("East\n");
        count++;
    }
    if (current_location[0] < (MAP_HEIGHT - 1) && currentMap[current_location[0] + 1][current_location[1]] == 0 && ret_visited[current_location[0] + 1][current_location[1]] == 1){
        //printf("South\n");
        count++;
    }
    if (current_location[1] > 0 && currentMap[current_location[0]][current_location[1] - 1] == 0 && ret_visited[current_location[0]][current_location[1] - 1] == 1){
        //printf("West\n");
        count++;
    }
    //printf("Count is: %d\n", count);
    return count;
}

/*
 * In this level, 5 pellets will be placed across the field. The
 * location of the pellets will be given to you as the list. The 
 * challenge is to make the Pacman plan a route from the current
 * position to first unconsumed pellet in the list. The robot’s
 * starting position will be given.
 */
void play_pacman_2(){
    end_coordinate[0] = food_list[0][0]; //set x and y coordinates of first item in food list
    end_coordinate[1] = food_list[0][1]; 
    int i;
    int x;
    for (i = 0; i < 5; i++) {
        set_start_end(i);
        //print_ret_steps();
        generate_directions();
    }
    
    firstPelletFlag = 1;
    //LED_Write(1);
    /*usbPutString("numOfIntersections is: ");
    usbPutInt(pelletIntersectionArray[0]);
    usbPutString("\n");
    usbPutString("intersectionArrayIterator is: ");
    usbPutInt(intersectionArrayIterator);
    usbPutString("\n");*/
    //intersectionArrayIterator = 0;
    //pelletIterator = 0;
    
    /*usbPutString("iAI is 0 : ");
    usbPutInt(intersectionArrayIterator);
    usbPutString("\n");
    usbPutString("PDC is 0 : ");
    usbPutInt(pacmanDirectionsCounter);
    usbPutString("\n");
    usbPutString("pelletIterator is 0 : ");
    usbPutInt(pelletIterator);
    usbPutString("\n");*/

    for (x = 0; x < 5; x++) {
        generate_movements(pelletIntersectionArray[x]);
    }
    /*int v;
    for (v = 0; v < pacmanDirectionsIndex; v++) {
        usbPutString("Ret_steps: ");
        print_ret_steps(v);
        usbPutString("\n");
    } */ 
    
    
   /*int v;
   for (v = 0; v < pacmanDirectionsIndex; v++) {
        usbPutString("Turns in the turn array in order are: ");
        usbPutInt(pacmanDirections[v]);
        usbPutString("\n");
    }
    
  for (v = 0; v < intersectionArrayIndex; v++) {
        usbPutString("Intersection array: ");
        usbPutInt(intersectionArray[v]);
        usbPutString("\n");
    }*/
    /*
    int result;
    for (v = 0; v < lastIntersectionIndex+1; v++) {
        usbPutString("distance to go: ");
        result = distanceToPellet(lastIntersectionPosition[v][0], lastIntersectionPosition[v][1], food_list[v][0],food_list[v][1]);
        usbPutInt(result);
        usbPutString("\n");
    }
   int v;
    for (v = 0; v < pelletIndex+1; v++) {
        usbPutString("Pellet array: ");
        usbPutInt(pelletIntersectionArray[v]);
        usbPutString("\n");
    }*/
    //LED_Write(1);
    //Convert coordinates to directions for robot
    //Implement directions
    //Raise flag after it reaches there to indicate robot need to re-orientate for next food item

    while(1);
}

/*
 * Remote control mode for manually traversing a maze.
 * 
 * The user can tell the robot which way to turn at an intersection
 * using the WSAD keys on a remote terminal connected via bluetooth.
 * Robot autonomously follows lines and waits at intersections 
 * for further instructions.
 */
void remote_control_mode(){
    btPutString("-----------------------------------------------------\n");
    btPutString("--------- Remote Control Operation Group 7 ----------\n");
    btPutString("-----------------------------------------------------\n");
    btPutString("Use the WSAD keys to remotely control the robot.\n");

    char cha;
    while(1) {
        cha = btGetChar();
        if (cha == 119) robot_follow_line(STRAIGHT);
        if (cha == 115) robot_follow_line(U_TURN);
        if (cha == 97) robot_follow_line(LEFT);
        if (cha == 100) robot_follow_line(RIGHT);
    }
}

void set_start_end(uint8 next_pellet) {
    if (next_pellet > 0) {
        start_coordinate[0] = food_list[next_pellet - 1][0];
        start_coordinate[1] = food_list[next_pellet - 1][1];
        end_coordinate[0] = food_list[next_pellet][0];
        end_coordinate[1] = food_list[next_pellet][1];
    }
    a_star(); 
}

void print_ret_steps() {
    int i;
    for (i = 0; i < 285; i++){ 
        if (ret_steps[i][0] != -1){
            usbPutInt(ret_steps[i][0]);
            usbPutString(",");
            usbPutInt(ret_steps[i][1]);
            usbPutString("\n");
        }
    }
}

void print_ret_steps_dfs() {
    int i;
    for (i = 0; i < DFS_RET_STEPS_SIZE; i++){ 
        if (ret_steps_dfs[i][0] != -1){
            usbPutInt(ret_steps_dfs[i][0]);
            usbPutString(",");
            usbPutInt(ret_steps_dfs[i][1]);
            usbPutString("\n");
        }
    }
}

enum intersectionType detectDeadEnd(int currentRow, int currentCol) {
    int i = 0;
    if (currentMap[currentRow+1][currentCol] == 1) {
        i++;
    }
    if (currentMap[currentRow-1][currentCol] == 1) {
        i++;
    }
    if (currentMap[currentRow][currentCol+1] == 1) {
        i++;
    }
    if (currentMap[currentRow][currentCol-1] == 1) {
        i++;
    }
    if (i == 3) {
        deadEndPosArray[intersectionBeforeDeadEndIndex][0] = currentRow;
        deadEndPosArray[intersectionBeforeDeadEndIndex][1] = currentCol;
        return DEAD_END;
    } else {
        return CROSSROADS; 
    }
}

enum intersectionOrNot flagIntersection_1(int currentPosRow, int currentPosCol) {
    if (pacoFacing == NORTH || pacoFacing == SOUTH) {
        if ( (currentMap[currentPosRow][currentPosCol - 1] == 0) ||
            (currentMap[currentPosRow][currentPosCol + 1] == 0) ) {
            //keep track of coordinates of current intersection and increment the intersection count for dead ends
            prevPosBeforeDeadEndArray[intersectionBeforeDeadEndIndex][0] = currentPosRow;
            prevPosBeforeDeadEndArray[intersectionBeforeDeadEndIndex][1] = currentPosCol;
            intersectionOrientation[intersectionBeforeDeadEndIndex] = pacoFacing;
            numOfIntersectionsToDeadEndArray[intersectionBeforeDeadEndIndex]++;
             
            return IS_INTERSECTION;
        } else {
            return NOT_INTERSECTION;
        }
    } else if (pacoFacing == EAST || pacoFacing == WEST) {
        if ( (currentMap[currentPosRow - 1][currentPosCol] == 0) ||
            (currentMap[currentPosRow + 1][currentPosCol] == 0) ) {
            //keep track of coordinates of current intersection and increment the intersection count for dead ends
            prevPosBeforeDeadEndArray[intersectionBeforeDeadEndIndex][0] = currentPosRow;
            prevPosBeforeDeadEndArray[intersectionBeforeDeadEndIndex][1] = currentPosCol;
            intersectionOrientation[intersectionBeforeDeadEndIndex] = pacoFacing;
            numOfIntersectionsToDeadEndArray[intersectionBeforeDeadEndIndex]++;             
            return IS_INTERSECTION;
        } else {
            return NOT_INTERSECTION;
        }
    }     
}

enum intersectionOrNot flagIntersection(int currentPosRow, int currentPosCol) {
    /*usbPutString(" Row and column : ");
    usbPutInt(currentPosRow);
    usbPutString(" , ");
    usbPutInt(currentPosCol);
    usbPutString(" End row and column : ");
    usbPutInt(end_coordinate[0]);
    usbPutString(" , ");
    usbPutInt(end_coordinate[1]);
    usbPutString(" \n");*/
    if (currentPosRow == start_coordinate[0] && currentPosCol == start_coordinate[1] && firstPelletFlag == 0) {
        /*usbPutString(" Row and column : ");
        usbPutInt(currentPosRow);
        usbPutString(" , ");
        usbPutInt(currentPosCol);
        usbPutString(" yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyay \n");*/
        pelletIndex++;
        lastIntersectionIndex++;
        pelletIntersectionArray[pelletIndex]--;
        return IS_INTERSECTION;
    }
    else if (pacoFacing == NORTH || pacoFacing == SOUTH) {
        if ( (currentMap[currentPosRow][currentPosCol - 1] == 0) ||
            (currentMap[currentPosRow][currentPosCol + 1] == 0) ) {
            
            lastIntersectionPosition[lastIntersectionIndex][0] = currentPosRow;
            lastIntersectionPosition[lastIntersectionIndex][1] = currentPosCol;
            return IS_INTERSECTION;
        } else {
            return NOT_INTERSECTION;
        }
    } else if (pacoFacing == EAST || pacoFacing == WEST) {
        if ( (currentMap[currentPosRow - 1][currentPosCol] == 0) ||
            (currentMap[currentPosRow + 1][currentPosCol] == 0) ) {
            //intersectionOrientation[lastIntersectionIndex] = pacoFacing; 
            lastIntersectionPosition[lastIntersectionIndex][0] = currentPosRow;
            lastIntersectionPosition[lastIntersectionIndex][1] = currentPosCol;
            return IS_INTERSECTION;
        } else {
            return NOT_INTERSECTION;
        }
    }     
}

void generate_directions() {
    int i = 0;
    while (ret_steps[i][0] != -1) {
        i++;
    }
    int a;
    for (a = 0; a < i - 1; a++) { 
        if (a == i - 2) { //save the second to last coordinate that the robot is in for in between particles
            prevPosition[0] = ret_steps[a][0];
            prevPosition[1] = ret_steps[a][1];
        }
        enum robotTurns turnToAdd = STRAIGHT;
        if (firstPelletFlag == 0 && a == 0) { //take into account 180 turns, for the cases where the robot needs to turn around after getting first pellet
            //save previous coordinates
            if (prevPosition[0] == ret_steps[a+1][0] && prevPosition[1] == ret_steps[a+1][1]) { //180 turn

                //add a u turn without needing to convert coordinates
                turnToAdd = U_TURN;
            }
            else {
                //decide if we need to turn, and which way to turn
                turnToAdd = convertCoordinates(prevPosition[0], prevPosition[1], ret_steps[a][0], ret_steps[a][1], ret_steps[a+1][0], ret_steps[a+1][1]);
            }
        }
        else if (a == 0 && firstPelletFlag == 1) { //don't check the previous coordinate at start up 
            turnToAdd = STRAIGHT;
        }
        else {
            //decide if we need to turn, and which way to turn
            turnToAdd = convertCoordinates(ret_steps[a-1][0], ret_steps[a-1][1], ret_steps[a][0], ret_steps[a][1], ret_steps[a+1][0], ret_steps[a+1][1]);
        }
        //only add turns to the turn array, not straights
        if (turnToAdd != STRAIGHT) { //if paco needs to turn at current coordinate
            pacmanDirections[pacmanDirectionsIndex] = turnToAdd;
            pacmanDirectionsIndex++;
        }
        
        //determine whether each point is an intersection, and update intersection array accordingly
        enum intersectionOrNot intersectionFlag = flagIntersection(ret_steps[a][0], ret_steps[a][1]);
        if ((intersectionFlag == IS_INTERSECTION) && (turnToAdd != STRAIGHT)) { //if paco is at an intersection
            intersectionArray[intersectionArrayIndex] = TURNING; //mark it as a turning intersection
            pelletIntersectionArray[pelletIndex]++; //keep track of how many intersections it takes to get to each pellet
            /*usbPutString("Intersection array value : ");
            usbPutInt(intersectionArray[intersectionArrayIndex]);
            usbPutString(" Row and column : ");
            usbPutInt(ret_steps[a][0]);
            usbPutString(" , ");
            usbPutInt(ret_steps[a][1]);
            usbPutString(" \n");*/
            intersectionArrayIndex++;          
        }
        else if ((intersectionFlag == IS_INTERSECTION) && (turnToAdd == STRAIGHT)) {
            intersectionArray[intersectionArrayIndex] = NOT_TURNING; //mark it as a turning intersection
            pelletIntersectionArray[pelletIndex]++; //keep track of how many intersections it takes to get to each pellet
            /*usbPutString("Intersection array value : ");
            usbPutInt(intersectionArray[intersectionArrayIndex]);
            usbPutString("Row and column : ");
            usbPutInt(ret_steps[a][0]);
            usbPutString(" , ");
            usbPutInt(ret_steps[a][1]);
            usbPutString(" \n");*/
            intersectionArrayIndex++;
        }
        turnToAdd = STRAIGHT; //reset the value of turnToAdd  
        
        intersectionOrientation[lastIntersectionIndex] = pacoFacing;
    }
    firstPelletFlag = 0;
}

void generate_directions_1() {
    int i = 0;
    while (ret_steps_dfs[i][0] != -1) {
        i++;
    }
    int a;
    for (a = 0; a < i - 1; a++) { 
        enum robotTurns turnToAdd = STRAIGHT;
        if (a != 0) { //don't generate a turn for the first direction because its going straight anyways and we cant access a-1
            if (ret_steps_dfs[a-1][0] == ret_steps_dfs[a+1][0] && ret_steps_dfs[a-1][1] == ret_steps_dfs[a+1][1]) { //180 turn
                //add a u turn without needing to convert coordinates
                turnToAdd = U_TURN;
                
                intersectionOrientation[intersectionBeforeDeadEndIndex] = pacoFacing;               
                
                numOfIntersectionsToDeadEndArray[intersectionBeforeDeadEndIndex]++;
                intersectionArray[intersectionArrayIndex] = TURNING;
                intersectionArrayIndex++;
                

            }
            else {
                //decide if we need to turn, and which way to turn
                turnToAdd = convertCoordinates(ret_steps_dfs[a-1][0], ret_steps_dfs[a-1][1], ret_steps_dfs[a][0], ret_steps_dfs[a][1], ret_steps_dfs[a+1][0], ret_steps_dfs[a+1][1]);
            }
        }
        //only add turns to the turn array, not straights
        if (turnToAdd != STRAIGHT) { //if paco needs to turn at current coordinate
            pacmanDirections[pacmanDirectionsIndex] = turnToAdd;
            pacmanDirectionsIndex++;
        }
        
        if ((detectDeadEnd(ret_steps_dfs[a][0], ret_steps_dfs[a][1]) == DEAD_END) && (a!= 0)) {           
            numOfIntersectionsToDeadEndArray[intersectionBeforeDeadEndIndex]--;
            intersectionBeforeDeadEndIndex++; //increment the position in the dead end intersection counter array
        }
        
        if ((a != 0) && (turnToAdd != U_TURN)) {
            //determine whether each point is an intersection, and update intersection array accordingly
            enum intersectionOrNot intersectionFlag = flagIntersection_1(ret_steps_dfs[a][0], ret_steps_dfs[a][1]);
            if ((intersectionFlag == IS_INTERSECTION) && (turnToAdd != STRAIGHT)) { //if paco is at an intersection
                intersectionArray[intersectionArrayIndex] = TURNING; //mark it as a turning intersection
                intersectionArrayIndex++;          
            }
            else if ((intersectionFlag == IS_INTERSECTION) && (turnToAdd == STRAIGHT)) {
                intersectionArray[intersectionArrayIndex] = NOT_TURNING; //mark it as a turning intersection
                intersectionArrayIndex++;
            }
        }
    }
}


enum robotTurns convertCoordinates(int prevPosRow, int prevPosCol, int currentPosRow, int currentPosCol, int nextPosRow, int nextPosCol) {
    /*usbPutString("current coordinates : ");
    usbPutInt(prevPosRow);
    usbPutString(" , ");
    usbPutInt(prevPosCol); 
    usbPutString(" , ");
    usbPutInt(currentPosRow); 
    usbPutString(" , ");
    usbPutInt(currentPosCol); 
    usbPutString(" , ");
    usbPutInt(nextPosRow);
    usbPutString(" , ");
    usbPutInt(nextPosCol);
    usbPutString(" \n");*/

    
    if (nextPosCol > currentPosCol) { // column has increased
        if (prevPosRow < currentPosRow) { //if row is increasing then robot is going south, and needs to turn left
            pacoFacing = EAST;
            return LEFT;
        }
        else if (prevPosRow > currentPosRow) { //if row is decreasing then robot is going north, and needs to turn right
            pacoFacing = EAST;
            return RIGHT; 
        }
        
    }
    else if (nextPosCol < currentPosCol) { // column has decreased
        if (prevPosRow < currentPosRow) { //if row is increasing then robot is going south, and needs to turn right
            pacoFacing = WEST;
            return RIGHT;
        }
        else if (prevPosRow > currentPosRow) { //if row is decreasing then robot is going north, and needs to turn left
            pacoFacing = WEST;
            return LEFT;
        }
        
    }
    else if (nextPosRow < currentPosRow) { // row has decreased
        if (prevPosCol < currentPosCol) { //if column is increasing then robot is going east, and needs to turn left
            pacoFacing = NORTH;
            return LEFT;
        }
        else if (prevPosCol > currentPosCol) { //if column is decreasing then robot is going west, and needs to turn right
            pacoFacing = NORTH;
            return RIGHT;
        }
        
    }
    else if (nextPosRow > currentPosRow) { // row has increased
        if (prevPosCol < currentPosCol) { //if column is increasing then robot is going east, and needs to turn right
            pacoFacing = SOUTH;
            return RIGHT;
        }
        else if (prevPosCol > currentPosCol) { //if column is decreasing then robot is going west, and needs to turn left
            pacoFacing = SOUTH;
            return LEFT;
        } 
        
    }
    return STRAIGHT; //else add straight
}

static int distanceToPellet(int intersectionRow, int intersectionCol, int pelletRow, int pelletCol) {
    int rowDiff = intersectionRow - pelletRow;
    int colDiff = intersectionCol - pelletCol;
    if (rowDiff < 0) {
        rowDiff = rowDiff * (-1);
    }
    if (colDiff < 0) {
        colDiff = colDiff * (-1);
    }
    if (rowDiff > 0) {
        return rowDiff;
    }
    if (colDiff > 0) {
        return colDiff;
    }   
}


void generate_movements_1(int numOfIntersections) {
    enum intersectionType pacoAt;
    int distanceForward;

    pacoAt = robot_follow_line(STRAIGHT); //tell paco to go straight at the very beginning of his journey
    int temp = intersectionArrayIterator;   
    
    for (intersectionArrayIterator = intersectionArrayIterator; intersectionArrayIterator < (numOfIntersections+temp - 1); intersectionArrayIterator++) {          
        if (intersectionArray[intersectionArrayIterator] == TURNING) { //paco needs to turn 
            pacoAt = robot_follow_line(pacmanDirections[pacmanDirectionsCounter]);
            pacmanDirectionsCounter++;
        } else {
            pacoAt = robot_follow_line(STRAIGHT); 
        }
    }
    //paco will be stopped at the intersection just before the dead end.
    if (intersectionArray[intersectionArrayIterator] == TURNING) { //orient paco to move straight towards dead end
        if (pacmanDirections[pacmanDirectionsCounter] == LEFT) {
            pacman_left_turn(); //turn to orientate 
        } 
        else if (pacmanDirections[pacmanDirectionsCounter] == RIGHT) {
            pacman_right_turn();
        }
        pacmanDirectionsCounter++;
    }
    intersectionArrayIterator++;
         
    //work out distance to travel forward to next pellet
    distanceForward = distanceToPellet(prevPosBeforeDeadEndArray[deadEndIterator][0], prevPosBeforeDeadEndArray[deadEndIterator][1], deadEndPosArray[deadEndIterator][0], deadEndPosArray[deadEndIterator][1]);

    
    //move paco straight the correct amount to reach the dead end
    forward_deadend();
    deadEndIterator++; //increment the array to indicate that we have reached the current dead end
    intersectionArrayIterator++; //increment the intersection array iterator to take into account that the pellet is an intersection that has been acknowledged   
    
    //check if paco needs to u turn to get back on track
    if (pacmanDirections[pacmanDirectionsCounter] == U_TURN) {
        pacman_u_turn(); //make u turn if needed
        pacmanDirectionsCounter++;
    }
}


void generate_movements_last() {
    LED_Write(1);
    enum intersectionType pacoAt;

    pacoAt = robot_follow_line(STRAIGHT); //tell paco to go straight at the very beginning of his journey
    //int temp = intersectionArrayIterator;   
    
    for (intersectionArrayIterator = intersectionArrayIterator; intersectionArrayIterator < intersectionArrayIndex; intersectionArrayIterator++) {          
        if (intersectionArray[intersectionArrayIterator] == TURNING) { //paco needs to turn 
            pacoAt = robot_follow_line(pacmanDirections[pacmanDirectionsCounter]);
            pacmanDirectionsCounter++;
        } else {
            pacoAt = robot_follow_line(STRAIGHT); 
        }
    }
}

void generate_movements(int numOfIntersections) {
    enum intersectionType pacoAt;
    int distanceForward;
    //iterate through the intersection array up to the intersection just before the food pellet
    pacoAt = robot_follow_line(STRAIGHT); //tell paco to go straight at the very beginning of his journey
    int temp = intersectionArrayIterator;   
    for (intersectionArrayIterator = intersectionArrayIterator; intersectionArrayIterator < (numOfIntersections+temp - 1); intersectionArrayIterator++) {      
        if (intersectionArray[intersectionArrayIterator] == TURNING) { //paco needs to turn 
            pacoAt = robot_follow_line(pacmanDirections[pacmanDirectionsCounter]);
            pacmanDirectionsCounter++;
        } else {
            pacoAt = robot_follow_line(STRAIGHT); 
        }
    }
    //paco will be stopped at the intersection just before the food pellet.
    if (intersectionArray[intersectionArrayIterator] == TURNING) { //orient paco to move straight towards food pellet
        if (pacmanDirections[pacmanDirectionsCounter] == LEFT) {
            pacman_left_turn(); //turn to orientate 
            pacmanDirectionsCounter++;
        } 
        else if (pacmanDirections[pacmanDirectionsCounter] == RIGHT) {
            pacman_right_turn();
            pacmanDirectionsCounter++;
        }
    }
    intersectionArrayIterator++;
     ////////////////
    //work out distance to travel forward to next pellet
    distanceForward = distanceToPellet(lastIntersectionPosition[pelletIterator][0], lastIntersectionPosition[pelletIterator][1], food_list[pelletIterator][0], food_list[pelletIterator][1]);
    
    //move paco straight the correct amount to reach the food pellet
    robot_forward(distanceForward, intersectionOrientation[pelletIterator]);
    pelletIterator++; //increment the array to indicate that we have reached the current pellet
    intersectionArrayIterator++; //increment the intersection array iterator to take into account that the pellet is an intersection that has been acknowledged
    
    //check if paco needs to u turn to get back on track
    if (pacmanDirections[pacmanDirectionsCounter] == U_TURN) {
        pacman_u_turn(); //make u turn if needed
        pacmanDirectionsCounter++;
    }
}

void a_star(){
    //printf("Inside a_star()\n");
    //printf("start_coordinate is X: %d, Y: %d\n", start_coordinate[0], start_coordinate[1]);
    //printf("end_coordinate is X: %d, Y: %d\n", end_coordinate[0], end_coordinate[1]);
    
    int x, y;
    static int ret_visited[15][19];
    for(x = 0; x < 15; x ++) {
        for(y = 0; y < 19; y ++) ret_visited[x][y] = 1;
    }
    static int open_list[285][2];
    static int closed_list[285][2];
    open_list[0][0] = start_coordinate[0];
    open_list[0][1] = start_coordinate[1];
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
    h_values[start_coordinate[0]][start_coordinate[1]] = abs(end_coordinate[0] - start_coordinate[0]) * 10 + abs(end_coordinate[1] - start_coordinate[1]) * 10;
    f_values[start_coordinate[0]][start_coordinate[1]] = abs(end_coordinate[0] - start_coordinate[0]) * 10 + abs(end_coordinate[1] - start_coordinate[1]) * 10;

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
        
        if (closed_list[closed_index - 1][0] == end_coordinate[0] && closed_list[closed_index - 1][1] == end_coordinate[1]){
            //printf("Closed target!!!\n");
            int ret_step_index = 284;
            int current_x_pos = end_coordinate[0];
            int current_y_pos = end_coordinate[1];
            static int temp_ret_steps[285][2];
            for(x = 0; x < 285; x ++) {
                for(y = 0; y < 2; y ++){
                    temp_ret_steps[x][y] = -1;
                    ret_steps[x][y] = -1;
                } 
            }
            while (current_x_pos != start_coordinate[0] || current_y_pos != start_coordinate[1]){
                temp_ret_steps[ret_step_index][0] = current_x_pos;
                temp_ret_steps[ret_step_index][1] = current_y_pos;
                int temp_x = parents_x[current_x_pos][current_y_pos];
                int temp_y = parents_y[current_x_pos][current_y_pos];
                current_x_pos = temp_x;
                current_y_pos = temp_y;
                ret_step_index--;
            }
            temp_ret_steps[ret_step_index][0] = start_coordinate[0];
            temp_ret_steps[ret_step_index][1] = start_coordinate[1];
            int step_number = 285 - ret_step_index;
            for (int i=0; i< step_number ; i++) {
                for (int j=0; j<2; j++) {
                    ret_steps[i][j] = temp_ret_steps[ret_step_index + i][j];
                }
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
    h_values[x][y] = abs(end_coordinate[0] - x) * 10 + abs(end_coordinate[1] - y) * 10;
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
    h_values[x][y] = abs(end_coordinate[0] - x) * 10 + abs(end_coordinate[1] - y) * 10;
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
