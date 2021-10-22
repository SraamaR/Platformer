#include <ncurses.h>
#include <stdbool.h>

#include "affichage/affichage.h"
#include "gameplay/gameplay.h"

int main() 
{
    bool enCours = true;

    //Init joueur
    joueur j = initJoueur();

    while (enCours) 
    {
        affichage(j)

        getch();

        enCours = false;
    }
    
    endwin();

    return 0;
}