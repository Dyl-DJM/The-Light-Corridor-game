#include "../inc/obstacle.h"
#include "../inc/bonus.h"

int main(void)
{

    ObstacleList *list;
    RectanglePoints rect = initRect(initCoords(0, 0), initCoords(6, 6));
    RectanglePoints rect2 = initRect(initCoords(2, 4), initCoords(6, 8));

    list = initObstacleList();

    printList(*list);

    add(list, rect, 10);
    add(list, rect, 12);
    add(list, rect, 15);
    add(list, rect2, 20);

    printList(*list);

    removeObs(list, -15); /* Remove all the obstacles which are positioned behind 15 in z value in the scene*/

    printList(*list);

    int ball_pos = -19;
    for (int i = 0; i < 3; i++)
    {
        addRandomObstacle(list, ball_pos, 1000);
        ball_pos -= 4;
    }

    printList(*list);

    printf("\n\n=== Bonus part ===\n\n");

    BonusList * blist = initBonusList();

    printBonusList(*blist);

    Coords3D bcoords;
    bcoords.x = 10;
    bcoords.y = 20;
    bcoords.z = 30;
    addBonus(blist, bcoords, 10);
    addBonus(blist, bcoords, 20);
    addBonus(blist, bcoords, 10);
    addBonus(blist, bcoords, 10);
    addBonus(blist, bcoords, 15);

    printBonusList(*blist);

    removeBonus(blist, -100);

    printBonusList(*blist);



    return 0;
}