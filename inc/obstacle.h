#pragma once

#include "../inc/types.h"



typedef struct Obstacle Obstacle;
struct Obstacle
{
    RectanglePoints obs;
    double z;
    Obstacle *next_obs; /* Points on the next obstacle */
};


typedef struct ObstacleList ObstacleList;
struct ObstacleList
{
    Obstacle *first_obs;   /* Points on the first obstacle */
};



ObstacleList *initObstacleList();

void printList(ObstacleList list);

void removeObs(ObstacleList *list, double z);

void add(ObstacleList *list, RectanglePoints coords, double z);