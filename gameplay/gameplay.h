#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "joueur.h"

extern const int MOUV_X;
extern const int MOUV_Y;

joueur initJoueur();

void ajouterVitesse(joueur *j, float valeur, int type);

void ajouterAcceleration(joueur *j, float valeur, int type);


void actualisation(joueur *j);

#endif
