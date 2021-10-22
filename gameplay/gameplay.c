#include "joueur.h"
#include <stdlib.h>

//initialise un joueur aux positions (0, 0)
joueur initJoueur()
{
    joueur res;

    res.posx = 0;
    res.posy = 0;

    return res;
}