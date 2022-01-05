#ifndef COLLISION_H
#define COLLISION_H

/* collision : permet de gerer les collisions du joueur dans la map  */

#include <stdbool.h>

#include "joueur.h"
#include "../map/map.h"


/* Verifie les collisions en axe x, arrete le mouvement ou tue le joueur en fonction */
bool verifierCollisionX(joueur *j, map instanceMap);

/* Verifie les collisions en axe y, arrete le mouvement ou tue le joueur en fonction */
bool verifierCollisionY(joueur *j, map instanceMap);


#endif