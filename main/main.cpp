#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <stack>

#include "testMaze.cpp"
#include "maze.h"
#include "coord.h"

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8

// cell[Y][X]
maze cell[16][16];

// Global stack for memory reasons once implemented on embedded system
std::stack<uint16_t> theStack;

coord globalMousePos = {0, 3};

/*
 * Altered: none
 * Description: Calculate shortest distance between two coordinates.
 */
uint8_t calcDist(uint8_t xpos, uint8_t ypos, uint8_t xtarget, uint8_t ytarget){
    uint8_t dist = (uint8_t) abs(ytarget-ypos)+abs(xtarget-xpos);
    return dist;
}

/*
  * Altered: none
  * Description: Calculate distance from coordinate to one of the
  *  closest 4 center blocks.
  */
uint8_t calcCenter(uint8_t xpos, uint8_t ypos)
{
    uint8_t dist = 0;

    if(ypos < 8){
        if(xpos < 8){
            // Mouse is in the top left of maze
            dist = calcDist(xpos, ypos, 7, 7);
        }
        else{
            // Mouse is in the top right of the maze
            dist = calcDist(xpos, ypos, 8, 7);
        }
    }
    else{
        if(xpos >= 8){
            // Mouse is in bottom right of maze
            dist = calcDist(xpos, ypos, 8, 8);
        }
        else{
            // Mouse is in bottom left of maze
            dist = calcDist(xpos, ypos, 7, 8);
        }
    }
    return dist;
}

/*
 * Altered: cell[][]
 * Description: Enters initial distances considering no walls
 *  into maze[][].
 */
void initDistances(){
    for (int i = 0; i < 16; i++) {
        for(int j = 0; j <16; j++){
            cell[i][j].distance = calcCenter(i, j);
        }
    }
}

/*
 * Altered: cell[][]
 * Description: Enters initial outer walls into maze[][].
 */
void initWalls(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++ ){
            if(i == 0){
                // Cell is along top edge of maze
                cell[i][j].walls = NORTH;
            }
            if(j == 0){
                // Cell is along left edge of maze
                cell[i][j].walls = WEST;
            }
            if(i == 15){
                // Cell is along south edge of maze
                cell[i][j].walls = SOUTH;
            }
            if(j == 15){
                // Cell is along east edge of maze
                cell[i][j].walls = EAST;
            }
        }
    }
    cell[0][0].walls = NORTH|WEST;
    cell[15][0].walls = WEST|SOUTH;
    cell[0][15].walls = NORTH|EAST;
    cell[15][15].walls = EAST|SOUTH;
}

/*
 * Altered: none
 * Description: Prints ASCII maze to terminal including dist. values.
 *  Each wall is printed twice (cell and neighboring cell).
 *  This is intended since walls are stored in memory in the same way.
 */
void printMaze(){
    for(int i = 0; i < 16; i++){

        // Print north walls
        for(int j = 0; j < 16; j++){
            if(cell[i][j].walls & NORTH){
                printf("o---o");
            }
            else{
                printf("o   o");
            }
        }
        printf("\n");

        // Print columns and distance values
        for(int j = 0; j < 16; j++){
            if((cell[i][j].walls & (WEST|EAST)) == (WEST|EAST)){
                printf("|%02d |", cell[i][j]. distance);
            }
            else if(cell[i][j].walls & WEST){
                printf("|%02d  ", cell[i][j].distance);
            }
            else if(cell[i][j].walls & EAST){
                printf(" %02d |", cell[i][j].distance);
            }
            else{
                printf(" %02d  ", cell[i][j].distance);
            }
        }
        printf("\n");

        // Print south walls
        for(int j = 0; j < 16; j++){
            if(cell[i][j].walls & SOUTH){
                printf("o---o");
            }
            else{
                printf("o   o");
            }
        }
        printf("\n");
    }
}

/* INPUT: sensor data fetched
 * OUTPUT: 0b0000WSEN formatted byte to represent wall
 * Altered: none
 * Description: Reads IR sensors to determine walls.
 */
uint8_t getWalls(){
    uint8_t walls = 0;

    return walls;
}

/*
 * INPUT: Walls adjacent to cell, coordinate of cell
 * OUTPUT: none
 * Altered: cell[][]
 * Description: Update walls for cell and neighboring cells in cell[][].
 */
void updateWalls(uint8_t walls, coord currentCoord){

}

/*
 * INPUT: Cell coordinate
 * OUTPUT: lowest distance value of neighboring cells
 * Altered: None
 * Description: Check neighboring open cells and return
 *  minimum distance value.
 */
uint8_t checkMinVals(coord currentCoord){
    uint8_t minVal = 0;

    return minVal;
}

/*
 * INPUT: Cell coordinate
 * OUTPUT: None
 * Altered: cell[][];
 * Description: Updates distances in cell[][] based on new walls found.
 */
void updateDistances(coord currentCoord){
    if(!theStack.empty()){
        /*Push the current cell (the one the robot is standing on) onto the stack

          Repeat the following set of instructions until the stack is empty:

          {
          Pop a cell from the stack
          Is the distance value of this cell == 1 + the minimum value of its open neighbors?

          No -> Change the cell to 1 + the minimum value of its open neighbors and
          push all of the cell’s open neighbors onto the stack to be checked
              Yes -> Do nothing
              }
        */
    }
    else{
        std::cout << "Stack not empty upon initializing.";
    }
}

void floodFill(){

}

int main()
{
    /* This goes in setup */
    //initDistances();
    //initWalls();
    /* End Setup */

    //printMaze();
    return 0;
}
