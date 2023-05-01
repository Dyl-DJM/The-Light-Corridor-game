/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Rules module is used to represents the whole  =
=  game mechanic and rules, the amount of life       =
=  points allowed for the user, the length of the	 =
=  corridor...  									 =
=													 =
======================================================
*/

#include "../inc/regles.h"

/*======================== Variables ===========================*/

int life_points = 5; /* amount of initial life points */
double end_corridor;

/*======================== Functions ===========================*/

/* Adds a single user life point */
void addLife()
{
    life_points++;
}

/* Initialize the length of the corridor */
void initLengthCorridor()
{
    end_corridor = randRange(40, 200);
}

/* Remove a single user life point */
void removeLife()
{
    life_points--;
}

/* Checks if the player is still alive */
int isAlive()
{
    return life_points > 0;
}

/* Retrieves the end information on the corridor axis */
double endCorridor()
{
    return end_corridor;
}

/* Checks if the racket position given is out of the corridor */
int isCorridorEnd(double racket_pos)
{
    return -racket_pos >= end_corridor;
}
