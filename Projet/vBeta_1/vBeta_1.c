#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"

LEVEL creation_lvl(SDL_Surface *ecran);
LEVEL init_lvl(LEVEL niveau);
void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void editor_menu(SDL_Surface *ecran);

int main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	
	main_menu(ecran);
	
	
	//LEVEL lvl;
	
	//lvl = lecture_fichier(2);
	//affichelvl(ecran,lvl);
	
	//creation_lvl(ecran);
	
	//pause();
	
	exit(EXIT_SUCCESS);
}

LEVEL creation_lvl(SDL_Surface *ecran)
{
	//printf("1\n");
	
	LEVEL niveau;
	niveau.width=10;
	niveau.height=10;
	
	niveau = init_lvl(niveau);
	
	/*
	int i,j;
	
	for(j=0;j<niveau.height;j++)
	{
		for(i=0;i<niveau.width;i++)
		{
			niveau.T[i][j] = 0;
		}
	}
	*/
	
	//printf("2\n");
	
	affichelvl(ecran,niveau);
	
	//printf("3\n");
	
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
	
	
	return niveau;
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


void main_menu(SDL_Surface *ecran)
{
	SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",30);

    SDL_Color couleurblanche = {255,255,255};

    SDL_Rect positionTexte;


    texte = TTF_RenderText_Blended(police,"PLAY",couleurblanche);

    positionTexte.x = 0 + (largeur_fenetre/2-(2*30))/2;
    positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    texte = TTF_RenderText_Blended(police,"EDIT LVL",couleurblanche);

    positionTexte.x = largeur_fenetre/2 + (largeur_fenetre/2-4*30)/2;
    positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    SDL_Flip(ecran);
    
    SDL_Event event;
    event = attendre_clic_gauche();
    
    if(encadrement(event.button.x,0,largeur_fenetre/2))
    {
		play_menu(ecran);
	}
	else
	{
		editor_menu(ecran);
	}
	
}

void play_menu(SDL_Surface *ecran)
{
	LEVEL lvl;
	lvl = lecture_fichier(1);
	affichelvl(ecran,lvl);
	pause();
}

void editor_menu(SDL_Surface *ecran)
{
	LEVEL niveau;
	niveau=creation_lvl(ecran);
	enregistrer_lvl(niveau);
}






