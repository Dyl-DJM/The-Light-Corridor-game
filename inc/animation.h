#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>

#include "../inc/3D_tools.h"
#include "../inc/obstacle.h"
#include "../inc/bonus.h"

int ballTouchWall(Coords3D ball);
int ballTouchObstacle(Obstacle obstacle, Coords3D ball);
int ballTouchRacket(RectanglePoints racket_points, Coords3D *ball, MovingState *ball_state);
void ballBounceOnRacket(Coords3D ball, RectanglePoints racket_points);
void setStoppedBall(Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state);
int collision(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state);
int move_ball(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state, Bonus bonus);
void move_racket(ObstacleList *obstacles, RectanglePoints racket_form, MovingState * racket_state, Bonus * bonus);