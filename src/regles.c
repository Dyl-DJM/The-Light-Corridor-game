#include "../inc/regles.h"



void addLife(){
    life_points ++;
}


void removeLife(){
    life_points --;
}


int isAlive(){
    return life_points <= 0;
}