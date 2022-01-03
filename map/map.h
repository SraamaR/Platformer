#ifndef MAP_H
#define MAP_H

extern const char CHAR_BORD;
extern const char CHAR_SPAWN;
extern const char CHAR_VIDE;
extern const char CHAR_PLATFORME;
extern const char CHAR_PIQUEDROITE;
extern const char CHAR_PIQUEGAUCHE;
extern const char CHAR_PIQUEHAUT;
extern const char CHAR_PIQUEBAS;

extern const char COLLISION;
extern const char PAS_COLLISION; 

typedef struct s_map {
    char** ptr_map;
    char** collision_map;
    int x;  //Longueur ligne
    int y;  //Nombre lignes
} map;

map chargementMap();

void posSpawnJoueur(int* x, int* y, map instanceMap);

void libererMemoireMap(map instanceMap);

int posFin(map instanceMap);

#endif
