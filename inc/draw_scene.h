#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../inc/3D_tools.h"

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawRacket(double center_x, double center_y, double size);


void drawCorridor();
