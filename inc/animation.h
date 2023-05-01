/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Animation module gathers all the mechanic     =
=  of objects which can move.                        =
=  Its is related to the ball bounces, racket moves. =
=													 =
======================================================
*/

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
#include "../inc/regles.h"

/* Ball touching a wall of the corridor */
int ballTouchWall(Coords3D ball);

/* Ball touching an obstacle */
int ballTouchObstacle(Obstacle obstacle, Coords3D ball);

/* The ball meets the racket */
int ballTouchRacket(RectanglePoints racket_points, Coords3D *ball, MovingState *ball_state);

/* The ball changes its direction by touching the racket */
void ballBounceOnRacket(Coords3D ball, RectanglePoints racket_points);

/* The ball is stopped */
void setStoppedBall(Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state);

/* Computes all the possible ways of colision in the scene */
int collision(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state);

/* Makes the ball move */
int move_ball(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state, Bonus bonus);

/* Makes the racket move */
void move_racket(ObstacleList *obstacles, RectanglePoints racket_form, MovingState *racket_state, Bonus *bonus, BonusList *bonus_list);