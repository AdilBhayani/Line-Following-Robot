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
#include <project.h>
#include "motion_control.h"
#include "rf.h"
#include "bluetooth.h"

#ifndef PACMAN_H_
#define PACMAN_H_

#define MAP_HEIGHT 15
#define MAP_WIDTH 19
#define DFS_RET_STEPS_SIZE 1000

static int map[15][19] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

static int map1[15][19] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
    {1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static int map8[15][19] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
    {1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static int currentMap[15][19] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1},
    {1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    
static int food_list[5][2] = 
{{5,4},
{11,3},
{12,15},
{4,17},
{6,11}};

static int start_coordinate[2] = {1,1};

static int end_coordinate[2] = {-1,-1};

static int ret_steps[285][2] = {{0}}; //maximum steps could be 19 * 15 = 285
static int ret_steps_dfs[DFS_RET_STEPS_SIZE][2];
static enum robotTurns pacmanDirections[300] = {STRAIGHT};
static enum intersectionOrNot {TURNING, NOT_TURNING, IS_INTERSECTION, NOT_INTERSECTION};
static enum intersectionOrNot intersectionArray[300] = {NOT_TURNING};
enum robotTurns convertCoordinates(int prevPosRow, int prevPosCol, int currentPosRow, int currentPosCol, int nextPosRow, int nextPosCol);
static int pacmanDirectionsIndex = 0;
static int firstPelletFlag = 1;
static int prevPosition[2] = {-1,-1};
static enum robotOrientation {NORTH, SOUTH, EAST, WEST};
static enum robotOrientation pacoFacing = SOUTH; //will need to hard code this value when given map on the day of testing
static int intersectionArrayIndex = 0;
static int pelletIndex = 0;
static int pelletIntersectionArray[5] = {0};
static int lastIntersectionIndex = 0;
static enum robotOrientation intersectionOrientation[5] = {SOUTH}; //will need to hard code this value when given map on the day of testing
static int lastIntersectionPosition[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
static int distanceToPellet(int intersectionRow, int intersectionCol, int pelletRow, int pelletCol);

void play_pacman_1();
void play_pacman_2();
void remote_control_mode();
void a_star();
void set_start_end(uint8 next_pellet);
void print_ret_steps();
void generate_directions();
void generate_movements(int numOfIntersections);
enum intersectionOrNot flagIntersection(int currentPosRow, int currentPosCol);

int find_lowest_f_square(int f_values[15][19], int open_list[285][2], int open_index);
int in_list(int x_pos, int y_pos, int list[285][2], int max_index);
void add_square(int parent_x, int parent_y, int x, int y, int open_list[285][2], int f_values[15][19], int g_values[15][19], int h_values[15][19], int parents_x[15][19], int parents_y[15][19], int* open_index);
void update_square(int index, int parent_x, int parent_y, int x, int y, int open_list[285][2], int f_values[15][19], int g_values[15][19], int h_values[15][19], int parents_x[15][19], int parents_y[15][19]);

void dfs();
int check_intersection(int ret_visited[15][19], int current_location[2]);
void print_ret_steps_dfs();
#endif /* PACMAN_H_ */

/* [] END OF FILE */

