#include "debugtools.h"
#include <stdio.h>

/*
 * Altered: none
 * Description: Prints ASCII maze to terminal including dist. values.
 *  Each wall is printed twice (cell and neighboring cell).
 *  This is intended since walls are stored in memory in the same way.
 */
void DebugTools::printMaze(){
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

void DebugTools::stepThroughMaze(){
    while(1){
        do{
            std::cout << '\n' << "Press enter to continue";
        } while (std::cin.get() != '\n');

        // Pretending  read some walls
        maze.updateWalls(EAST|WEST, globalMousePos);
        floodfill.updateDistances(globalMousePos);
        printMaze();

        globalMousePos._y -= 1;
    }
}

void DebugTools::mouseInMaze(){
    for(int i=0; i < 13; i++){
        maze.updateWalls(EAST|WEST, globalMousePos);
        globalMousePos._y -= 1;
    }

    globalMousePos = {7, 0};

    floodfill.updateDistances(globalMousePos);

    printMaze();
}
