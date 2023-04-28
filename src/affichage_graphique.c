#include "../inc/affichage_graphique.h"


/*============================== Variables ==================================*/

static const float GL_VIEW_SIZE = 6.;
static float aspectRatio = 1.0;

#define AMOUNT_OF_PART 100

/* Static array which stores all the particles of the display */
Part particules_graphic[AMOUNT_OF_PART];


/*============================== Functions ==================================*/

/* Initialize the particles of the array */
void initPartsGraphic(int win_mode){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		particules_graphic[i].coords.x = randRange(-5, 5);
		particules_graphic[i].coords.y = randRange(3, 10);
		particules_graphic[i].init_y = particules_graphic[i].coords.y;

        if(win_mode){
            particules_graphic[i].r = 0;
		    particules_graphic[i].g = 1;
		    particules_graphic[i].b = 0;
        }else{
            particules_graphic[i].r = 1;
		    particules_graphic[i].g = 0;
		    particules_graphic[i].b = 0;
        }
	}
}


/* Makes all the particles of the array move */
void animPartsGraphic(){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		if(particules_graphic[i].coords.y <= -3){
			particules_graphic[i].coords.y = particules_graphic[i].init_y;
		}else{
			particules_graphic[i].coords.y -= 0.1;
		}
	}
}


/* Resize the window in 2D display */
void onWindowResizedGraphic(GLFWwindow* window, int width, int height)
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


/* Draw all the particles */
void drawPartsGraphic(){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		glPushMatrix();
		glBegin(GL_QUADS);
			glScaled(0.1, 0.1, 0);
			glColor3d(particules_graphic[i].r, particules_graphic[i].g, particules_graphic[i].b);
			glVertex2d(particules_graphic[i].coords.x, particules_graphic[i].coords.y);
			glVertex2d(particules_graphic[i].coords.x + 0.2, particules_graphic[i].coords.y);
			glVertex2d(particules_graphic[i].coords.x + 0.2, particules_graphic[i].coords.y + 0.2);
			glVertex2d(particules_graphic[i].coords.x, particules_graphic[i].coords.y + 0.2);
		glEnd();
		glPopMatrix();
	}
}


/* Escaping handler */
void escape(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_A:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		default:{} /* Nothing */
		}
	}
}


/* Launches the 2D window */
int window(int win_or_lose){

	/* Initialize the array */
	initPartsGraphic(win_or_lose);

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

	glfwSetWindowSizeCallback(window,onWindowResizedGraphic);
	onWindowResizedGraphic(window,WINDOW_WIDTH,WINDOW_HEIGHT);
    glfwSetKeyCallback(window, escape); /* Escape key */

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

		/* Draw the main frame */
		drawPartsGraphic();

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

		/* Animation scenery */
		animPartsGraphic();
	}

	glfwTerminate();
    return 0;
}


/* Launches an end window with a win display */
void launchWinWindow(){
    window(1);
}

/* Launches an end window with a loose display */
void launchLooseWindow(){
    window(0);
}