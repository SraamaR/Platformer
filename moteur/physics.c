#include <math.h>

#include "./frames.h"
#include "./physics.h"


const float g = 10;
const float coefficientVitesse = 2.0; // définit la vitesse du mouvement (et donc par conséquent du jeu)


/* retourne la position relative par rapport a l'instant précédent */
float valeurAcceleration(mouvement accel) {

    float t = (compteurFrame - accel.tempsModif) * ecartFrameMs / 1000 * coefficientVitesse;
    float tm1 = (compteurFrame - accel.tempsModif - 1) * ecartFrameMs / 1000 * coefficientVitesse;
    float res = accel.valeur * t * t;

    if (tm1 > 0) { // si le temps - 1 (tm1) est supérieur à 0 on enleve le trajet fait précédemment
        res -= accel.valeur * tm1 * tm1;
    }

    return res;

}


/*  */
float valeurVitesse(mouvement vitesse) {

    return vitesse.valeur * ecartFrameMs / 1000 * coefficientVitesse; // pas besoin de soustraire, car c'est linéaire, tout les dt la position augmente de la même grandeur

}
