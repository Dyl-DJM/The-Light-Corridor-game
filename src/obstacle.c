#include "../inc/obstacle.h"

#include <stdlib.h>




ObstacleList *initObstacleList()
{
    ObstacleList *list = malloc(sizeof(*list));

    if (list == NULL)
    {
        return NULL;
    }

    list->first_obs = NULL;
    
    return list;
}



void printList(ObstacleList list)
{
    Obstacle *obstacle = list.first_obs;

    printf("\n\n=== LIST ===\n");
    while (obstacle != NULL)
    {
        print(obstacle->obs);
        printf("%f\n", obstacle->z);
        obstacle = obstacle->next_obs;
    }
    printf("NULL\n");
}


/* NE MARCHE PAS POUR LE PREMIER ELEMENT À CORRIGER*/
void removeObs(ObstacleList *list, double z)
{
    if (list == NULL)
    {
        return;
    }

    Obstacle *obstacle = list->first_obs;

    while(obstacle != NULL){
        Obstacle * danglingElem = obstacle->next_obs;
        while(danglingElem != NULL && danglingElem->z < z){ /* Supression*/
            Obstacle * remove = danglingElem;
            danglingElem = danglingElem->next_obs;
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