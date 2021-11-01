#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "joueur.h"

joueur initJoueur();

void nouveauMouvement(joueur *j, float vx, float vy);

void actualisation(joueur *j);

#endif
