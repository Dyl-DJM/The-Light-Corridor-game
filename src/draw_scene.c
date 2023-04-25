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

void drawOrigin()
{
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

void drawColoredSphere()
{
    glColor3d(1, .2, .2);
    glPushMatrix();
    glTranslated(5 + ball_pos, 0, .25);
    glScaled(0.05, 0.05, 0.05);

    drawSphere();
    glPopMatrix();
}

void drawRacket(double center_x, double center_y, double size)
{
    float racket_pos_y = 0.25;
    racket_pos_y -= (0.14 * (((-500) + center_y) / 150));
    if (racket_pos_y > 0.39)
    {
        racket_pos_y = 0.39;
    }
    if (racket_pos_y < 0.11)
    {
        racket_pos_y = 0.11;
    }

    float racket_pos_x = (0.4 * (((-500) + center_x) / 300));
    if (racket_pos_x > 0.39)
    {
        racket_pos_x = 0.39;
    }
    if (racket_pos_x < -0.39)
    {
        racket_pos_x = -0.39;
    }

    glPushMatrix();
    glColor3d(1, 1, 1);
    glTranslated(5 + racket_pos, racket_pos_x, racket_pos_y);
    glRotated(90, 0, 1, 0);
    drawSquareForm(size);
    glPopMatrix();
}

/*Draw the ball in the scene*/
void drawBall()
{
    drawColoredSphere();
}

/* Draw the whole corridor in the scene*/
void drawCorridor()
{
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
void drawFrame()
{
    // drawOrigin();
    drawCorridor();
    drawBall();
}
