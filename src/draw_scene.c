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

int nb_section = 7;

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
        glTranslated(4.95 + ball_pos, 0, .25);
        glScaled(0.05, 0.05, 0.05);

        drawSphere();
    glPopMatrix();
}

void drawRacket(double center_x, double center_y, double size)
{
    float racket_pos_y = 0.25;
    racket_pos_y -= (0.14 * (((-500) + center_y * 1.25) / 150));
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


/*Draw the ball in the scene*/
void drawBallWithRacket(double x, double y)
{
    float ball_pos_y = 0.25;
    ball_pos_y -= (0.14 * (((-500) + y * 1.25) / 150));
    if (ball_pos_y > 0.39)
    {
        ball_pos_y = 0.39;
    }
    if (ball_pos_y < 0.11)
    {
        ball_pos_y = 0.11;
    }

    float ball_pos_x = (0.4 * (((-500) + x) / 300));
    if (ball_pos_x > 0.39)
    {
        ball_pos_x = 0.39;
    }
    if (ball_pos_x < -0.39)
    {
        ball_pos_x = -0.39;
    }

    glPushMatrix();
        glTranslated(0, ball_pos_x, ball_pos_y - 0.25);
        drawColoredSphere();
    glPopMatrix();
   
}

void drawSection(int id)
{
    glPushMatrix();
    glTranslated(id + nb_section - 1, 0, 0);

    /* High and low rectangles */
    glPushMatrix();
    /*Low*/
    glScaled(1, 1, 1);
    if (id % 2 == 0)
    {
        drawSquare(0.5, 0.5, 1);
    }
    else
    {
        drawSquare(0.6, 0.6, 0.6);
    }
    /*High*/
    glTranslated(0, 0, 0.5);
    if (id % 2 == 0)
    {
        drawSquare(0.5, 0.5, 1);
    }
    else
    {
        drawSquare(0.6, 0.6, 0.6);
    }
    glPopMatrix();

    /* First side rectangle */
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.5, 1);
    glTranslated(0, .5, .5);
    if (id % 2 == 0)
    {
        drawSquare(0.3, 0.3, 1);
    }
    else
    {
        drawSquare(0.3, 0.3, 0.6);
    }
    glPopMatrix();

    /* Second side rectangle*/
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glScaled(1, 0.5, 1);
    glTranslated(0, 0.5, -.5);
    if (id % 2 == 0)
    {
        drawSquare(0.3, 0.3, 1);
    }
    else
    {
        drawSquare(0.3, 0.3, 0.6);
    }
    glPopMatrix();

    glPopMatrix();
}

/* Draw the whole corridor in the scene*/
void drawCorridor()
{
    for (int i = racket_pos; i > racket_pos - nb_section; i--)
    {
        drawSection(i);
    }
}

/*
Draw a wall at section depending on pos.
0 = Up, 1 = Down, 2 = Left, 3 = Right

*/
void drawWall(int section, int pos)
{
    float wall_pos_x = 0;
    float wall_pos_y = 0.25;
    float wall_width = 0;
    float wall_heigth = 0;
    switch (pos)
    {
    case 0:
        wall_heigth = 0.25;
        wall_width = 1;
        wall_pos_y = 0.375;
        break;
    case 1:
        wall_heigth = 0.25;
        wall_width = 1;
        wall_pos_y = 0.125;
        break;
    case 2:
        wall_heigth = 0.5;
        wall_width = 0.5;
        wall_pos_x = -0.25;
        wall_pos_y = 0.25;
        break;
    case 3:
        wall_heigth = 0.5;
        wall_width = 0.5;
        wall_pos_x = 0.25;
        wall_pos_y = 0.25;
        break;
    }
    glPushMatrix();
    glTranslated(4 - section + 0.5, wall_pos_x, wall_pos_y);
    glScaled(1, wall_width, wall_heigth);
    glRotated(90, 0, 1, 0);
    drawSquare(0, 1.0, 0);
    glPopMatrix();
}

/* Draw the x, y, z axis */
void drawFrame(double x, double y, double racket_size, MovingState ball_state)
{
    // drawOrigin();
    drawCorridor();

    // drawWall tests
    /*
    drawWall(3, 0);
    drawWall(6, 1);
    drawWall(9, 2);
    drawWall(12, 3);
    */

    /* Draw the racket */
    drawRacket(x, y, racket_size);

    if(ball_state == MOVING){
        drawBall();
    }else{
        drawBallWithRacket(x, y);
    }
    
}
