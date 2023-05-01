/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Bonus module gathers all the mechanic that    =
=  concerns the bonus of the game.                   =
=  We can find the list of bonus management there    =
=													 =
======================================================
*/

#include "../inc/bonus.h"

/* Initializes a bonus */
BonusObject *initBonus(Coords3D coords, double radius, Bonus type)
{
    BonusObject *tmp = malloc(sizeof(*tmp));

    if (tmp == NULL)
    {
        return NULL;
    }

    tmp->coords = coords;
    tmp->r = radius;
    tmp->type = type;
    tmp->next_bonus = NULL;

    return tmp;
}

/* Initializes an empty list of bonus */
BonusList *initBonusList()
{
    BonusList *list = malloc(sizeof(*list));

    if (list == NULL)
    {
        return NULL;
    }

    list->first_bonus = NULL;
    list->last_bonus = NULL;

    return list;
}

/* Console display of a bonus */
void printBonus(BonusObject bonus)
{
    printf("(%f, %f, %f) => %f => (type : %d)\n", bonus.coords.x, bonus.coords.y, bonus.coords.z, bonus.r, bonus.type);
}

/* Display the elements stored in the bonus list */
void printBonusList(BonusList list)
{
    BonusObject *bonus = list.first_bonus;

    while (bonus != NULL)
    {
        printBonus(*bonus);
        bonus = bonus->next_bonus;
    }
}

/* Removes all the bonus stored which are behind a given position */
void removeBonus(BonusList *list, double racket_pos)
{
    if (list == NULL)
    {
        return;
    }

    BonusObject *bonus = list->first_bonus;
    while (bonus != NULL && bonus->coords.z > racket_pos + 2)
    {
        // Suppresion
        BonusObject *remove = bonus;
        list->first_bonus = bonus->next_bonus;
        bonus = bonus->next_bonus;
        free(remove);
    }
}

/* Adds a bonus on a list */
void addBonus(BonusList *list, Coords3D coords, double radius, Bonus type)
{
    BonusObject *to_insert = initBonus(coords, radius, type);
    if (list == NULL)
    {
        return;
    }
    list->last_bonus = to_insert;
    BonusObject *tmp = list->first_bonus;
    if (tmp == NULL)
    {
        list->first_bonus = to_insert;
        return;
    }
    while (tmp->next_bonus != NULL)
    {
        tmp = tmp->next_bonus;
    }
    tmp->next_bonus = to_insert;
}

/* Adds a random positioned bonus in the list */
void addRandomBonus(BonusList *list, double ball_pos, double limit)
{
    if (list->last_bonus == NULL || list->last_bonus->coords.z >= ball_pos - 3)
    {
        Bonus type = NONE;
        double x = (rand() % 100) / 100.0;
        double y = (rand() % 50) / 100.0;
        if (x <= 0.06)
        {
            x = 0.06;
        }
        if (x >= 0.94)
        {
            x = 0.94;
        }
        if (y <= 0.06)
        {
            y = 0.06;
        }
        if (y >= 0.44)
        {
            y = 0.44;
        }
        int tmp = rand() % 2;
        switch (tmp)
        {
        case 0:
            type = GLUE;
            break;
        case 1:
            type = LIFE;
            break;
        }
        int z = list->last_bonus == NULL ? ball_pos - rand() % 3 - 1.5 : (list->last_bonus->coords.z) - rand() % 3 - 7.5;
        if (z < limit)
        {
            addBonus(list, initCoords3D(x, y, z), 0.05, type);
        }
    }
}

/* Checks if a 3D point is included in a sphere */
int pointInSphere(Coords3D origin, Coords point, double section, double radius)
{
    double x = pow((point.x - origin.x), 2);
    double y = pow((point.y - origin.y), 2);
    double z = pow((section - origin.z), 2);

    double d = sqrt(x + y + z);
    if (d <= radius + 0.2)
    {
        return 1;
    }
    return 0;
}

/* Checks if a rectangle goes through a bonus */
int squareInBonus(BonusObject bonus, RectanglePoints rect, double section)
{
    if (pointInSphere(bonus.coords, rect.a, section, bonus.r))
    {
        return 1;
    }
    if (pointInSphere(bonus.coords, rect.b, section, bonus.r))
    {
        return 1;
    }
    if (pointInSphere(bonus.coords, rect.c, section, bonus.r))
    {
        return 1;
    }
    if (pointInSphere(bonus.coords, rect.d, section, bonus.r))
    {
        return 1;
    }
    return 0;
}

/*Frees the bonus list */
void freeBonus(BonusList *list)
{
    if (list == NULL)
    {
        return;
    }

    for (BonusObject *current = list->first_bonus; current != NULL;)
    {
        BonusObject *remove = current;
        current = current->next_bonus;
        free(remove);
        remove = NULL;
    }

    free(list);
    list = NULL;
}

/* Removes the first bonus of the list */
void removeFirst(BonusList *list)
{
    if (list == NULL)
    {
        return;
    }

    BonusObject *to_remove = list->first_bonus;
    list->first_bonus = to_remove->next_bonus;

    free(to_remove);
    to_remove = NULL;
}