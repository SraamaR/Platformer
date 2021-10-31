#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../gameplay/joueur.h"
#include "../map/map.h"

typedef struct camera {
    int centrex;
    int centrey;
} camera;

void initAffichage();

void affichage(joueur j, map map);

#endif