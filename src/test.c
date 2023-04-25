#include "../inc/obstacle.h"

int main(void){

    ObstacleList *list;
    RectanglePoints points;
    RectanglePoints points2;

    points2.a.x = 0; 
    points2.a.y = 0;
    points2.b.x = 2; 
    points2.b.y = 2;
    points2.c.x = 4; 
    points2.c.y = 4;
    points2.d.x = 6; 
    points2.d.y = 6;

    points.a.x = 0; 
    points.a.y = 0;
    points.b.x = 2; 
    points.b.y = 2;
    points.c.x = 4; 
    points.c.y = 4;
    points.d.x = 6; 
    points.d.y = 6;

    list = initObstacleList();

    printList(*list); 

    add(list, points, 12);
    add(list, points, 10);
    add(list, points, 10);
    add(list, points2, 20);

    printList(*list);

    removeObs(list, 15); /* Remove all the obstacles which are positioned behind 15 in z value in the scene*/

    printList(*list);

    return 0;
}