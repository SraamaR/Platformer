#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* gameplay : permet de gerer les mouvements du joueur  */

#include "joueur.h"
#include "../map/map.h"


extern const int MOUV_X;
extern const int MOUV_Y;

/* crée un nouveau mouvement avec un vecteur vitesse de composantes vx et vy */
void ajouterVitesse(joueur *j, float valeur, int type);

/*  */
void ajouterAcceleration(joueur *j, float valeur, int type);

/* Actualise tous les mouvements dans le jeu */
void actualisationMouvements(joueur *j, map instanceMap);

/* Creer un mouvement vers la gauche */
void mouvGauche(joueur* j);

/* Creer un mouvement vers la droite */
void mouvDroite(joueur* j);

/* Creer un saut (mouvement vers le haut) */
void mouvSaut(joueur* j);

/* Gestion de la mort du joueur*/
void mortJoueur(joueur *j);

/* Gestion de la victoire */
void victoireJoueur(joueur *j);


#endif
