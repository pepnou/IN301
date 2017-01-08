#~ PEPIN Thibaut 

compil: Sokoban
	

test: clean all
	./Sokoban -n 8 ./sauvegardes/sasquatch1.xsb

run: compil
	./Sokoban

Sokoban: gestion_event.o affichage.o lecture_ecriture.o actions.o manipulation_liste.o ligne_commande.o verification_lvl.o Sokoban.o
	gcc -Wall -g -o Sokoban Sokoban.o gestion_event.o affichage.o lecture_ecriture.o manipulation_liste.o ligne_commande.o verification_lvl.o actions.o `sdl-config --libs` -lm -lSDL_ttf

Sokoban.o: Sokoban.h constantes.h Sokoban.c
	gcc -c `sdl-config --cflags` Sokoban.c

gestion_event.o: constantes.h gestion_event.c
	gcc -c `sdl-config --cflags` gestion_event.c

affichage.o: constantes.h affichage.c
	gcc -c `sdl-config --cflags` affichage.c

lecture_ecriture.o: constantes.h lecture_ecriture.c
	gcc -c lecture_ecriture.c

manipulation_liste.o: constantes.h manipulation_liste.c
	gcc -c manipulation_liste.c

ligne_commande.o: constantes.h ligne_commande.c
	gcc -c `sdl-config --cflags` ligne_commande.c

verification_lvl.o: constantes.h verification_lvl.c
	gcc -c verification_lvl.c

actions.o: constantes.h actions.c
	gcc -c actions.c

clean:
	rm -f *.o
	rm -f Sokoban

alignement:
	indent -linux -l 120 *.c
