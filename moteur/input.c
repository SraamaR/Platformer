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
            //nouveauMouvement(j, 0.0, 3.0);
            afficherMessageConsole("Nouveau mouvement", INFOMSG);
            break;
        default:
            break;

    }

    return;

}
