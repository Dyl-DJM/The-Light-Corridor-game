#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../inc/3D_tools.h"
#include "../inc/obstacle.h"

void move_ball(ObstacleList * obstacles);
void move_racket(ObstacleList * obstacles, RectanglePoints racket_form);