#include "../inc/animation.h"

double ball_speed = 0.1;
double racket_speed = 0.05;
double ball_trans_x = 0;
double ball_trans_y = 0;
double ball_trans_z = -0.1;

int ballTouchWall(Coords3D ball)
{
    if (ball.x + ball_trans_x <= 0.05)
    {
        ball_trans_x *= -1;
        return 1;
    }
    if (ball.x + ball_trans_x >= 0.95)
    {
        ball_trans_x *= -1;
        return 1;
    }
    if (ball.y + ball_trans_y <= 0.05)
    {
        ball_trans_y *= -1;
        return 1;
    }
    if (ball.y + ball_trans_y >= 0.45)
    {
        ball_trans_y *= -1;
        return 1;
    }
    return 0;
}

int ballTouchObstacle(Obstacle obstacle, Coords3D ball)
{
    if ((-ball.z <= obstacle.section && obstacle.section <= -ball.z - ball_trans_z) || (-ball.z >= obstacle.section && obstacle.section >= -ball.z - ball_trans_z))
    {
        if ((ball.x + ball_trans_x >= obstacle.rect.a.x - 0.049 && ball.x + ball_trans_x <= obstacle.rect.d.x + 0.049))
        {
            if (ball.y + ball_trans_y >= obstacle.rect.a.y - 0.049 && ball.y + ball_trans_y <= obstacle.rect.d.y + 0.049)
            {
                ball_trans_z *= -1;
                return 1;
            }
        }

        if (ball.x + ball_trans_x <= 0.05 || ball.x + ball_trans_x >= 0.95)
        {
            ball_trans_z *= -1;
            return 0;
        }

        if (ball.y + ball_trans_y <= 0.05 || ball.y + ball_trans_y >= 0.45)
        {
            ball_trans_z *= -1;
            return 0;
        }
    }
    return 0;
}

int ballTouchRacket(RectanglePoints racket_points, Coords3D *ball, MovingState *ball_state)
{
    if (ball->z <= racket_pos && ball->z >= racket_pos - racket_speed - ball_trans_z && ball_trans_z > 0)
    {
        if (ball->x + ball_trans_x >= racket_points.a.x - 0.049 && ball->x + ball_trans_x <= racket_points.d.x + 0.049)
        {
            if (ball->y + ball_trans_y >= racket_points.a.y - 0.049 && ball->y + ball_trans_y <= racket_points.d.y + 0.049)
            {
                ballBounceOnRacket(*ball, racket_points);
                return 1;
            }
            else
            {
                setStoppedBall(ball, racket_points, ball_state);
                return 2;
            }
        }
        else
        {
            setStoppedBall(ball, racket_points, ball_state);
            return 2;
        }
    }
    if (ball->z > racket_pos && ball_trans_z > 0)
    {
        setStoppedBall(ball, racket_points, ball_state);
        return 2;
    }
    return 0;
}

void ballBounceOnRacket(Coords3D ball, RectanglePoints racket_points)
{
    double center_racket_x = racket_points.d.x - ((racket_points.d.x - racket_points.a.x) / 2);
    double center_racket_y = racket_points.d.y - ((racket_points.d.y - racket_points.a.y) / 2);
    double distance_center_x = ball.x - center_racket_x;
    double distance_center_y = ball.y - center_racket_y;

    ball_trans_x *= -1;
    ball_trans_y *= -1;
    ball_trans_x += ball_speed * distance_center_x;
    ball_trans_y += ball_speed * distance_center_y;

    ball_trans_z *= -1;
}

void setStoppedBall(Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state)
{
    double center_racket_x = racket_points.d.x - ((racket_points.d.x - racket_points.a.x) / 2);
    double center_racket_y = racket_points.d.y - ((racket_points.d.y - racket_points.a.y) / 2);
    ball->x = center_racket_x;
    ball->y = center_racket_y;
    ball->z = racket_pos;
    ball_trans_x = 0;
    ball_trans_y = 0;
    ball_trans_z = -ball_speed;
    *ball_state = STOP;
    double startTime = glfwGetTime();
    double elapsedTime = glfwGetTime() - startTime;
    while (elapsedTime < 1)
    {
        glfwWaitEventsTimeout(1 - elapsedTime);
        elapsedTime = glfwGetTime() - startTime;
    }
}

int collision(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state)
{
    int value = 0;

    if ((value = ballTouchRacket(racket_points, ball, ball_state)))
    {
        return value;
    }

    if (ballTouchWall(*ball))
    {
        return 0;
    }

    Obstacle *obstacle = obstacles.first_obs;

    while (obstacle != NULL)
    {
        // printf("Ball = %f Section = %f\n", ball.z, obstacle->section);
        if (ballTouchObstacle(*obstacle, *ball))
        {
            break;
        }
        obstacle = obstacle->next_obs;
    }

    return 0;
}

int move_ball(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points, MovingState *ball_state, Bonus bonus)
{

    int type_of_collision = 0;
    type_of_collision = collision(obstacles, ball, racket_points, ball_state);
    if (*ball_state == MOVING)
    {
        ball->x += ball_trans_x;
        ball->y += ball_trans_y;
        ball->z += ball_trans_z;
    }

    if (bonus == GLUE && type_of_collision == 1)
    { // The racket is in glue mode and the ball touched the racket
        *ball_state = STOP;
        return 1;
    }

    return type_of_collision;
}

Obstacle *last_obstacle_passed;

void move_racket(ObstacleList *obstacles, RectanglePoints racket_points, MovingState *racket_state, Bonus *bonus_state, BonusList *bonus_list)
{
    Obstacle *obstacle = obstacles->first_obs;
    BonusObject *bonus = bonus_list->first_bonus;

    if (bonus != NULL && squareInBonus(*bonus, racket_points, racket_pos))
    { // Hit the bonus item
        switch (bonus->type)
        {
        case GLUE:
        {
            *bonus_state = GLUE;
            break;
        }
        case LIFE:
        {
            addLife();
            break;
        }
        default:
        {
        }
        }
        removeFirst(bonus_list);
    }

    if (obstacle != NULL && -racket_pos <= obstacle->section && obstacle->section < -racket_pos + racket_speed)
    { /*The obstacle is in front of the racket*/
        if (squareInObstacle(*obstacle, racket_points))
        {
            return;
        }
    }
    racket_pos -= racket_speed;
    return;
}