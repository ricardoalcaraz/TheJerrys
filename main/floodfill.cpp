#include "floodfill.h"
/*
 * INPUT: Cell coordinate
 * OUTPUT: lowest distance value of neighboring cells
 * Altered: None
 * Description: Check neighboring open cells and return
 *  minimum distance value.
 */
uint8_t Floodfill::findMinVals(Coord coord){
    uint8_t minVal = cell[coord._y][coord._x].distance;
    for(int i = 0; i < sizeof(bearings); i++){
        Coord neighborCoord = maze.findNeighbor(coord, bearings[i]);

        if(!maze.isOutOfBounds(neighborCoord)){
            // If direction does not collide with wall (neighbour is accessible)
            if(!(bearings[i] & cell[coord._y][coord._x].walls)){
                if(cell[neighborCoord._y][neighborCoord._x].distance < cell[coord._y][coord._x].distance){
                    minVal =cell[neighborCoord._y][neighborCoord._x].distance;
                }
            }
        }
    }
    return minVal;
}

/*
 * INPUT: Cell coordinate
 * OUTPUT: None
 * Altered: cell[][];
 * Description: Updates distances in cell[][] based on new walls found.
 */
void Floodfill::updateDistances(Coord coord){
    if(theStack.empty()){
        theStack.push(coord);

        // Push coordinates of open neighbours onto stack
        for (int i = 0; i < sizeof(bearings); i++){
            Coord neighborCoord = maze.findNeighbor(coord, bearings[i]);

            if(!maze.isOutOfBounds(neighborCoord)){
                // If direction does not collide with wall (neighbour is accessible)
                if(!(bearings[i] & cell[coord._y][coord._x].walls)){
                    theStack.push(neighborCoord);
                }
            }
        }

        while(!theStack.empty()){
            Coord currentCoord = theStack.top();
            theStack.pop();

            uint8_t minVal = findMinVals(currentCoord);

            if(cell[currentCoord._y][currentCoord._x].distance != minVal + 1){
                cell[currentCoord._y][currentCoord._x].distance = minVal + 1;

                // Push coordinates of open neighbours onto stack
                for (int i = 0; i < sizeof(bearings); i++){
                    Coord nextCoord = maze.findNeighbor(currentCoord, bearings[i]);

                    if(!maze.isOutOfBounds(nextCoord)){
                        // If direction does not collide with wall (neighbour is accessible)
                        if(!(bearings[i] & cell[currentCoord._y][currentCoord._x].walls)){
                            theStack.push(nextCoord);
                        }
                    }
                }
            }
        }
    }
}
