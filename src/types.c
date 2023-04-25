
#include <stdio.h>

typedef struct Coords {
    double x;
    double y;
} Coords;


/*
a ----- b
|       |
|       |
c ----- d
*/
typedef struct RectanglePoints {
    Coords a;
    Coords b;
    Coords c;
    Coords d;
} RectanglePoints;



/*void print(RectanglePoints points){
    printf("((%f - %f) == (%f - %f) == (%f - %f) == (%f - %f))\n",
            points.a.x, points.a.y, points.b.x, points.b.y, points.c.x, points.c.y,
                                points.d.x, points.d.y);
}*/