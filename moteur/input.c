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
            ajouterVitesse(j, 15.0, MOUV_Y);
            ajouterAcceleration(j, -g, MOUV_Y);
            afficherMessageConsole("Nouveau mouvement", INFOMSG);
            break;
        case KEY_RIGHT:
            ajouterVitesse(j, 3.0, MOUV_X);
            ajouterAcceleration(j, -1.5, MOUV_X);
            afficherMessageConsole("Nouveau mouvement lateral", INFOMSG);
            break;
        case KEY_LEFT:
            ajouterVitesse(j, -3.0, MOUV_X);
            ajouterAcceleration(j, 1.5, MOUV_X);
            afficherMessageConsole("Nouveau mouvement lateral", INFOMSG);
            break;
        default:
            break;

    }

    return;

}
