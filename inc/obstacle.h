#pragma once

#include <time.h>
#include <stdlib.h>
#include "../inc/types.h"
#include "3D_tools.h"

/*=========================== Types ===============================*/

/* Corridor obstacle */
typedef struct Obstacle Obstacle;
struct Obstacle
{
    RectanglePoints rect; /* The four points (corners) of the obstacle shape */
    double section;       /* Value on the z axis (corridor axis) */
    Obstacle *next_obs;   /* Points on the next obstacle */
};

/* Chained list that stores obstacles of the scene */
typedef struct ObstacleList ObstacleList;
struct ObstacleList
{
    Obstacle *first_obs; /* Points on the first obstacle */
    Obstacle *last_obs;  /* Points on the last obstacle */
};

/*=========================== Functions ===============================*/

/* Initalizes an obstacle object thanks to its points and its position in the z axis */
Obstacle *initObstacle(RectanglePoints rect, double section);

/* Initializes an obstacle chained list */
ObstacleList *initObstacleList();

/* Displays the elements stored in the obstacle list */
void printList(ObstacleList list);

/* Removes all the obstacles behing the position on the z axis given */
void removeObs(ObstacleList *list, double racket_pos);

/* Adds a new obstacle in the list */
void add(ObstacleList *list, RectanglePoints coords, double section);

/* Adds a random positioned obstacle in the corridor */
void addRandomObstacle(ObstacleList *list, double ball_pos, double limit);

/* Checks if a rectangle shape (four points) is included in an obstacle object */
int squareInObstacle(Obstacle obstacle, RectanglePoints rect);

/* Frees the allocated objects stored in the allocated list */
void freeObstacles(ObstacleList *obstacles);