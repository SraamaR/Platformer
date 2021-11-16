#ifndef PHYSICS_H
#define PHYSICS_H

extern const float g;

typedef struct coords {

    int x;
    int y;

} coords;

typedef struct vecteur {

    float x;
    float y;

} vecteur;

typedef struct mouvement {

    float valeur;
    int tempsModif;

} mouvement;

coords calculPosition(int frameDebut, vecteur v0);

float valeurVitesse(mouvement vitesse);

float valeurAcceleration(mouvement accel);

#endif
