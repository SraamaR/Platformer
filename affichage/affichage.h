#ifndef AFFICHAGE_H

#define AFFICHAGE_H

#include "../gameplay/joueur.h"

void afficherMessageConsole(char str[]);

void initConsole();

void initAffichage();

void affichage(joueur j);

void libererMemoireAffichage();

#endif