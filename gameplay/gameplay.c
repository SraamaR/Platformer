//#include <ncurses.h>
#include <stdlib.h>

#include "joueur.h"
#include "../affichage/affichage.h"
#include "../affichage/console.h"
#include "../map/map.h"

//Initialise un joueur aux positions (x, y)
joueur initJoueur(int x, int y)
{
    joueur j;
    j.posx = x;
    j.posy = y;

    afficherMessageConsole("Initialisation du joueur effectuee", INFOMSG);
    /*Tests
    mvprintw(LINES / 2 - 1, 1, "x = %d", x);
    mvprintw(LINES / 2    , 1, "y = %d", y);
    */

    return j;
}