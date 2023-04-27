#include "../inc/menu.h"


static const float GL_VIEW_SIZE = 6.;


#define AMOUNT_OF_PART 100

Coords mouseMenu;

static float aspectRatio = 1.0;

double ball_menu_pos = 0;
double wall_pos = 3;

Part particules[AMOUNT_OF_PART];


int play_flag = 0;
int quit_flag = 0;

int play_hover_flag = 0;
int quit_hover_flag = 0;


/**/
void initParts(){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		particules[i].coords.x = randRange(-5, 5);
		particules[i].coords.y = randRange(3, 10);
		particules[i].init_y = particules[i].coords.y;

		particules[i].r = randRange(0, 1);
		particules[i].g = randRange(0, 1);
		particules[i].b = randRange(0, 1);
	}
}




void animParts(){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		if(particules[i].coords.y <= -3){
			particules[i].coords.y = particules[i].init_y;
		}else{
			particules[i].coords.y -= 0.1;
		}
	}
}



/*===========  Draw part ================*/


void drawParts(){
	for(int i = 0; i < AMOUNT_OF_PART; i ++){
		glPushMatrix();
		glBegin(GL_QUADS);
			glScaled(0.1, 0.1, 0);
			glColor3d(particules[i].r, particules[i].g, particules[i].b);
			glVertex2d(particules[i].coords.x, particules[i].coords.y);
			glVertex2d(particules[i].coords.x + 0.2, particules[i].coords.y);
			glVertex2d(particules[i].coords.x + 0.2, particules[i].coords.y + 0.2);
			glVertex2d(particules[i].coords.x, particules[i].coords.y + 0.2);
		glEnd();
		glPopMatrix();
	}
}



void drawPlay(){
	glPushMatrix();
		glColor3d(0, 0, 0);
		glTranslated(-0.25, 1.25, 0);
		drawTriangle();
	glPopMatrix();
}




void drawCross(){

	glPushMatrix();
		glRotated(45, 0, 0, 1);
		glScaled(0.05, 0.7, 0);
		drawSquare(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
		glRotated(135, 0, 0, 1);
		glScaled(0.05, 0.7, 0);
		drawSquare(0, 0, 0);
	glPopMatrix();
}

void drawButtons(){
	glPushMatrix();
			glTranslated(0, 1.5, 0);
			glScaled(3, 1, 0);

			if(play_hover_flag){
				drawSquare(1, 1, 0.);
			}else{
				drawSquare(1, 1, 0.4);
			}
	glPopMatrix();

	glPushMatrix();
			glScaled(3, 1, 0);

			if(quit_hover_flag){
				drawSquare(1, 0.5, 0.3);
			}else{
				drawSquare(1, 0.7, 0.4);
			}
	glPopMatrix();

	drawPlay();
	drawCross();
}



void drawBallMenu(){
	glPushMatrix();
		glColor3d(1, .2, .2);
		glTranslated(-1.5 + ball_menu_pos, -1.5, 0);
		glScaled(0.3, 0.3, 0);
		drawCircle();
	glPopMatrix();
}


void drawMenuWall(){
	glPushMatrix();
		glTranslated(-1.1 + wall_pos, -1.3, 0);
		glScaled(0.1, 1, 0);
		drawSquare(0, 1, 0);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0, -1.9, 0);
		glScaled(1, 0.1, 0);
		glBegin(GL_QUADS);
			glColor3d(1, 1 ,1);
			glVertex2d(-1.5, 0);
			glVertex2d(2, 0);
			glVertex2d(2, 0.2);
			glVertex2d(-1.5, 0.2);
			//drawSquare(1, 1, 1);
		glEnd();
	glPopMatrix();
}



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




int clickInFirstButton(){
	if(-1.5 <= mouseMenu.x && mouseMenu.x <= 1.5){
		if(1 <= mouseMenu.y && mouseMenu.y <= 2){
			return 1;
		}
	}
	return 0;
}


int clickInSecondButton(){

	if(-1.5 <= mouseMenu.x && mouseMenu.x <= 1.5){
		if(-0.5 <= mouseMenu.y && mouseMenu.y <= 0.5){
			return 1;
		}
	}
	return 0;
}



void clickEvent(GLFWwindow * window, int code, int action, int other){

	double x,y;
	if(action == GLFW_PRESS){
		glfwGetCursorPos(window, &x, &y);
		screen_to_virtual(&x, &y);
		mouseMenu.x = x;
		mouseMenu.y = y;

		if(clickInFirstButton()){
			play_flag = 1;
		}else if (clickInSecondButton()){
			quit_flag = 1;
		}
	}
}



void movedCursorMenu(GLFWwindow *window, double x, double y)
{
	/*int hauteur, largeur;
	glfwGetWindowSize(window, &largeur, &hauteur);*/

	screen_to_virtual(&x, &y);

	mouseMenu.x = x; /* largeur;*/
	mouseMenu.y = y; /*/ hauteur;*/

	if(clickInFirstButton()){
		play_hover_flag = 1;
	}else{
		play_hover_flag = 0;
	}

	if(clickInSecondButton()){
		quit_hover_flag = 1;
	}else{
		quit_hover_flag = 0;
	}
}

int launchMenu(){

	srand(time(NULL)); /* Initializing the seed */

	initParts();

	mouseMenu.x = 0.;
	mouseMenu.y = 0.;

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
	glfwSetCursorPosCallback(window, movedCursorMenu);		/* Mouse moved */
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

		drawParts();
		
		drawButtons();

		drawBallMenu();

		drawMenuWall();

		

		if(play_flag){
			menu_response = 1;
			break;
		}else if(quit_flag) {
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


		if(ball_menu_pos >= wall_pos){
			ball_menu_pos = 0;
		}else{
			ball_menu_pos = (ball_menu_pos + .1);
		}

		animParts();
	}

	glfwTerminate();
	return menu_response;
}


