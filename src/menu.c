/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Menu module is used to represent the game     =
=  menu display at the beginning for this project.   =
=  This is a 2D scene with buttons and animated      =
=  objects                                      	 =
=													 =
======================================================
*/

#include "../inc/menu.h"

/*============================ Parameters ==============================*/

#define AMOUNT_OF_PART 100

static const float GL_VIEW_SIZE = 6.;
static float aspectRatio = 1.0;

double ball_menu_pos = 0;
double wall_pos = 3;

Coords mouseMenu; // Mouse 2D coordinates
Part particules[AMOUNT_OF_PART];

/* Display type flags */
int play_flag = 0;
int quit_flag = 0;

int play_hover_flag = 0;
int quit_hover_flag = 0;

/*============================== Functions ================================*/

/* Initializes the particles array */
void initParts()
{
	for (int i = 0; i < AMOUNT_OF_PART; i++)
	{
		particules[i].coords.x = randRange(-5, 5);
		particules[i].coords.y = randRange(3, 10);
		particules[i].init_y = particules[i].coords.y;

		particules[i].r = randRange(0, 1);
		particules[i].g = randRange(0, 1);
		particules[i].b = randRange(0, 1);
	}
}

/* - - - - Particles animation - - - - */

/* Animates all the particles*/
void animParts()
{
	for (int i = 0; i < AMOUNT_OF_PART; i++)
	{
		if (particules[i].coords.y <= -3)
		{
			particules[i].coords.y = particules[i].init_y;
		}
		else
		{
			particules[i].coords.y -= 0.1;
		}
	}
}

/* - - - - Particles drawing - - - - */

/* Draw all the particles */
void drawParts()
{
	for (int i = 0; i < AMOUNT_OF_PART; i++)
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		glScaled(0.1, 0.1, 0); // A particle is a small colored square
		glColor3d(particules[i].r, particules[i].g, particules[i].b);
		glVertex2d(particules[i].coords.x, particules[i].coords.y);
		glVertex2d(particules[i].coords.x + 0.2, particules[i].coords.y);
		glVertex2d(particules[i].coords.x + 0.2, particules[i].coords.y + 0.2);
		glVertex2d(particules[i].coords.x, particules[i].coords.y + 0.2);
		glEnd();
		glPopMatrix();
	}
}

/* Draws the play logo (triangle) */
void drawPlay()
{
	glPushMatrix();
	glColor3d(0, 0, 0);
	glTranslated(-0.25, 1.25, 0);
	drawTriangle();
	glPopMatrix();
}

/* Draws the cross logo */
void drawCross()
{
	/* First line */
	glPushMatrix();
	glRotated(45, 0, 0, 1);
	glScaled(0.05, 0.7, 0);
	drawSquare(0, 0, 0);
	glPopMatrix();

	/* Second line */
	glPushMatrix();
	glRotated(135, 0, 0, 1);
	glScaled(0.05, 0.7, 0);
	drawSquare(0, 0, 0);
	glPopMatrix();
}

/* Draw the two buttons in the menu */
void drawButtons()
{
	glPushMatrix();
	glTranslated(0, 1.5, 0);
	glScaled(3, 1, 0);

	if (play_hover_flag) // The mouse is on the play button
	{
		drawSquare(1, 1, 0.);
	}
	else
	{
		drawSquare(1, 1, 0.4);
	}
	glPopMatrix();

	glPushMatrix();
	glScaled(3, 1, 0);

	if (quit_hover_flag) // The mouse is on the quit button
	{
		drawSquare(1, 0.5, 0.3);
	}
	else
	{
		drawSquare(1, 0.7, 0.4);
	}
	glPopMatrix();

	/* logos in the buttons */
	drawPlay();
	drawCross();
}

/* Draws the ball */
void drawBallMenu()
{
	glPushMatrix();
	glColor3d(1, .2, .2);
	glTranslated(-1.5 + ball_menu_pos, -1.5, 0);
	glScaled(0.3, 0.3, 0);
	drawCircle();
	glPopMatrix();
}

/* Draws the obstacle of the menu */
void drawMenuWall()
{
	glPushMatrix();
	glTranslated(-1.1 + wall_pos, -1.3, 0);
	glScaled(0.1, 1, 0);
	drawSquare(0, 1, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -1.9, 0);
	glScaled(1, 0.1, 0);
	glBegin(GL_QUADS);
	glColor3d(1, 1, 1);
	glVertex2d(-1.5, 0);
	glVertex2d(2, 0);
	glVertex2d(2, 0.2);
	glVertex2d(-1.5, 0.2);
	glEnd();
	glPopMatrix();
}

/* Rezizes the 2D window */
void onWindowResized(GLFWwindow *window, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (aspectRatio > 1)
	{
		gluOrtho2D(
			-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
			-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
			-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
			-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
	glMatrixMode(GL_MODELVIEW);
}

/* Makes the conversion between the window and the scene 2D coordinates */
void screen_to_virtual(double *a, double *b)
{
	*a = GL_VIEW_SIZE * aspectRatio * (*a) / WINDOW_WIDTH - (GL_VIEW_SIZE * aspectRatio / 2);
	*b = -(GL_VIEW_SIZE * (*b) / WINDOW_HEIGHT - (GL_VIEW_SIZE / 2));
}

/* Checks if the click was on the play button area */
int clickInFirstButton()
{
	if (-1.5 <= mouseMenu.x && mouseMenu.x <= 1.5)
	{
		if (1 <= mouseMenu.y && mouseMenu.y <= 2)
		{
			return 1;
		}
	}
	return 0;
}

/* Checks if the click was on the quit button area */
int clickInSecondButton()
{

	if (-1.5 <= mouseMenu.x && mouseMenu.x <= 1.5)
	{
		if (-0.5 <= mouseMenu.y && mouseMenu.y <= 0.5)
		{
			return 1;
		}
	}
	return 0;
}

/* Handles the mouse click events */
void clickEvent(GLFWwindow *window, int code, int action, int other)
{
	double x, y;
	if (action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &x, &y);
		screen_to_virtual(&x, &y); // Conversion with the scene
		mouseMenu.x = x;
		mouseMenu.y = y;

		if (clickInFirstButton())
		{
			play_flag = 1; // The player wants to play a game
		}
		else if (clickInSecondButton())
		{
			quit_flag = 1; // The player wants to quit
		}
	}
}

/* Handles the cursor movements on the window */
void movedCursorMenu(GLFWwindow *window, double x, double y)
{
	screen_to_virtual(&x, &y);
	mouseMenu.x = x;
	mouseMenu.y = y;

	if (clickInFirstButton()) // The cursor was moved to the play button area
	{
		play_hover_flag = 1;
	}
	else
	{
		play_hover_flag = 0;
	}

	if (clickInSecondButton()) // The cursor was moved to the exit button area
	{
		quit_hover_flag = 1;
	}
	else
	{
		quit_hover_flag = 0;
	}
}

/* Launches the window with the 2D display menu */
int launchMenu()
{
	srand(time(NULL)); /* Initializing the seed */

	initParts(); // Initializes all the particles of the menu

	/* Initializing the values to avoid some bad behaviours */
	mouseMenu.x = 0.;
	mouseMenu.y = 0.;

	int menu_response = 0;

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

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetCursorPosCallback(window, movedCursorMenu); /* Mouse moved */
	glfwSetMouseButtonCallback(window, clickEvent);	   /* Mouse click events */

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* Draw part of the menu */
		drawParts();
		drawButtons();
		drawBallMenu();
		drawMenuWall();

		if (play_flag)
		{
			menu_response = 1;
			break;
		}
		else if (quit_flag)
		{
			menu_response = 2;
			break;
		}

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

		/* Animation of the ball */

		// Ball animation
		if (ball_menu_pos >= wall_pos)
		{
			ball_menu_pos = 0;
		}
		else
		{
			ball_menu_pos = (ball_menu_pos + .1);
		}

		// Particles animation
		animParts();
	}

	glfwTerminate();
	return menu_response;
}
