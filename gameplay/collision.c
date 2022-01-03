#include "joueur.h"
#include "../map/map.h"
#include "../moteur/physics.h"
#include "../moteur/frames.h"
#include <stdbool.h>
#include "../moteur/logger.h"
#include <stdio.h>

const int HIGH = 0;
const int LOW = 1;
const int EMPTY = 2;


void arreterMouvementY(joueur *j, int type) {

    if (type == LOW) {

        j->accelY.valeur = 0.0;
        j->accelY.tempsModif = compteurFrame;

        j->vitesseY.valeur = 0.0;

        return;

    } else {

        j->accelY.valeur = -g;
        j->accelY.tempsModif = compteurFrame;

        j->vitesseY.valeur = 0.0;

        return;
    }

}

void arreterMouvementX(joueur *j) {

    j->accelX.valeur = 0.0;
    j->accelX.tempsModif = 0.0;

    j->vitesseX.valeur = 0.0;

}

bool verifierCollisionY(joueur *j, map instanceMap){

    int sens = 0;

    if (j->deltaPos.y == 0.0) {
        sens = 0;
    } else if (j->deltaPos.y < 0.0) {
        sens = -1;
    } else {
        sens = 1;
    }

    if (j->position.y < 2 && sens == 1){
        arreterMouvementY(j, HIGH);
        return true;
    }

    if (j->position.y > instanceMap.y  - 2){
        arreterMouvementY(j, LOW);
        return true;
    }
    
    char suivant = instanceMap.collision_map[j->position.x][j->position.y - 1];
    char precedent = instanceMap.collision_map[j->position.x][j->position.y + 1];

    

    char msg[100];

    sprintf(msg, "sens : %d", sens);
    newLog(msg);

    if (suivant == COLLISION && sens == 1) {
        arreterMouvementY(j, HIGH);
        return true;
    }

    if (precedent == COLLISION && sens == -1) {
        arreterMouvementY(j, LOW);
        return true;
    }

    if (sens == 0) {

        if (j->vitesseY.valeur > 0.0 && suivant == COLLISION) {
            arreterMouvementY(j, LOW);
            return true;
        }

        if (precedent != COLLISION && j->accelY.valeur > -g){
            j->accelY.valeur = -g;
            j->accelY.tempsModif = compteurFrame;
            return false;
        }

    }

    

    

    return false;

}

bool verifierCollisionX(joueur *j, map instanceMap){

    int sens = 0;

    if (j->deltaPos.x == 0.0) {
        sens = 0;
    } else if (j->deltaPos.x < 0.0) {
        sens = -1;
    } else {
        sens = 1;
    }

    if (j->position.x < 2 && sens == -1){
        arreterMouvementX(j);
        return true;
    }

    if (j->position.x > instanceMap.x - 2){
        arreterMouvementX(j);
        return true;
    }
    
    char suivant = instanceMap.collision_map[j->position.x + 1][j->position.y];
    char precedent = instanceMap.collision_map[j->position.x - 1][j->position.y];

    if (sens == 1) {

        if (suivant == COLLISION) {

            arreterMouvementX(j);
            return true;
        }


    }

    if (sens == -1){
    
        if (precedent == COLLISION) {
            arreterMouvementX(j);
            return true;
        }
    }

    if (sens == 0) {

        if(j->vitesseX.valeur < 0 && precedent == COLLISION) {
            arreterMouvementX(j);
            return true;
        }

        if(j->vitesseX.valeur > 0 && suivant == COLLISION) {
            arreterMouvementX(j);
            return true;
        }

    }

    

    return false;

}
