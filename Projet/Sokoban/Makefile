all: vBeta_1
	

run: all
	./vBeta_1

vBeta_1: gestion_event.o affichage.o lecture_ecriture.o deplacement.o manipulation_liste.o ligne_commande.o verification_lvl.o vBeta_1.o
	gcc -Wall -g -o vBeta_1 vBeta_1.o gestion_event.o affichage.o lecture_ecriture.o manipulation_liste.o ligne_commande.o verification_lvl.o deplacement.o `sdl-config --libs` -lm -lSDL_ttf

vBeta_1.o: constantes.h vBeta_1.c
	gcc -c `sdl-config --cflags` vBeta_1.c

gestion_event.o: constantes.h gestion_event.c
	gcc -c `sdl-config --cflags` gestion_event.c

affichage.o: constantes.h affichage.c
	gcc -c `sdl-config --cflags` affichage.c
	
lecture_ecriture.o: constantes.h deplacement.h lecture_ecriture.c
	gcc -c lecture_ecriture.c

manipulation_liste.o: constantes.h manipulation_liste.c
	gcc -c manipulation_liste.c

ligne_commande.o: constantes.h ligne_commande.c
	gcc -c `sdl-config --cflags` ligne_commande.c

verification_lvl.o: constantes.h verification_lvl.c
	gcc -c verification_lvl.c

deplacement.o: constantes.h deplacement.c
	gcc -c deplacement.c

clean:
	rm -f *.o
	rm -f vBeta_1
