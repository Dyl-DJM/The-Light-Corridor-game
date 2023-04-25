
#include "../inc/types.h"



void print(RectanglePoints points){
    printf("((%f - %f) == (%f - %f) == (%f - %f) == (%f - %f))\n",
            points.a.x, points.a.y, points.b.x, points.b.y, points.c.x, points.c.y,
                                points.d.x, points.d.y);
}