#include <stdio.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/3D_tools.h"
#include "../inc/draw_scene.h"
#include "../inc/types.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Mouse coords */
Coords mouse;

/* Racket size */
double racket_size = 0.15;

/* Error handling function */
void onError(int error, const char *description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GLFW_KEY_B:
			if (dist_zoom < 100.0f)
				dist_zoom *= 1.1;
			printf("Zoom is %f\n", dist_zoom);
			break;
		case GLFW_KEY_N:
			if (dist_zoom > 1.0f)
				dist_zoom *= 0.9;
			printf("Zoom is %f\n", dist_zoom);
			break;
		case GLFW_KEY_UP:
			if (phy > 2)
				phy -= 2;
			printf("Phy %f\n", phy);
			break;
		case GLFW_KEY_DOWN:
			if (phy <= 88.)
				phy += 2;
			printf("Phy %f\n", phy);
			break;
		case GLFW_KEY_LEFT:
			theta -= 5;
			break;
		case GLFW_KEY_RIGHT:
			theta += 5;
			break;
		default:
			fprintf(stdout, "Touche non gérée (%d)\n", key);
		}
	}
}

/* The mouse now has new coords*/
void movedCursor(GLFWwindow *window, double x, double y)
{
	/*int hauteur, largeur;

	glfwGetWindowSize(window, &largeur, &hauteur);*/

	mouse.x = x; /* largeur;*/
	mouse.y = y; /*/ hauteur;*/

	printf("Mouse coords : %f - %f\n", mouse.x, mouse.y);
}

int main(int argc, char **argv)
{
	/* GLFW initialisation */
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Callback events */
	glfwSetWindowSizeCallback(window, onWindowResized); /* Window resize */
	glfwSetKeyCallback(window, onKey);					/* Key pressed */
	glfwSetCursorPosCallback(window, movedCursor);		/* Mouse moved */

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2, 0.0, 0.0, 0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		glPushMatrix();
		glTranslatef(0.0, 0.0, -0.01);
		glScalef(10.0, 10.0, 1.0);
		glColor3f(0.0, 0.0, 0.1);
		drawSquare(0, 0, 0);
		glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();

		/* Scene rendering */
		drawFrame();

		/* Draw the racket */
		drawRacket(mouse.x, mouse.y, racket_size);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}

		/* Animate scenery */
		move_ball();
		move_racket();
	}

	glfwTerminate();
	return 0;
}