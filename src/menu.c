#include "../inc/menu.h"


/*MENU ELEMENTS*/

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 6.;


Coords mouseMenu;

static float aspectRatio = 1.0;



void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( aspectRatio > 1)
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


void screen_to_virtual(double * a, double * b){
	*a = GL_VIEW_SIZE * aspectRatio * (*a) / WINDOW_WIDTH - (GL_VIEW_SIZE * aspectRatio / 2);
	*b = -(GL_VIEW_SIZE * (*b) / WINDOW_HEIGHT - (GL_VIEW_SIZE / 2));
}

void clickEvent(GLFWwindow * window, int code, int action, int other){

	double x,y;
	if(action == GLFW_PRESS){
		glfwGetCursorPos(window, &x, &y);
		screen_to_virtual(&x, &y);
		mouseMenu.x = x;
		mouseMenu.y = y;
	}
}

int launchMenu(){

	//current.x = 0;
	//current.y = 0;


	mouseMenu.x = 0.;

	int menu_response = 0;

	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

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

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetMouseButtonCallback(window, clickEvent);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

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

		/*glTranslatef(1, 2, 0.);
		drawCircle();

		// SQUARE RED
		glLoadIdentity();
		glRotatef(45., 0., 0., 1.);
		glTranslatef(1., 0., 0.);

		drawSquare(1, 0, 0);


		// Reload of the initial 
		glLoadIdentity();
		// SQUARE PURPLE

		glTranslatef(1., 0., 0.);
		glRotatef(45., 1., 0., 1.);
		
		drawSquare(0, 0, 1);*/

		//glTranslatef(vertex.x - current.x, vertex.y - current.y, 0);
		drawSquare(0, 1, 0);

		if(mouseMenu.x != 0){
			menu_response = 1;
			break;
		}else if(menu_response) {
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
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

	glfwTerminate();
	return menu_response;
}


