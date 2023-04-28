#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*======================= Types ==========================*/

/* Represents a 2D element */
typedef struct Coords
{
    double x;
    double y;
} Coords;


/*
Represents all the points coordinates of a rectangle shape

c ----- d
|       |
|       |
a ----- b
*/
typedef struct RectanglePoints
{
    Coords a;
    Coords b;
    Coords c;
    Coords d;
} RectanglePoints;


/* Represents the movement state of an object */
typedef enum
{
    MOVING = 0,
    STOP = 1
} MovingState;


/* Represents a 3D element */
typedef struct Coords3D
{
    double x;
    double y;
    double z;
} Coords3D;


/* Particle object representation*/
typedef struct Part{
	Coords coords;
	double init_y;  /* The value on the y axis the particle was initilized with */

    /* Its color informations*/
	double r;
	double g;
	double b;
}Part;


/*======================= Functions ==========================*/

/* Initialize a 2D Coord object with its x and y values */
Coords initCoords(double x, double y);

/* Initialize a 3D Coord object with its x, y and z values */
Coords3D initCoords3D(double x, double y, double z);

/* Initialize a rectangle with two opposite corners */
RectanglePoints initRect(Coords a, Coords d);

/* Print the rectangle element informations on the console */
void print(RectanglePoints points);     /* <= Debug use */

/* Computes a double in a given range (This function code commes from :  https://stackoverflow.com/questions/33058848/generate-a-random-double-between-1-and-1) */
double randRange(double min, double max);