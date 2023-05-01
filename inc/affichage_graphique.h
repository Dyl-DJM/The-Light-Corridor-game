/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Graphical display module is used to call one  =
=  of the two possible windows which announces the   =
=  result of the game for the user in a 2D scene.    =
=													 =
======================================================
*/

#pragma once

#include "../inc/types.h"

#include "../inc/3D_tools.h"
#include "../inc/window.h"

#include <time.h>

/* Launches an end window with a win display */
void launchWinWindow();

/* Launches an end window with a loose display */
void launchLooseWindow();