platformer: main.o affichage.o gameplay.o joueur.o map.o console.o
	gcc main.o affichage.o gameplay.o joueur.o map.o console.o -o platformer -lncurses -Wall

main.o: main.c affichage/affichage.h gameplay/gameplay.h map/map.h affichage/console.h
	gcc -c main.c

affichage.o: affichage/affichage.c gameplay/joueur.h affichage/console.h
	gcc -c affichage/affichage.c

gameplay.o: gameplay/gameplay.c gameplay/input.h gameplay/joueur.h affichage/affichage.h
	gcc -c gameplay/gameplay.c

input.o: gameplay/input.c
	gcc -c gameplay/input.c

joueur.o: gameplay/joueur.c
	gcc -c gameplay/joueur.c

console.o: affichage/console.c
	gcc -c affichage/console.c

map.o: map/map.c affichage/affichage.h affichage/console.h
	gcc -c map/map.c

clean:
	rm -f *.o
	rm -f platformer
