#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"

int NBR_NIVEAUX = 0;

LEVEL creation_lvl(SDL_Surface *ecran);
LEVEL init_lvl(LEVEL niveau);
void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void editor_menu(SDL_Surface *ecran);
void affiche_play_menu(SDL_Surface *ecran,int lvl_num);

int main()
{
	//printf("1\n");
	
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	//printf("2\n");
	
	//NBR_NIVEAUX = lecture_nbr_lvl();
	
	//printf("3\n");
	
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
	SDL_Surface *fond = NULL;
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre, hauteur_fenetre, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_Rect positionCase;
	positionCase.x=0;
	positionCase.y=0;
	
	SDL_BlitSurface(fond,NULL,ecran,&positionCase);
	
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
    
    /*
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
	*/
	
	int continuer = 1;
	SDL_Event event;
    
    while(continuer)
    {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 0;
						break;	
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(encadrement(event.button.x,0,largeur_fenetre/2))
				{
					play_menu(ecran);
				}
				else
				{
					editor_menu(ecran);
				}
				break;
			case SDL_QUIT:
					continuer = 0;
					break;
		}
	}
}

void play_menu(SDL_Surface *ecran)
{
	NBR_NIVEAUX = lecture_nbr_lvl();
	
	LEVEL lvl;
	
	int niveau_a_lire = 1;
	
	affiche_play_menu(ecran,niveau_a_lire);
	
	int continuer = 1;
	SDL_Event event;
    
    while(continuer)
    {
		SDL_WaitEvent(&event);
		if((event.type ==SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_RETURN)) continuer = 0;
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			if(encadrement(event.button.x,0,largeur_fenetre/2))
			{
				if(niveau_a_lire>1) niveau_a_lire --;
			}
			else
			{
				if(niveau_a_lire<NBR_NIVEAUX) niveau_a_lire ++;
			}
			
			affiche_play_menu(ecran,niveau_a_lire);
		}
		
		
	}
	
	
	
	lvl = lecture_fichier(niveau_a_lire);
	affichelvl(ecran,lvl);
	pause();
}

void editor_menu(SDL_Surface *ecran)
{
	LEVEL niveau;
	niveau=creation_lvl(ecran);
	enregistrer_lvl(niveau);
	
	//printf("%d\n",NBR_NIVEAUX);
	NBR_NIVEAUX++;
	//printf("%d\n",NBR_NIVEAUX);
	
	//ecriture_nbr_lvl(NBR_NIVEAUX);
	main_menu(ecran);
}

void affiche_play_menu(SDL_Surface *ecran,int lvl_num)
{
	SDL_Surface *fond = NULL;
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre, hauteur_fenetre, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_Rect positionCase;
	positionCase.x=0;
	positionCase.y=0;
	
	SDL_BlitSurface(fond,NULL,ecran,&positionCase);
	
	SDL_Surface *texte = NULL;
	
    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",30);

    SDL_Color couleurblanche = {255,255,255};

    SDL_Rect positionTexte;

    texte = TTF_RenderText_Blended(police,"+",couleurblanche);

    positionTexte.x = largeur_fenetre*3/4 -15;
    positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    texte = TTF_RenderText_Blended(police,"-",couleurblanche);

    positionTexte.x = largeur_fenetre/4 -15;
    positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    
    char Tmp[10] = "";
    sprintf(Tmp,"%d",lvl_num);
    
    texte = TTF_RenderText_Blended(police,Tmp,couleurblanche);

    positionTexte.x = largeur_fenetre/2 - 15;
    positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    SDL_Flip(ecran);
}




