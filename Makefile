platformer: main.o affichage.o gameplay.o joueur.o
	gcc main.o affichage.o gameplay.o joueur.o -o platformer -lncurses -Wall

main.o: main.c affichage/affichage.h gameplay/gameplay.h
	gcc -c main.c

affichage.o: affichage/affichage.c gameplay/joueur.h
	gcc -c affichage/affichage.c

gameplay.o: gameplay/gameplay.c gameplay/input.h gameplay/joueur.h
	gcc -c gameplay/gameplay.c

input.o: gameplay/input.c
	gcc -c gameplay/input.c

joueur.o: gameplay/joueur.c
	gcc -c gameplay/joueur.c

clean:
	rm -f *.o
	rm -f platformer