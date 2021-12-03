#include <ncurses.h>
#include <stdbool.h>
#include "../affichage/console.h"
#include "../gameplay/gameplay.h"
#include "../gameplay/joueur.h"

void inputControle(int entree, bool *enCours, joueur *j) {

    switch(entree) {

        case 27: // 27 => echap
            *enCours = false;
            afficherMessageConsole("Le programme va s'arreter. Appuyez sur une touche pour continuer...", INFOMSG);
            break;
        case KEY_UP:
            mouvSaut(j);
            break;
        case KEY_RIGHT:
            mouvDroite(j);
            break;
        case KEY_LEFT:
            mouvGauche(j);
            break;
        default:
            break;
    }

    return;

}