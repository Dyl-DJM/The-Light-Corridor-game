#pragma once

#include <time.h>
#include "../inc/types.h"
#include "3D_tools.h"

typedef struct Obstacle Obstacle;
struct Obstacle
{
    RectanglePoints rect;
    double section;
    Obstacle *next_obs; /* Points on the next obstacle */
};

typedef struct ObstacleList ObstacleList;
struct ObstacleList
{
    Obstacle *first_obs; /* Points on the first obstacle */
    Obstacle *last_obs;  /* Points on the last obstacle */
};

Obstacle *initObstacle(RectanglePoints rect, double section);

ObstacleList *initObstacleList();

void printList(ObstacleList list);

void removeObs(ObstacleList *list, double racket_pos);

void add(ObstacleList *list, RectanglePoints coords, double section);

void addRandomObstacle(ObstacleList *list, double ball_pos);

int squareInObstacle(Obstacle obstacle, RectanglePoints rect);
