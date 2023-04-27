#include "../inc/jeu.h"

static float aspectRatio = 1.0;

/* Mouse coords */
Coords mouse;

/* Ball state */
MovingState ball_state = STOP; // The ball isn't moving at the beginning, it just follows the racket

/* Racket state */
MovingState racket_state = STOP; // The ball isn't moving at the beginning, it just follows the racket

/* Racket size */
double racket_size = 0.1;

void onWindowResizedGame(GLFWwindow *window, int width, int height)
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

	// printf("Mouse coords : %f - %f\n", mouse.x, mouse.y);
}

/* Handles the right and left mouse buttons */
void mouseButton(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		ball_state = MOVING;
		racket_state = MOVING;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		racket_state = racket_state == MOVING ? STOP : MOVING; // to debug
	}
}

int launchGame()
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
	glfwSetWindowSizeCallback(window, onWindowResizedGame); /* Window resize */
	glfwSetKeyCallback(window, onKey);						/* Key pressed */
	glfwSetCursorPosCallback(window, movedCursor);			/* Mouse moved */
	glfwSetMouseButtonCallback(window, mouseButton);		/* Mouse click event */

	onWindowResizedGame(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	/* Obstacles */
	ObstacleList *obstacles = initObstacleList();

	/* Racket points */
	RectanglePoints racket_points = initRect(initCoords(0, 0), initCoords(0, 0));

	/* Ball coords*/
	Coords3D ball = initCoords3D(0, 0, -2.0);

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
		drawFrame(mouse.x, mouse.y, racket_size, ball_state, *obstacles, &racket_points, &ball);

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
		if (ball_state == MOVING)
		{
			move_ball(*obstacles, &ball, racket_points);
		}
		if (racket_state == MOVING && ball_state == MOVING)
		{ /* The racket is moving forward (doesn't matters the lateral moving)*/
			move_racket(obstacles, racket_points);
		}

		/* Update Obstacles*/
		addRandomObstacle(obstacles, ball.z);
		removeObs(obstacles, racket_pos);
	}

	glfwTerminate();

	return 0;
}