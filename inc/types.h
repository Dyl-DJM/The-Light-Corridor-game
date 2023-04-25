#pragma once

#include "../src/types.c"

typedef enum {
    MOVING = 0,
    STOP = 1
} MovingState;


typedef struct Coords3D {
    double x;
    double y;
    double z;
} Coords3D;


/*RectanglePoints;*/

/*void print(RectanglePoints points);*/