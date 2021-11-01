#include <math.h>
#include "./frames.h"

const float g = 9.81;
const float coefficientVitesse = 2.0; // définit la vitesse du mouvement (et donc par conséquent du jeu)

typedef struct coords {

    int x;
    int y;

} coords;

typedef struct vecteur {

    float x;
    float y;

} vecteur;

coords calculPosition(int frameDebut, vecteur v0) 
{

    coords res;

    float t = (compteurFrame - frameDebut) * ecartFrameMs / 1000 * coefficientVitesse;

    res.x = round(v0.x * t);
    
    res.y = round(-g/2*t*t + v0.y * t);

    return res;

}
