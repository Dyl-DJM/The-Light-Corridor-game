#include "../inc/obstacle.h"

#include <stdlib.h>


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





ObstacleList *initObstacleList(RectanglePoints coords, double z)
{
    ObstacleList *list = malloc(sizeof(*list));
    Obstacle *obs = malloc(sizeof(*obs));

    if (list == NULL || obs == NULL)
    {
        return NULL;
    }

    obs->obs = coords;
    obs->z = z;
    obs->next_obs = NULL;
    list->first_obs = obs;
    
    return list;
}



void printList(ObstacleList list)
{
    Obstacle *obstacle = list.first_obs;

    while (obstacle != NULL)
    {
        /*print(obstacle->obs);*/
        printf("%f\n", obstacle->z);
        obstacle = obstacle->next_obs;
    }
    printf("NULL\n");
}


void removeObs(ObstacleList *list, double z)
{
    if (list == NULL)
    {
        return;
    }

    Obstacle *obstacle = list->first_obs;

    while(obstacle != NULL){
        Obstacle * danglingElem = obstacle->next_obs;
        while(danglingElem != NULL && danglingElem->z > z){ /* Supression*/
            Obstacle * remove = obstacle->next_obs;
            danglingElem= danglingElem->next_obs;
            free(remove);
        }
        obstacle->next_obs = danglingElem;
        obstacle = obstacle->next_obs;
    }
}


void add(ObstacleList *list, RectanglePoints coords, double z)
{
    Obstacle *to_insert = malloc(sizeof(*to_insert));
    if (list == NULL || to_insert == NULL)
    {
        return;
    }
    to_insert->obs = coords;
    to_insert->z = z;

    to_insert->next_obs = list->first_obs;
    list->first_obs = to_insert;
}

int isTouchingObstacle(Obstacle obstacle){

    return 0;
}