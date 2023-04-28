
#include "../inc/types.h"


/* Initialize a 2D Coord object with its x and y values */
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


/* Initialize a 3D Coord object with its x, y and z values */
Coords3D initCoords3D(double x, double y, double z)
{
    Coords3D *tmp = malloc(sizeof(*tmp));
    if (tmp == NULL)
    {
        return *tmp;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->z = z;
    return *tmp;
}


/* Initialize a rectangle with two opposite corners */
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


/* Print the rectangle element informations on the console */
void print(RectanglePoints points)
{
    printf("((%f - %f) ; (%f - %f) ; (%f - %f) ; (%f - %f))\n",
           points.a.x, points.a.y, points.b.x, points.b.y, points.c.x, points.c.y,
           points.d.x, points.d.y);
}


/* Computes a double in a given range (This function code commes from :  https://stackoverflow.com/questions/33058848/generate-a-random-double-between-1-and-1) */
double randRange(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}