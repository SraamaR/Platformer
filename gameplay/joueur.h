#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdbool.h>
#include "../moteur/physics.h"

typedef struct s_joueur {

    coords position;
    vecteur positionPrecise;
    vecteur deltaPos; // ecart de position
    mouvement accelX; // acceleration sur x
    mouvement accelY; // acceleration sur y
    mouvement vitesseX; // vitesse sur x
    mouvement vitesseY; //vitesse sur y

} joueur;

joueur initJoueur();

#endif
