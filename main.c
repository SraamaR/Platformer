#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "affichage/affichage.h"
#include "gameplay/gameplay.h"
#include "map/map.h"

int main() 
{
    //Declaration variables
    bool enCours = true;
    bool activerConsole = true;
    char* map = NULL;

    //Init affichage
    initscr();
    if(activerConsole)
    {
        initConsole();
    }
    initAffichage();

    //Init map
    chargementMap(map);
    
    //Init gameplay
    joueur j = initJoueur();

    while (enCours) 
    {
        affichage(j);

        getch();

        enCours = false;
    }
    
    //Arret du jeu
    if(map != NULL)
    {
        free(map);
    }
    libererMemoireAffichage();
    endwin();
    return 0;
}