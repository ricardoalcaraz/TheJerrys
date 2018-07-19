#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <array>
#include <vector>

#include "testMaze.cpp"
#include "maze.h"

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8

// cell[Y][X]
maze cell[16][16];

uint8_t calcDist(uint8_t xpos, uint8_t ypos, uint8_t xtarget, uint8_t ytarget){
    uint8_t dist = (uint8_t) abs(ytarget-ypos)+abs(xtarget-xpos);
    return dist;
}
int calcCenter(uint8_t xpos, uint8_t ypos)
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

void initDistances(){
    for (int i = 0; i < 16; i++) {
        for(int j = 0; j <16; j++){
            cell[i][j].distance = calcCenter(i, j);
        }
    }

}

void printMaze(maze distances[16][16])
{
    std::vector<std::string> rows;
    std::vector<std::string> columns;

    //First row (always the same)
    for(int i = 0; i < 16; i++){
        std::cout << "o---";
    }
    std::cout << 'o' << std::endl;

    int cellNumber = 0;
    for(int i = 0; i < 16; i++){
        // Print columns
        for(int j = 0; j < 16; j++){
            cellNumber = (15-i) + 16*j;
            if(testMaze[cellNumber] & WEST){
                //std::cout << "|   ";
                printf("|%02d ", cell[i][j].distance);
            }
            else{
                //std::cout << "    ";
                printf(" %02d ", cell[i][j].distance);
            }
        }
        std::cout << '|' << std::endl;

        // Print rows
        for(int j = 0; j < 16; j++){
            cellNumber = (15-i) + 16*j;
            if(testMaze[cellNumber] & SOUTH){
                //std::cout << "o---";
                printf("o---");
            }
            else{
                //std::cout << "o   ";
                printf("o   ");
            }
        }
        std::cout << 'o' << std::endl;
    }
}

int main()
{
    initDistances();
    printMaze(cell);
    return 0;
}
