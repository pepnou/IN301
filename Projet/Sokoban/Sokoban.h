// PEPIN Thibaut

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <string.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"
#include "manipulation_liste.h"
#include "ligne_commande.h"
#include "verification_lvl.h"
#include "actions.h"

int NBR_NIVEAUX = 0;

char* fichier_a_lire = "./sauvegardes/default.xsb";
char* fichier_pour_ecrire = "./sauvegardes/default.xsb";

void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void menu_taille_lvl(SDL_Surface *ecran);
void creation_lvl(SDL_Surface *ecran,int width,int height);
void modif_niveau(LEVEL niveau,SDL_Surface *ecran);
void play_mode(SDL_Surface *ecran,int num_lvl);
LEVEL play_mode_invert(SDL_Surface *ecran,LEVEL lvl);
LEVEL play_mode_invert_auto(SDL_Surface *ecran,LEVEL lvl);
