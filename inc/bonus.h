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

#pragma once

#include <time.h>
#include "../inc/types.h"

/*============================= Variables ===========================*/

#define TYPES_BONUS_RANGE 2 // Amount of implemented bonus types

/*============================= Types ===========================*/

/* Type of bonus (effect)*/
typedef enum Bonus
{
    NONE,
    GLUE,
    LIFE
} Bonus;

/* A bonus object representation */
typedef struct BonusObject BonusObject;
struct BonusObject
{
    Coords3D coords; /* center of the bonus object sphere representation */
    double r;        /* radius */
    Bonus type;
    BonusObject *next_bonus; /* Points on the next bonus */
};

/* List of bonus */
typedef struct BonusList BonusList;
struct BonusList
{
    BonusObject *first_bonus; /* Points on the first bonus */
    BonusObject *last_bonus;  /* Points on the last bonus */
};

/*============================= Functions ===========================*/

/* Initializes a bonus */
BonusObject *initBonus(Coords3D coords, double radius, Bonus type);

/* Initializes an empty list of bonus */
BonusList *initBonusList();

/* Display the elements stored in the bonus list */
void printBonusList(BonusList list);

/* Removes all the bonus stored which are behind a given position */
void removeBonus(BonusList *list, double racket_pos);

/* Adds a bonus on a list */
void addBonus(BonusList *list, Coords3D coords, double radius, Bonus type);

/* Adds a random positioned bonus in the list */
void addRandomBonus(BonusList *list, double ball_pos, double limit);

/* Checks if a rectangle goes through a bonus */
int squareInBonus(BonusObject bonus, RectanglePoints rect, double section);

/*Frees the bonus list */
void freeBonus(BonusList *list);

/* Removes the first bonus of the list */
void removeFirst(BonusList *list);
