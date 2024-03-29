/*
======================================================
=  													 =
=    Created by Nicolas Atrax and Dylan DE JESUS	 =
=													 =
=													 =
=  The Draw Scene module is used to build the        =
=  graphical aspects of the 3D game.                 =
=  It's all about drawing there.                     =
=													 =
======================================================
*/

#include "../inc/draw_scene.h"

/*=================================== Variables ======================================*/
int nb_section = 7;

Coords thrownBall; // Coordinates of the ball at the moment we want it to be thrown

/*=================================== Functions ======================================*/

/* Draw the origin of the scene */
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

/* Draws the 2D racket */
void drawRacket(double center_x, double center_y, double size, RectanglePoints *racket_points, Bonus bonus)
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

    double centre_x = racket_pos_x + 0.5;
    double centre_y = racket_pos_y;

    Coords point1 = initCoords(centre_x - 0.1, centre_y - 0.1); // point bas gauche de la raquette
    Coords point2 = initCoords(centre_x + 0.1, centre_y + 0.1); // point haut droit de la raquette

    *racket_points = initRect(point1, point2);

    glPushMatrix();
    if (bonus == GLUE)
    {
        glColor3d(1, 0, 0); // Bonus coloured of the Glue
    }
    else
    {
        glColor3d(1, 1, 1);
    }
    glTranslated(5 + racket_pos, racket_pos_x, racket_pos_y); // (z, x, y)
    glRotated(90, 0, 1, 0);
    drawSquareForm(size);
    glPopMatrix();
}

/* Draws the 3D ball */
void drawBall(Coords3D *ball)
{

    glColor3d(.2, .2, 1.);
    glPushMatrix();
    glTranslated(4.95 + ball->z, ball->x - 0.5, ball->y);
    glScaled(0.05, 0.05, 0.05);
    if (racket_pos - 6 <= ball->z)
    {
        drawSphere();
    }
    glPopMatrix();
}

/* Draws the ball glued to the racket */
void drawBallWithRacket(double x, double y, Coords3D *ball)
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

    ball->x = ball_pos_x + 0.5;
    ball->y = ball_pos_y;

    glPushMatrix();
    drawBall(ball);
    glPopMatrix();
}

/* Draws a section of the corridor */
void drawSection(int id)
{
    glPushMatrix();
    glTranslated(id + nb_section - 0.5, 0, 0);

    /* High and low rectangles */
    glPushMatrix();
    /*Low*/
    glScaled(1, 1, 1);
    if (id % 2 == 0)
    {
        drawSquare(0.7, 0.7, 1);
    }
    else
    {
        drawSquare(0.8, 0.8, 0.8);
    }
    /*High*/
    glTranslated(0, 0, 0.5);
    if (id % 2 == 0)
    {
        drawSquare(0.7, 0.7, 1);
    }
    else
    {
        drawSquare(0.8, 0.8, 0.8);
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

/* Draw the whole corridor in the scene */
void drawCorridor()
{
    for (int i = racket_pos; i > racket_pos - nb_section; i--)
    {
        if (!isCorridorEnd(i))
        {
            drawSection(i);
        }
    }
}

/* Draws a single obstacle */
void drawObstacle(Obstacle *obstacle)
{
    int section = obstacle->section;
    float wall_width = obstacle->rect.a.x - obstacle->rect.b.x;
    float wall_heigth = obstacle->rect.a.y - obstacle->rect.c.y;

    float center_x = (obstacle->rect.b.x - obstacle->rect.a.x) / 2 + obstacle->rect.a.x;
    float center_y = (obstacle->rect.c.y - obstacle->rect.a.y) / 2 + obstacle->rect.a.y;
    float wall_pos_x = center_x - 0.5;
    float wall_pos_y = center_y;

    glPushMatrix();
    glTranslated(5 - section, wall_pos_x, wall_pos_y);
    glScaled(1, wall_width, wall_heigth);
    glRotated(90, 0, 1, 0);
    drawSquare(0, 1.0, 0);
    glPopMatrix();
}

/* Draws all the obstacles in the list */
void drawObstacles(ObstacleList list)
{
    Obstacle *obstacle = list.first_obs;

    while (obstacle != NULL)
    {
        if (obstacle->section > -racket_pos + 6)
        {
            break;
        };
        drawObstacle(obstacle);
        obstacle = obstacle->next_obs;
    }
}

/* Draws a bonus object */
void drawBonus(BonusObject bonus)
{
    glPushMatrix();
    glColor3d(1, 1, 0);
    glTranslated(4.95 + bonus.coords.z, bonus.coords.x - 0.5, bonus.coords.y); // Mettre les bonnes valeurs de coordonnées de bonus
    glScaled(0.05, 0.05, 0.05);
    drawSphere();
    glPopMatrix();
}

/* Draws all the bonus objects stored in the list */
void drawManyBonus(BonusList list)
{
    BonusObject *bonus = list.first_bonus;

    while (bonus != NULL)
    {
        if (bonus->coords.z < racket_pos - 5.5)
        {
            break;
        };
        drawBonus(*bonus);
        bonus = bonus->next_bonus;
    }
}

/* Sets the light system following the ball */
void setLightBall(Coords3D ball)
{
    GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {4.70 + ball.z, ball.x - 0.5, ball.y};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 2.0);
    glEnable(GL_LIGHT0);
}

/* Sets the light system behinf the racket */
void setLightCamera(Coords3D ball)
{
    GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {5.0 + racket_pos, 0.0, 0.25};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.3);
    if (racket_pos == ball.z)
    {
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 10);
    }
    else
    {
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 10 / -(ball.z - racket_pos));
    }
    glEnable(GL_LIGHT1);
}

/* Draws a single frame, the whole scene elements */
void drawFrame(double x, double y, double racket_size, MovingState ball_state, ObstacleList obstacles, RectanglePoints *racket_points, Coords3D *ball, Bonus bonus, BonusList bonus_list)
{
    if (isCorridorEnd(racket_pos - 2))
    {
        drawCorridor();
        drawRacket(x, y, racket_size, racket_points, bonus);
        return;
    }
    drawCorridor();

    /* Draw of the obstacles*/
    drawObstacles(obstacles);

    /* Draw of the bonus */
    drawManyBonus(bonus_list);

    /* Draw the racket */
    drawRacket(x, y, racket_size, racket_points, bonus);

    /* Configure Lighting */
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    setLightCamera(*ball);
    setLightBall(*ball);

    if (ball_state == MOVING) // The ball is moving in the corridor
    {
        drawBall(ball);
    }
    else
    {
        drawBallWithRacket(x, y, ball); // The ball follows the racket center
    }
}
