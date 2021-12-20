#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../gameplay/joueur.h"
#include "../map/map.h"

void initCurses();

void afficherMenu();

void afficherMsgVictoire();

void afficherMsgMort();

void initAffichageJeu();

void affichageJeu(joueur j, map map);

void libererMemoireAffichage();

#endif
