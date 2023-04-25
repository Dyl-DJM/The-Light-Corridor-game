#pragma once

#include "../src/types.c"

typedef struct Coords {
    double x;
    double y;
} Coords;


typedef enum {
    MOVING = 0,
    STOP = 1
} MovingState;
