
#include "../inc/types.h"

Coords initCoords(double x, double y)
{
    Coords *tmp = malloc(sizeof(*tmp));
    if (tmp == NULL)
    {
        return *tmp;
    }
    tmp->x = x;
    tmp->y = y;
    return *tmp;
}

RectanglePoints initRect(Coords a, Coords d)
{
    RectanglePoints *tmp = malloc(sizeof(*tmp));
    if (tmp == NULL)
    {
        return *tmp;
    }
    tmp->a = a;
    tmp->d = d;
    tmp->b = initCoords(d.x, a.y);
    tmp->c = initCoords(a.x, d.y);
    return *tmp;
}

void print(RectanglePoints points)
{
    printf("((%f - %f) ; (%f - %f) ; (%f - %f) ; (%f - %f))\n",
           points.a.x, points.a.y, points.b.x, points.b.y, points.c.x, points.c.y,
           points.d.x, points.d.y);
}