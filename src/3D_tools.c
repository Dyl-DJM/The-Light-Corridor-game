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

#include "../inc/3D_tools.h"

/*============================== Variables ===============================*/

/* Camera parameters and functions */
float theta = 0;		// Angle between x axis and viewpoint
float phy = 88.0f;		// Angle between z axis and viewpoint
float dist_zoom = 6.0f; // Distance between origin and viewpoint

/* Objects position*/
float racket_pos = -2.0f; // Position of the racket

/*============================== Functions ===============================*/

/* Sets the camera position in the scene */
void setCamera()
{
	gluLookAt(dist_zoom * cos(toRad(theta)) * sin(toRad(phy)) + racket_pos,
			  dist_zoom * sin(toRad(theta)) * sin(toRad(phy)),
			  dist_zoom * cos(toRad(phy)),
			  racket_pos, 0.0, 1.0,
			  0.0, 0.0, 1.0);
}

/* Convert degree to radians */
float toRad(float deg)
{
	return deg * M_PI / 180.0f;
}

/* Draws a coloured square */
void drawSquare(double r, double g, double b)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(r, g, b);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}

/* Draws a square */
void drawSquareForm(double size)
{
	double half_size = size;
	glBegin(GL_LINE_LOOP);
	glVertex3d(-half_size, -half_size, 0.0);
	glVertex3d(half_size, -half_size, 0.0);
	glVertex3d(half_size, half_size, 0.0);
	glVertex3d(-half_size, half_size, 0.0);
	glEnd();
}

/* Draw a circle in a 2D scene */
void drawCircle()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
	for (int i = 0; i <= NB_SEG_CIRCLE; i++)
	{
		glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
	}
	glEnd();
}

/* Draws a cone in the 3D scene */
void drawCone()
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 1.0);
	float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
	for (int i = 0; i <= NB_SEG_CIRCLE; i++)
	{
		glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
	}
	glEnd();
}

/* Draws a sphere in the 3D scene */
void drawSphere()
{
	gluSphere(gluNewQuadric(), 1.0, NB_SEG_CIRCLE, NB_SEG_CIRCLE);
}

/* Draws a triangle in the 2D scene */
void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(0.5, 0.25);
	glVertex2d(0, 0.5);
	glEnd();
}