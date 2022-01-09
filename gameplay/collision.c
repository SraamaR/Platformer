#include <stdbool.h>
#include <stdio.h>

#include "joueur.h"
#include "../map/map.h"
#include "./gameplay.h"
#include "../moteur/physics.h"
#include "../moteur/frames.h"
#include "../moteur/logger.h"


const int HIGH = 0;
const int LOW = 1;
const int EMPTY = 2;


/* Arrete le mouvement en axe x */
void arreterMouvementX(joueur* j) {

    j->accelX.valeur = 0.0;
    j->accelX.tempsModif = 0.0;

    j->vitesseX.valeur = 0.0;

    return;

}


/* Arrete le mouvement en axe y */
void arreterMouvementY(joueur* j, int type) {

    if (type == LOW) { // cas où le joueur est au sol
    
        j->accelY.valeur = 0.0;
        j->accelY.tempsModif = compteurFrame;
    
        j->vitesseY.valeur = 0.0;
    
    }
    else { // cas ou le joueur est en l'air
    
        j->accelY.valeur = -g;
        j->accelY.tempsModif = compteurFrame;

        j->vitesseY.valeur = 0.0;
    
    }

    return;
}


/* Verifie les collisions en axe x, arrete le mouvement ou tue le joueur en fonction */
bool verifierCollisionX(joueur* j, map instanceMap) {

    int sens = 0;

    if (j->deltaPos.x == 0.0) {
        sens = 0;
    }
    else if (j->deltaPos.x < 0.0) {
        sens = -1;
    }
    else {
        sens = 1;
    }

    if ((j->position.x < 2) && (sens == -1)) {
    
        arreterMouvementX(j);
        return true;
    
    }

    if (j->position.x > instanceMap.x-2) {
    
        arreterMouvementX(j);
        return true;
    
    }

    char suivant = instanceMap.collision_map[j->position.x + 1][j->position.y];
    char precedent = instanceMap.collision_map[j->position.x - 1][j->position.y];
    char objSuivant = instanceMap.ptr_map[j->position.x + 1][j->position.y];
    char objPrecedent = instanceMap.ptr_map[j->position.x - 1][j->position.y];

    if (sens == 1) {
    
        if (objSuivant == CHAR_PIQUEDROITE) {
            mortJoueur(j, instanceMap);
        }
    
        if (suivant == COLLISION) {
        
            arreterMouvementX(j);
            return true;
        
        }
    
    }

    if (sens == -1) {
    
        if(objPrecedent == CHAR_PIQUEGAUCHE) {
            mortJoueur(j, instanceMap);
        }
    
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
    
        if((j->vitesseX.valeur > 0) && (suivant == COLLISION)) {
        
            arreterMouvementX(j);
            return true;
        
        }

    }

    return false;

}


/* Verifie les collisions en axe y, arrete le mouvement ou tue le joueur en fonction */
bool verifierCollisionY(joueur* j, map instanceMap) {

    int sens = 0;

    if (j->deltaPos.y == 0.0) {
        sens = 0;
    }
    else if (j->deltaPos.y < 0.0) {
        sens = -1;
    }
    else {
        sens = 1;
    }

    if ((j->position.y < 2) && (sens == 1)) {
    
        arreterMouvementY(j, HIGH);
        return true;
    
    }

    if (j->position.y > instanceMap.y-2) {
    
        arreterMouvementY(j, LOW);
        return true;
    
    }

    char suivant = instanceMap.collision_map[j->position.x][j->position.y - 1];
    char precedent = instanceMap.collision_map[j->position.x][j->position.y + 1];
    char objSuivant = instanceMap.ptr_map[j->position.x][j->position.y - 1];
    char objPrecedent = instanceMap.ptr_map[j->position.x][j->position.y + 1];

    /* Tests
    char msg[100];
    sprintf(msg, "sens : %d", sens);
    nouveauLog(msg);
    */

    if(sens == 1) {
    
        if (objSuivant == CHAR_PIQUEHAUT) {
            mortJoueur(j, instanceMap);
        }
    
        if (suivant == COLLISION) {
        
            arreterMouvementY(j, HIGH);
            return true;
        
        }

    }

    if(sens == -1){
    
        if (objPrecedent == CHAR_PIQUEBAS) {
            mortJoueur(j, instanceMap);
        }

        if (precedent == COLLISION) {
        
            arreterMouvementY(j, LOW);
            return true;
        
        }
    
    }

    if (sens == 0) {
    
        if ((j->vitesseY.valeur > 0.0) && (suivant == COLLISION)) {
        
            arreterMouvementY(j, LOW);
            return true;
        
        }
    
        if ((precedent != COLLISION) && (j->accelY.valeur > -g)) {
        
            j->accelY.valeur = -g;
            j->accelY.tempsModif = compteurFrame;
            return false;
        
        }

    }

    return false;

}