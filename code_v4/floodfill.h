#ifndef FLOODFILL_H
#define FLOODFILL_H
#include <array>
#include "globals.h"
#include "coord.h"
#include "cell.h"
#include "maze.h"

/*
 * floodfill.h
 *
 * Any floodfill related functions go here
 */
class Floodfill
{
private:
    std::array<uint8_t,4> bearings = {NORTH, EAST, SOUTH, WEST};

    Maze maze;
public:

    uint8_t findMinVals(Coord coord);

    void updateDistances(Coord coord);
};

#endif
