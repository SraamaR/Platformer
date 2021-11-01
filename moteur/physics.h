#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct coords {

    int x;
    int y;

} coords;

typedef struct vecteur {

    float x;
    float y;

} vecteur;

coords calculPosition(int frameDebut, vecteur v0);

#endif
