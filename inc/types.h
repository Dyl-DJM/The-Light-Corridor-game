#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Coords
{
    double x;
    double y;
} Coords;

/*
a ----- b
|       |
|       |
c ----- d
*/
typedef struct RectanglePoints
{
    Coords a;
    Coords b;
    Coords c;
    Coords d;
} RectanglePoints;

typedef enum
{
    MOVING = 0,
    STOP = 1
} MovingState;

typedef struct Coords3D
{
    double x;
    double y;
    double z;
} Coords3D;

Coords initCoords(double x, double y);
RectanglePoints initRect(Coords a, Coords d);
void print(RectanglePoints points);