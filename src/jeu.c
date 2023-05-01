/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Game module concerns all the actions we can   =
=  see in the 3D scene.                              =
=  Graphical elements, events (click, moved cursor,  =
=  animted objects...)                               =
=													 =
======================================================
*/

#include "../inc/jeu.h"

/*============================== Variables ==================================*/

static float aspectRatio = 1.0;

/* Mouse coords */
Coords mouse;

/* Ball state */
MovingState ball_state = STOP; // The ball isn't moving at the beginning, it just follows the racket

/* Racket state */
MovingState racket_state = STOP; // The ball isn't moving at the beginning, it just follows the racket

/* Racket size */
double racket_size = 0.1;

/* Bonus */
Bonus bonus = NONE; /* At the beginning there is not any bonus */

/*============================== Functions ==================================*/

/* Resize of the window */
void onWindowResizedGame(GLFWwindow *window, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

/* Key events handling */
void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A: // All the keys
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_B:
			if (dist_zoom < 100.0f)
				dist_zoom *= 1.1;
			break;
		case GLFW_KEY_N:
			if (dist_zoom > 1.0f)
				dist_zoom *= 0.9;
			break;
		case GLFW_KEY_UP:
			if (phy > 2)
				phy -= 2;
			break;
		case GLFW_KEY_DOWN:
			if (phy <= 88.)
				phy += 2;
			break;
		case GLFW_KEY_LEFT:
			theta -= 5;
			break;
		case GLFW_KEY_RIGHT:
			theta += 5;
			break;
		default:
			printf("Unknown Command !\n");
		}
	}
}

/* Handles the movements of the cursor in the window */
void movedCursor(GLFWwindow *window, double x, double y)
{
	/* Update of the current position */
	mouse.x = x;
	mouse.y = y;
}

/* Handles the right and left mouse buttons */
void mouseButton(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) /* The ball is launched && the bonus is updated (GLUE mode) */
	{
		ball_state = MOVING;
		bonus = NONE;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) /* The racket moves and stop*/
	{
		if (ball_state == STOP)
		{ /* The ball hasn't been launched yet, wa cant move the racket */
			return;
		}
		racket_state = racket_state == MOVING ? STOP : MOVING;
	}
}

/* Launches the window with the 3D scene of the game */
int launchGame()
{
	/* GLFW initialisation */
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	/* Error handling */
	glfwSetErrorCallback(onError);

	/* Create a window */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate(); /* Error in the window creation */
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Callback events */
	glfwSetWindowSizeCallback(window, onWindowResizedGame); /* Window resize */
	glfwSetKeyCallback(window, onKey);						/* Key pressed */
	glfwSetCursorPosCallback(window, movedCursor);			/* Mouse moved */
	glfwSetMouseButtonCallback(window, mouseButton);		/* Mouse click event */

	onWindowResizedGame(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	/* Obstacles */
	ObstacleList *obstacles = initObstacleList();

	/* Bonus */
	BonusList *bonus_list = initBonusList();

	printBonusList(*bonus_list);

	/* Racket points */
	RectanglePoints racket_points = initRect(initCoords(0, 0), initCoords(0, 0));

	/* Ball coords */
	Coords3D ball = initCoords3D(0, 0, -2.0);

	/* Initialze the length of the corridor */
	initLengthCorridor();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && isAlive() && !isCorridorEnd(racket_pos))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2, 0.0, 0.0, 0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Scene rendering */
		drawFrame(mouse.x, mouse.y, racket_size, ball_state, *obstacles, &racket_points, &ball, bonus, *bonus_list);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;

		/* If to few time is spend vs our wanted FPS, we wait */
		while (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}

		/* Animate scenery */
		if (ball_state == MOVING)
		{
			if (move_ball(*obstacles, &ball, racket_points, &ball_state, bonus) == 2)
			{ /* The ball is behind the racket */
				removeLife();
			}
		}
		if (racket_state == MOVING && ball_state == MOVING)
		{ /* The racket is moving forward (doesn't matters the lateral moving)*/
			move_racket(obstacles, racket_points, &racket_state, &bonus, bonus_list);
		}

		/* Update Obstacles*/
		addRandomObstacle(obstacles, ball.z, endCorridor() - 3);
		addRandomBonus(bonus_list, ball.z, endCorridor() - 3);
		removeObs(obstacles, racket_pos);
		removeBonus(bonus_list, racket_pos);
	}

	/* Free the memory resources*/
	freeObstacles(obstacles);
	freeBonus(bonus_list);

	glfwTerminate();

	return isAlive() ? (isCorridorEnd(racket_pos) ? 1 : 0) : 2;
}