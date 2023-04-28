#include "../inc/regles.h"

int life_points = 5;
double end_corridor;

void addLife(){
    life_points ++;
}



void initLengthCorridor(){
    end_corridor = randRange(40, 200);
}

void removeLife(){
    life_points --;
}


int isAlive(){
    return life_points > 0;
}


double endCorridor(){
    return end_corridor;
}

int isCorridorEnd(double racket_pos){
    return -racket_pos >= end_corridor; 
}