#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "3D_tools.h"
#include "animation.h"
#include "types.h"
#include "obstacle.h"
#include "regles.h"
#include "bonus.h"



void drawFrame(double x, double y, double racket_size, MovingState ball_state, ObstacleList obstacles, RectanglePoints *racket_points, Coords3D *ball, Bonus bonus);



