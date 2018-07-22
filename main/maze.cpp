#include "maze.h"

/*
 * Altered: none
 * Description: Calculate shortest distance between two coordinates.
 */
uint8_t Maze::calcDist(uint8_t xpos, uint8_t ypos, uint8_t xtarget, uint8_t ytarget){
    uint8_t dist = (uint8_t) abs(ytarget-ypos)+abs(xtarget-xpos);
    return dist;
}

/*
 * Altered: none
 * Description: Calculate distance from coordinate to one of the
 *  closest 4 center blocks.
 */
uint8_t Maze::calcCenter(uint8_t xpos, uint8_t ypos)
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
 * Description: Enters initial outer walls into maze[][].
 */
void Maze::initWalls(){
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
 * Altered: cell[][]
 * Description: Enters initial distances considering no walls
 *  into maze[][].
 */
void Maze::initDistances(){
    for (int i = 0; i < 16; i++) {
        for(int j = 0; j <16; j++){
            cell[i][j].distance = calcCenter(i, j);
        }
    }
}

/* INPUT: Any coordinate
 * OUTPUT: boolean
 * Altered: none
 * Description: Used to determine if a coordinate is a valid maze cell.
 */
bool Maze::isOutOfBounds(Coord coord){
    if((coord._x < 0) || (coord._y < 0) || (coord._x > 15) || (coord._y > 15)){
        return true;
    }
    else{
        return false;
    }
}

/* INPUT: Reference coordinate, direction to move (NORTH, EAST...)
 * OUTPUT: New coordinate
 * Altered: none
 * Description: outputs coordinates of cell to the north, east,
 *  south, west of other cell.
 */
Coord Maze::findNeighbor(Coord coord, uint8_t bearing){
    Coord newCoord = {0,0};
    switch (bearing){
    case NORTH:
        newCoord._x = coord._x;
        newCoord._y = coord._y-1;
        break;
    case EAST:
        newCoord._x = coord._x+1;
        newCoord._y = coord._y;
        break;
    case SOUTH:
        newCoord._x = coord._x;
        newCoord._y = coord._y+1;
        break;
    case WEST:
        newCoord._x = coord._x-1;
        newCoord._y = coord._y;
        break;
    }
    return newCoord;
}

/*
 * INPUT: Walls adjacent to cell, coordinate of cell
 * OUTPUT: none
 * Altered: cell[][]
 * Description: Update walls for cell and neighboring cells in cell[][].
 */
void Maze::updateWalls(uint8_t walls, Coord coord){
    for(int i = 0; i < sizeof(bearings); i++){
        if(walls & bearings[i]){
            // add wall bits
            cell[coord._y][coord._x].walls |= bearings[i];

            Coord neighborCoord = findNeighbor(coord, bearings[i]);
            if(!isOutOfBounds(neighborCoord)){
                // add wall bits for neighbouring cell
                cell[neighborCoord._y][neighborCoord._x].walls |= reverseBearings[i];
            }
        }
    }
}
