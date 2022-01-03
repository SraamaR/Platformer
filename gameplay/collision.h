#ifndef COLLISION_H
#define COLLISION_H

#include "joueur.h"
#include "../map/map.h"
#include <stdbool.h>

bool verifierCollisionY(joueur *j, map instanceMap);

bool verifierCollisionX(joueur *j, map instanceMap);

#endif