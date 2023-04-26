#include "../inc/animation.h"

void move_ball(ObstacleList * obstacles)
{
    ball_pos -= 0.08;
}


Obstacle * last_obstacle_passed;


void move_racket(ObstacleList * obstacles, RectanglePoints racket_form)
{
    Obstacle * obstacle = obstacles->first_obs;
    if(-racket_pos  > obstacle->section && obstacle->section > -racket_pos - 0.2){ /*The obstacle is in front of the racket*/
        printf("%d\n", obstacle == last_obstacle_passed);
        if(squareInObstacle(*obstacle, racket_form)){
            return;
        }
    }
    racket_pos -= 0.06;
    return;
}