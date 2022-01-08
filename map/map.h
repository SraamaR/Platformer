#ifndef MAP_H
#define MAP_H

/* map : Permet de charger la map depuis un fichier .txt */


extern const char CHAR_BORD;
extern const char CHAR_VIDE;
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

/* Lit un fichier texte puis renvoie ses données sous la forme d'un struct map lisible par le jeu */
map chargementMap();

/* Libère la mémoire occupée par les tableaux */
void libererMemoireMap(map instanceMap);

/* Renvoie les coordonées du point d'apparition du joueur 
puis supprime le charactère spawn de la carte envoyée en argument */
void posSpawnJoueur(int* x, int* y, map instanceMap);

/* Renvoie les coordonées de la ligne de victoire
puis supprime le charactère fin de la carte envoyée en argument */
int posFin(map instanceMap);


#endif
