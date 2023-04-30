#pragma once

#include <time.h>
#include "../inc/types.h"

#define TYPES_BONUS_RANGE 2

typedef enum Bonus
{
    NONE,
    GLUE,
    LIFE
} Bonus;

typedef struct BonusObject BonusObject;
struct BonusObject
{
    Coords3D coords;
    double r; /* radius */
    Bonus type;
    BonusObject *next_bonus; /* Points on the next obstacle */
};

typedef struct BonusList BonusList;
struct BonusList
{
    BonusObject *first_bonus; /* Points on the first bonus */
    BonusObject *last_bonus;  /* Points on the last bonus */
};

BonusObject *initBonus(Coords3D coords, double radius, Bonus type);

BonusList *initBonusList();

void printBonusList(BonusList list);

void removeBonus(BonusList *list, double racket_pos);

void addBonus(BonusList *list, Coords3D coords, double radius, Bonus type);

void addRandomBonus(BonusList *list, double ball_pos, double limit);

int squareInBonus(BonusObject bonus, RectanglePoints rect, double section);

void freeBonus(BonusList *list);

void removeFirst(BonusList *list);
