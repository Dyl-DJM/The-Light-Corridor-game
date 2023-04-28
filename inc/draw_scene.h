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

void drawOrigin();

void drawFrame(double x, double y, double racket_size, MovingState ball_state, ObstacleList obstacles, RectanglePoints *racket_points, Coords3D *ball);

void drawRacket(double center_x, double center_y, double size, RectanglePoints *racket_points);

void drawBall(Coords3D *ball);

void drawBallWithRacket(double x, double y, Coords3D *ball);

void drawSection(int id);

void drawCorridor();

void drawObstacle(Obstacle *obstacle);

void drawObstacles(ObstacleList list);