#include <ncurses.h>
#include "affichage/affichage.h"
#include <stdbool.h>

int main() 
{
    bool enCours = true;

    while (enCours) {

        creerMenu();

        getch();

        enCours = false;
    
    }
        

    endwin();

    return 0;

}