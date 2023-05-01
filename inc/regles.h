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

#pragma once

#include "../inc/types.h"

/* Checks if the player is still alive */
int isAlive();

/* Adds a single user life point */
void addLife();

/* Remove a single user life point */
void removeLife();

/* Retrieves the end information on the corridor axis */
double endCorridor();

/* Initialize the length of the corridor */
void initLengthCorridor();

/* Checks if the racket position given is out of the corridor */
int isCorridorEnd(double racket_pos);