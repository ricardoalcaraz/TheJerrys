#ifndef MAZE_H
#define MAZE_H
#include <stdint.h>
#include <cstdlib>
#include <array>
#include "globals.h"

/*
 * maze.h
 *
 * Basic maze operations
 */
class Maze
{
private:
    // For looping through direction
    std::array<uint8_t,4> bearings = {NORTH, EAST, SOUTH, WEST};
    // For complementary walls, changing direction etc.
    std::array<uint8_t,4> reverseBearings = {SOUTH, WEST, NORTH, EAST};
public:
    uint8_t calcDist(uint8_t xpos, uint8_t ypos, uint8_t xtarget, uint8_t ytarget);

    uint8_t calcCenter(uint8_t xpos, uint8_t ypos);

    void initWalls();

    void initDistances();

    bool isOutOfBounds(Coord coord);

    Coord findNeighbor(Coord coord, uint8_t bearing);

    void updateWalls(uint8_t walls, Coord coord);
};

#endif
