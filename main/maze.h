/* Distance: number of cells to center as an integer
 *
 * Bit order for walls:
 * 0b000VWSEN
 * V: visted, 1 for visited, 0 for unvisited
 * N: north, 1 for wall 0 for no wall
 * E: east, 1 for wall 0 for no wall
 * S: south, 1 for wall 0 for no wall
 * W: west, 1 for wall 0 for no wall
 */
#ifndef maze_h
#define maze_h
#include <stdint.h>


struct maze
{
    uint8_t distance;
    uint8_t walls;
};

#endif
