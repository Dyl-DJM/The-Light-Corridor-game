#include "../inc/animation.h"

double ball_speed = 0.06;
double racket_speed = 0.03;
double ball_trans_x = 0;
double ball_trans_y = 0;
double ball_trans_z = -0.06;

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
        if (ball.x + ball_trans_x >= obstacle.rect.a.x - 0.049 && ball.x + ball_trans_x <= obstacle.rect.d.x + 0.049)
        {
            if (ball.y + ball_trans_y >= obstacle.rect.a.y - 0.049 && ball.y + ball_trans_y <= obstacle.rect.d.y + 0.049)
            {
                ball_trans_z *= -1;
                return 1;
            }
        }
    }
    return 0;
}

int ballTouchRacket(RectanglePoints racket_points, Coords3D ball)
{
    if (ball.z <= racket_pos && ball.z >= racket_pos - racket_speed - ball_trans_z && ball_trans_z > 0)
    {
        if (ball.x + ball_trans_x >= racket_points.a.x - 0.049 && ball.x + ball_trans_x <= racket_points.d.x + 0.049)
        {
            if (ball.y + ball_trans_y >= racket_points.a.y - 0.049 && ball.y + ball_trans_y <= racket_points.d.y + 0.049)
            {
                ballBounceOnRacket(ball, racket_points);
                return 1;
            }
        }
    }
    return 0;
}

void ballBounceOnRacket(Coords3D ball, RectanglePoints racket_points)
{
    double center_racket_x = racket_points.d.x - ((racket_points.d.x - racket_points.a.x) / 2);
    double center_racket_y = racket_points.d.y - ((racket_points.d.y - racket_points.a.y) / 2);
    double distance_center_x = ball.x - center_racket_x;
    double distance_center_y = ball.y - center_racket_y;
    printf("Distance center x = %f, Distance center y = %f\n", distance_center_x, distance_center_y);

    ball_trans_x *= -1;
    ball_trans_y *= -1;
    ball_trans_x += ball_speed * distance_center_x;
    ball_trans_y += ball_speed * distance_center_y;
    ball_trans_z *= -1;
}

void collision(ObstacleList obstacles, Coords3D ball, RectanglePoints racket_points)
{
    // printf("Ball = %f Racket = %f\n", ball.z, racket_pos);
    if (ballTouchRacket(racket_points, ball))
    {
        printf("Boing ! Ball = %f Racket = %f\n", ball.z, racket_pos);
        return;
    }

    if (ballTouchWall(ball))
    {
        // printf("Boing (wall) ! Ball = %f \n", ball.z);
        return;
    }

    Obstacle *obstacle = obstacles.first_obs;

    while (obstacle != NULL)
    {
        // printf("Ball = %f Section = %f\n", ball.z, obstacle->section);
        if (ballTouchObstacle(*obstacle, ball))
        {
            // printf("Boing ! Ball = %f Section = %f\n", ball.z, obstacle->section);
            break;
        }
        obstacle = obstacle->next_obs;
    }
}

void move_ball(ObstacleList obstacles, Coords3D *ball, RectanglePoints racket_points)
{
    collision(obstacles, *ball, racket_points);
    ball->x += ball_trans_x;
    ball->y += ball_trans_y;
    ball->z += ball_trans_z;
}

Obstacle *last_obstacle_passed;

void move_racket(ObstacleList *obstacles, RectanglePoints racket_points)
{
    Obstacle *obstacle = obstacles->first_obs;
    if (-racket_pos <= obstacle->section && obstacle->section < -racket_pos + racket_speed)
    { /*The obstacle is in front of the racket*/

        // printf("section = %f, racket_pos = %f\n", obstacle->section, racket_pos);
        //  printf("%d\n", obstacle == last_obstacle_passed);
        if (squareInObstacle(*obstacle, racket_points))
        {
            return;
        }
    }
    racket_pos -= racket_speed;
    return;
}