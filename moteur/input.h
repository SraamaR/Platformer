#ifndef INPUT_H
#define INPUT_H

/* input : Permet de gerer les actions celon les entrees clavier */

#include <stdbool.h>

#include "../gameplay/joueur.h"
#include "../map/map.h"


/* Permet d'effectuer des actions celon l'entree clavier utilisee */
void inputControle(int entree, bool *enCours, joueur *j, map instanceMap);


#endif