#include "sensor.h"

/* INPUT: sensor data fetched
 * OUTPUT: 0b0000WSEN formatted byte to represent wall
 * Altered: none
 * Description: Reads IR sensors to determine walls.
 */
uint8_t Sensor::getWalls(){
    uint8_t walls = EAST|WEST;

    return walls;
}
