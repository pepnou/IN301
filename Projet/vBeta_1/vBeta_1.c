#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"



int main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    

    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	LEVEL lvl;
	
	lvl = lecture_fichier(2);
	
	affichelvl(ecran,lvl);
	
	pause();
	
	exit(EXIT_SUCCESS);
}
