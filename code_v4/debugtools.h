#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H
#include <stdio.h>
#include <iostream>
#include "globals.h"
#include "maze.h"
#include "floodfill.h"

/*
 * debugtools.h
 *
 * Any functions that will not be uploaded to the final build go here
 */

class DebugTools
{
private:
    Maze maze;
    Floodfill floodfill;
public:
    void printMaze();

    /* For quick testing */
    void stepThroughMaze();

    /* For debugging */
    void mouseInMaze();
};

#endif
