#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "joueur.h"
#include "../map/map.h"

extern const int MOUV_X;
extern const int MOUV_Y;


void ajouterVitesse(joueur *j, float valeur, int type);

void ajouterAcceleration(joueur *j, float valeur, int type);

void actualisationMouvements(joueur *j, map instanceMap);

void mortJoueur(joueur *j);

void victoireJoueur(joueur *j);

void mouvSaut(joueur* j);
void mouvDroite(joueur* j);
void mouvGauche(joueur* j);

#endif
