#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <stack>

#include "cell.h"
#include "coord.h"
#include "globals.h"
#include "maze.h"
#include "floodfill.h"
#include "debugtools.h"

Maze maze;
Floodfill floodfill;
DebugTools debug;

// cell[Y][X]
Cell cell[16][16];

// Global stack for memory reasons once implemented on embedded system
std::stack<Coord> theStack;

// Tracking mouse coordinate {y, x}
Coord globalMousePos = {15, 0};

int main()
{
    /* This goes in setup */
    maze.initDistances();
    maze.initWalls();
    /* End Setup */

    globalMousePos = {15, 0};
    debug.printMaze();
    debug.stepThroughMaze();

    return 0;
}
