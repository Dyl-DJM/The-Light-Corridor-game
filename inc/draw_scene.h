#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "3D_tools.h"
#include "animation.h"
#include "types.h"

void drawOrigin();

void drawFrame(double x, double y, double racket_size, MovingState ball_state);

void drawRacket(double center_x, double center_y, double size);

void drawBall();

void drawSection(int id);

void drawCorridor();

void drawWall(int section, int pos);
