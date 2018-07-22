#ifndef GLOBALS_H
#define GLOBALS_H

#include <stack>
#include "cell.h"
#include "coord.h"

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8

// cell[Y][X]
extern Cell cell[16][16];

// Global stack for memory reasons once implemented on embedded system
extern std::stack<Coord> theStack;

// Tracking mouse coordinate {y, x}
extern Coord globalMousePos;

#endif
