#include "../inc/draw_scene.h"

void drawBase() {
}

void drawArm() {
}

void drawPan() {
}


/*void drawSquare(double size){
    glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 1); // White color

        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);
        glVertex3f(10, 60, 0);
        glVertex3f(0, 60, 0);
    glEnd();
}*/

void drawRacket(double center_x, double center_y, double size) {
    
}

void drawCorridor(){
    glPushMatrix();

        glPushMatrix();

            glScaled(10, 1, 1);
            drawSquare(0.5, 0.5, 1);
            
            glTranslated(0, 0, 0.5);
            drawSquare(0.5, 0.5, 1);
        
        glPopMatrix();
        glPushMatrix();
        
            glRotated(90, 1, 0, 0);
            glScaled(10, 0.5, 1);
            glTranslated(0, .5, .5);
            drawSquare(0.3, 0.3, 1);

        glPopMatrix();


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
    glBegin(GL_LINES);

        glColor3f(1, 0, 0); /* red axis */
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glColor3f(0, 1, 0); /* green axis */
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        
        glColor3f(0, 0, 1); /* blue axis */
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);

    glEnd();

    drawCorridor();
}