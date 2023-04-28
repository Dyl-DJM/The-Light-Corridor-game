#include "../inc/obstacle.h"

#include <stdlib.h>

Obstacle *initObstacle(RectanglePoints rect, double section)
{
    Obstacle *tmp = malloc(sizeof(*tmp));

    if (tmp == NULL)
    {
        return NULL;
    }

    tmp->rect = rect;
    tmp->section = section;
    tmp->next_obs = NULL;

    return tmp;
}

ObstacleList *initObstacleList()
{
    ObstacleList *list = malloc(sizeof(*list));

    if (list == NULL)
    {
        return NULL;
    }

    list->first_obs = NULL;
    list->last_obs = NULL;

    return list;
}

void printList(ObstacleList list)
{
    Obstacle *obstacle = list.first_obs;

    printf("\n\n=== LIST ===\n");
    while (obstacle != NULL)
    {
        print(obstacle->rect);
        printf("%f\n", obstacle->section);
        obstacle = obstacle->next_obs;
    }
    printf("NULL\n");
}

void removeObs(ObstacleList *list, double racket_pos)
{
    if (list == NULL)
    {
        return;
    }

    Obstacle *obstacle = list->first_obs;
    while (obstacle != NULL && obstacle->section < -racket_pos - 2)
    {
        // Suppresion
        Obstacle *remove = obstacle;
        list->first_obs = obstacle->next_obs;
        obstacle = obstacle->next_obs;
        free(remove);
    }
    while (obstacle != NULL)
    {
        Obstacle *danglingElem = obstacle->next_obs;

        while (danglingElem != NULL && danglingElem->section < -racket_pos - 2)
        { /* Supression*/
            Obstacle *remove = danglingElem;
            danglingElem = danglingElem->next_obs;
            free(remove);
        }
        obstacle->next_obs = danglingElem;
        obstacle = obstacle->next_obs;
    }
}

void add(ObstacleList *list, RectanglePoints obs, double section)
{
    Obstacle *to_insert = initObstacle(obs, section);
    if (list == NULL)
    {
        return;
    }
    list->last_obs = to_insert;
    Obstacle *tmp = list->first_obs;
    if (tmp == NULL)
    {
        list->first_obs = to_insert;
        return;
    }
    while (tmp->next_obs != NULL)
    {
        tmp = tmp->next_obs;
    }
    tmp->next_obs = to_insert;
}

void addRandomObstacle(ObstacleList *list, double ball_pos, double limit)
{

    if (list->last_obs == NULL || list->last_obs->section <= -ball_pos + 2)
    {
        double x1 = 0;
        double x2 = 0;
        double y1 = 0;
        double y2 = 0;
        srand(time(NULL));
        int type = rand() % 4;
        switch (type)
        {
        case 0: // DOWN
            x1 = 0;
            y1 = 0;
            x2 = 1.0;
            y2 = (double)rand() / (double)(RAND_MAX / 0.1) + 0.15;
            break;
        case 1: // UP
            x1 = 0;
            y1 = (double)rand() / (double)(RAND_MAX / 0.1) + 0.25;
            x2 = 1.0;
            y2 = 0.5;
            break;
        case 2: // LEFT
            x1 = 0;
            y1 = 0;
            x2 = (double)rand() / (double)(RAND_MAX / 0.2) + 0.3;
            y2 = 0.5;
            break;
        case 3: // RIGHT
            x1 = (double)rand() / (double)(RAND_MAX / 0.2) + 0.5;
            y1 = 0;
            x2 = 1.0;
            y2 = 0.5;
            break;
        }
        RectanglePoints rect = initRect(initCoords(x1, y1), initCoords(x2, y2));
        int z = list->last_obs == NULL ? rand() % 3 - ball_pos + 3 : rand() % 3 + (list->last_obs->section) + 3;
        if(z < limit){
            add(list, rect, z);
        }
    }
}

int squareInObstacle(Obstacle obstacle, RectanglePoints rect)
{

    // print(obstacle.rect);
    // print(rect);

    if (obstacle.rect.a.x <= rect.a.x && rect.a.x <= obstacle.rect.d.x)
    {
        if (obstacle.rect.a.y <= rect.a.y && rect.a.y <= obstacle.rect.d.y)
        {
            return 1;
        }
    }

    if (obstacle.rect.a.x <= rect.b.x && rect.b.x <= obstacle.rect.d.x)
    {
        if (obstacle.rect.a.y <= rect.b.y && rect.b.y <= obstacle.rect.d.y)
        {
            return 1;
        }
    }

    if (obstacle.rect.a.x <= rect.c.x && rect.c.x <= obstacle.rect.d.x)
    {
        if (obstacle.rect.a.y <= rect.c.y && rect.c.y <= obstacle.rect.d.y)
        {
            return 1;
        }
    }

    if (obstacle.rect.a.x <= rect.d.x && rect.d.x <= obstacle.rect.d.x)
    {
        if (obstacle.rect.a.y <= rect.d.y && rect.d.y <= obstacle.rect.d.y)
        {
            return 1;
        }
    }
    return 0;
}



void freeObstacles(ObstacleList * obstacles){ 
    if(obstacles == NULL){  
        return;
    }

    for(Obstacle * current = obstacles->first_obs; current != NULL;){
        Obstacle * remove = current;
        current = current->next_obs;
        free(remove);
        remove = NULL;
    }

    free(obstacles);
    obstacles = NULL;
}