#include "../inc/regles.h"

int life_points = 5;

void addLife(){
    life_points ++;
}


void removeLife(){
    life_points --;
}


int isAlive(){
    return life_points > 0;
}