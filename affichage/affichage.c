#include <ncurses.h>

#include "../gameplay/joueur.h"

void creerMenu()
{
    initscr();

    int yMax, xMax;

    getmaxyx(stdscr, yMax, xMax);

    mvprintw(yMax /2, xMax / 2 - 5,"Platformer");
}

void affichage(joueur j)
{
    creerMenu();
}
