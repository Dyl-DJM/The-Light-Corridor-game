/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Draw Scene module is used to build the        =
=  graphical aspects of the 3D game.                 =
=  It's all about drawing there.                     =
=													 =
======================================================
*/

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

/* Draw the origin of the scene */
void drawOrigin();

/* Draws the 2D racket */
void drawRacket(double center_x, double center_y, double size, RectanglePoints *racket_points, Bonus bonus);

/* Draws the 3D ball */
void drawBall(Coords3D *ball);

/* Draws the ball glued to the racket */
void drawBallWithRacket(double x, double y, Coords3D *ball);

/* Draws a section of the corridor */
void drawSection(int id);

/* Draw the whole corridor in the scene */
void drawCorridor();

/* Draws a single obstacle */
void drawObstacle(Obstacle *obstacle);

/* Draws all the obstacles in the list */
void drawObstacles(ObstacleList list);

/* Draws a bonus object */
void drawBonus(BonusObject bonus);

/* Draws all the bonus objects stored in the list */
void drawManyBonus(BonusList list);

/* Sets the light system following the ball */
void setLightBall(Coords3D ball);

/* Sets the light system behinf the racket */
void setLightCamera();

/* Draws a single frame, the whole scene elements */
void drawFrame(double x, double y, double racket_size, MovingState ball_state, ObstacleList obstacles, RectanglePoints *racket_points, Coords3D *ball, Bonus bonus, BonusList bonus_list);