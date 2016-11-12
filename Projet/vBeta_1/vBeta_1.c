#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"

void creation_lvl(SDL_Surface *ecran);
LEVEL init_lvl(LEVEL niveau);

int main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	LEVEL lvl;
	
	//lvl = lecture_fichier(2);
	//affichelvl(ecran,lvl);
	
	creation_lvl(ecran);
	
	//pause();
	
	exit(EXIT_SUCCESS);
}

void creation_lvl(SDL_Surface *ecran)
{
	//printf("1\n");
	
	LEVEL niveau;
	niveau.width=10;
	niveau.height=10;
	
	//niveau = init_lvl(niveau);
	
	
	int i,j;
	
	for(j=0;j<niveau.height;j++)
	{
		for(i=0;i<niveau.width;i++)
		{
			niveau.T[i][j] = 0;
		}
	}
	
	printf("2\n");
	
	affichelvl(ecran,niveau);
	
	printf("3\n");
	
	SDL_Event event;
	int continuer = 1;
	
	
	
	while(continuer)
	{
		
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_RETURN) continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				niveau.T[event.button.x/(largeur_fenetre/niveau.width)][event.button.y/(hauteur_fenetre/niveau.height)] = (niveau.T[event.button.x/(largeur_fenetre/niveau.width)][event.button.y/(hauteur_fenetre/niveau.height)] + 1 ) % 7;
				affichelvl(ecran,niveau);
				break;
			default:
				break;
		}
	}
	
	
	
}

LEVEL init_lvl(LEVEL niveau)
{
	int i,j;
	
	for(j=0;j<niveau.height;j++)
	{
		for(i=0;i<niveau.width;i++)
		{
			niveau.T[i][j] = 0;
		}
	}
	
	return niveau;
}



