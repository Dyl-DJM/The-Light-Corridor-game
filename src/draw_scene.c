#include "../inc/draw_scene.h"


/*void drawSquare(double size){
    glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 1); // White color

        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);
        glVertex3f(10, 60, 0);
        glVertex3f(0, 60, 0);
    glEnd();
}*/


void drawOrigin(){
    glBegin(GL_LINES);

        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);

    glEnd();
}


void drawColoredSphere(){
    glColor3d(1, .2, .2);
    glPushMatrix();
        glTranslated(5, 0, .25);
        glScaled(0.1, 0.1, 0.1);
        
        drawSphere();
    glPopMatrix();
}

void drawRacket(double center_x, double center_y, double size) {
    glPushMatrix();
        glColor3d(1, 1, 1);
        glRotated(90, 0, 1, 0);
        glTranslated(0, 0, 5);
        drawSquareForm(size);
    glPopMatrix();
}

/*Draw the ball in the scene*/
void drawBall(){
    drawColoredSphere();
}


/* Draw the whole corridor in the scene*/
void drawCorridor(){
    glPushMatrix();

        /* High and low rectangles */
        glPushMatrix();
            /*Low*/
            glScaled(10, 1, 1);
            drawSquare(0.5, 0.5, 1);
            /*High*/
            glTranslated(0, 0, 0.5);
            drawSquare(0.5, 0.5, 1);
        
        glPopMatrix();

        /* First side rectangle */
        glPushMatrix();
            glRotated(90, 1, 0, 0);
            glScaled(10, 0.5, 1);
            glTranslated(0, .5, .5);
            drawSquare(0.3, 0.3, 1);
        glPopMatrix();

        /* Second side rectangle*/
        glPushMatrix();
            glRotated(90, 1, 0, 0);
            glScaled(10, 0.5, 1);
            glTranslated(0, 0.5, -.5);
            drawSquare(0.3, 0.3, 1);
        glPopMatrix();
    glPopMatrix();
}

/* Draw the x, y, z axis */
void drawFrame(){
    drawOrigin();
    drawCorridor();
    drawBall();
}












