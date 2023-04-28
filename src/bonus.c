#include "../inc/bonus.h"




BonusObject *initBonus(Coords3D coords, double radius)
{
    BonusObject *tmp = malloc(sizeof(*tmp));

    if (tmp == NULL)
    {
        return NULL;
    }

    tmp->coords = coords;
    tmp->r = radius;
    tmp->type = (rand() % 2) == 0 ? GLUE : LIFE;
    tmp->next_bonus = NULL;

    return tmp;
}

BonusList *initBonusList()
{
    BonusList *list = malloc(sizeof(*list));

    if (list == NULL)
    {
        return NULL;
    }

    list->first_bonus = NULL;
    list->last_bonus = NULL;

    return list;
}

void printBonus(BonusObject bonus){
    printf("(%f, %f, %f) => %f => (type : %d)\n", bonus.coords.x, bonus.coords.y, bonus.coords.z, bonus.r, bonus.type);
}

void printBonusList(BonusList list)
{
    BonusObject *bonus = list.first_bonus;

    printf("\n\n=== LIST ===\n");
    while (bonus != NULL)
    {
        printBonus(*bonus);
        bonus = bonus->next_bonus;
    }
    printf("NULL\n");
}

void removeBonus(BonusList *list, double racket_pos)
{
    if (list == NULL)
    {
        return;
    }

    BonusObject *bonus = list->first_bonus;
    while (bonus != NULL && bonus->coords.z < -racket_pos - 2)
    {
        // Suppresion
        BonusObject *remove = bonus;
        list->first_bonus = bonus->next_bonus;
        bonus = bonus->next_bonus;
        free(remove);
    }
    while (bonus != NULL)
    {
        BonusObject *danglingElem = bonus->next_bonus;

        while (danglingElem != NULL && danglingElem->coords.z < -racket_pos - 2)
        { /* Supression*/
            BonusObject *remove = danglingElem;
            danglingElem = danglingElem->next_bonus;
            free(remove);
        }
        bonus->next_bonus = danglingElem;
        bonus = bonus->next_bonus;
    }
}

void addBonus(BonusList *list, Coords3D coords, double radius)
{
    BonusObject *to_insert = initBonus(coords, radius);
    if (list == NULL)
    {
        return;
    }
    list->last_bonus = to_insert;
    BonusObject *tmp = list->first_bonus;
    if (tmp == NULL)
    {
        list->first_bonus = to_insert;
        return;
    }
    while (tmp->next_bonus != NULL)
    {
        tmp = tmp->next_bonus;
    }
    tmp->next_bonus = to_insert;
}



int pointInSphere(Coords3D origin, Coords point, double section, double radius){
    double x = pow((point.x - origin.x), 2);
    double y = pow((point.y - origin.y), 2);
    double z = pow((section - origin.z), 2);

    double d = sqrt(x + y + z);
    if(d  <= radius + 0.2){
        return 1;
    }
    return 0;
}

int squareInBonus(BonusObject bonus, RectanglePoints rect, double section){
    if(pointInSphere(bonus.coords, rect.a, section, bonus.r)){
        return 1;
    }
    if(pointInSphere(bonus.coords, rect.b, section, bonus.r)){
        return 1;
    }
    if(pointInSphere(bonus.coords, rect.c, section, bonus.r)){
        return 1;
    }
    if(pointInSphere(bonus.coords, rect.d, section, bonus.r)){
        return 1;
    }
    return 0;
}

void freeBonus(BonusList * list)
{ 
    if(list == NULL){  
        return;
    }

    for(BonusObject * current = list->first_bonus; current != NULL;){
        BonusObject * remove = current;
        current = current->next_bonus;
        free(remove);
        remove = NULL;
    }

    free(list);
    list = NULL;
}