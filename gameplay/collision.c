#include "joueur.h"
#include "../map/map.h"
#include "../moteur/physics.h"
#include "../moteur/frames.h"
#include <stdbool.h>
#include "../moteur/logger.h"
#include <stdio.h>

const int HIGH = 0;
const int LOW = 1;

bool verifierPasDepassementX(joueur *j, map instanceMap) {

    if (j->position.x + 1 >= instanceMap.x || j->position.x - 1 <= 0) {

        return false;

    } else {

        return true;

    }

}

bool verifierPasDepassementY(joueur *j, map instanceMap) {

    if (j->position.y + 1 >= instanceMap.y || j->position.y - 1 <= 0) {

        return false;

    } else {
    
        return true;

    }
}

void resetMouvementX(joueur *j) {

    j->accelX.valeur = 0.0;
    j->vitesseX.valeur = 0.0;

    return;

}

void resetMouvementY(joueur *j, int type) {

    j->vitesseY.valeur = 0.0;

    if (type == LOW) {

        j->accelY.valeur = 0.0;

    } else {

        j->accelY.valeur = -g;
        //j->accelY.tempsModif = compteurFrame;

    }

    return;

}

void checkCollision(joueur *j, map instanceMap) {


    // Cas de bords de map

    if (!verifierPasDepassementX(j, instanceMap)) {

        resetMouvementX(j);

        return;

    } 

    if (!verifierPasDepassementY(j, instanceMap)) {

        if (j->position.y <= 1) {
            
            resetMouvementY(j, HIGH); // cas ou le joueur est au sol 

        } else {

            resetMouvementY(j, LOW); // cas ou le joueur est au plafond

        }

        return;
        
    }

    int posX = j->position.x;
    int posY = j->position.y;



    if (j->deltaPos.x > 0 && instanceMap.collision_map[posX + 1][posY] == COLLISION) {

        resetMouvementX(j);
        newLog("collision x+");

    }

    if (j->deltaPos.x < 0 && instanceMap.collision_map[posX - 1][posY] == COLLISION) {

        resetMouvementX(j);

        char msg[100];
        sprintf(msg, "collision- \"%c\"", instanceMap.collision_map[posX - 1][posY]);
        newLog(msg);

    }



    if (j->deltaPos.y < 0.0 && instanceMap.collision_map[posX][posY + 1] == COLLISION) {

        resetMouvementY(j, LOW);

    }
    
    if (j->deltaPos.y > 0.0 && instanceMap.collision_map[posX][posY - 1] == COLLISION) {

        resetMouvementY(j, HIGH);

    }

    if (j->deltaPos.y <= 0 && instanceMap.collision_map[posX][posY + 1] == PAS_COLLISION) {

        resetMouvementY(j, HIGH);

    }

    return;

}
