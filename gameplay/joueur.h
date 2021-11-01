#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdbool.h>
#include "../moteur/physics.h"

typedef struct joueur {
    coords position;
    coords positionInitiale;
    bool mouvementEnCours;
    int frameDebutMouvement;
    vecteur mouvement;
} joueur;

#endif
