#ifndef JOUEUR_H
#define JOUEUR_H

/* joueur : permet de crer un joueur  */

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

/* Définit les coordonées du spawn */
void defSpawn(int x, int y);

/* Initialise un joueur aux coordonnées du spawn */
joueur initJoueurSpawn();


#endif
