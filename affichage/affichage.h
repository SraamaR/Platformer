#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/* affichage : permet d'afficher le jeu et les différents menus  */

#include "../gameplay/joueur.h"
#include "../map/map.h"


/* Initialise la bibliotèque NCurses */
void initCurses();

/* Affiche le menu */
void afficherMenu();

/* Initialise l'affichage */
void initAffichageJeu();

/* Affiche le jeu */
void affichageJeu(joueur j, map map);

/* Affiche le message de mort */
void afficherMsgMort();

/* Affiche le message de victoire */
void afficherMsgVictoire();

/* Libère la mémoire de l'affichage */
void libererMemoireAffichage();


#endif
