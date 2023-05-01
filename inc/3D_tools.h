/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The 3D tools module is a box with some useful     =
=  tools to make primitive shapes in 3D scene        =
=													 =
======================================================
*/

#pragma once

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*======================== Variables =========================*/

#define NB_SEG_CIRCLE 64

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;     // Angle between x axis and viewpoint
extern float phy;       // Angle between z axis and viewpoint
extern float dist_zoom; // Distance between origin and viewpoint
extern float racket_pos;

/*======================== Functions =========================*/

/* Sets the camera position in the scene */
void setCamera();

/* Draws a coloured square */
void drawSquare(double r, double g, double b);

/* Draw a circle in a 2D scene */
void drawCircle();

/* Draws a cone in the 3D scene */
void drawCone();

/* Draws a sphere in the 3D scene */
void drawSphere();

/* Draws a triangle in the 2D scene */
void drawTriangle();

/* Small tools */
float toRad(float deg);

/* Draws a square */
void drawSquareForm(double size);