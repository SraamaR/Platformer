#ifndef FRAMES_H
#define FRAMES_H

/* frames : Agit comme une horloge; compte les frames depuis le démarrage du jeu */


extern int compteurFrame;
extern float ecartFrameMs;

/* initialise le moteur de frame avec le nombre de fps visé */
void initFrames(int fps);

/* compte la frame suivante */
void frameSuivante();


#endif
