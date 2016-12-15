#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"

void affichelvl(SDL_Surface *ecran,LEVEL niveau)
{	
	int cote;
	if(largeur_fenetre/niveau.width>=hauteur_fenetre/niveau.height) cote = hauteur_fenetre/niveau.height;
	else cote = largeur_fenetre/niveau.width;
	
	SDL_Surface *vide = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *caisse = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *arrive = NULL;
	SDL_Surface *joueur_arrive = NULL;
	SDL_Surface *caisse_arrive = NULL;

	//~ vide = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ mur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ joueur_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	//~ caisse_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	
	vide = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	mur = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	joueur_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	caisse_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote, 32, 0, 0, 0, 0);
	
	SDL_FillRect(vide, NULL, SDL_MapRGB(ecran->format, 100, 247, 255));
	SDL_FillRect(mur, NULL, SDL_MapRGB(ecran->format, 142, 142, 142));
	SDL_FillRect(caisse, NULL, SDL_MapRGB(ecran->format, 237, 161, 55));
	SDL_FillRect(joueur, NULL, SDL_MapRGB(ecran->format, 58, 255, 77));
	SDL_FillRect(arrive, NULL, SDL_MapRGB(ecran->format, 228, 0, 8));
	SDL_FillRect(joueur_arrive, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
	SDL_FillRect(caisse_arrive, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
	
	SDL_Rect positionCase;
	
	SDL_Surface *fond = NULL;
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre, hauteur_fenetre, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	positionCase.x=0;
	positionCase.y=0;
	SDL_BlitSurface(fond,NULL,ecran,&positionCase);
	
	int i,j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			//~ positionCase.x=i*(largeur_fenetre/niveau.width) + (largeur_fenetre%niveau.width)/2;
			//~ positionCase.y=j*(hauteur_fenetre/niveau.height) + (hauteur_fenetre%niveau.height)/2;
			
			positionCase.x=i*(cote) + (largeur_fenetre%(cote*niveau.width))/2;
			positionCase.y=j*(cote) + (hauteur_fenetre%(cote*niveau.height))/2;
			
			switch(niveau.T[i][j])
			{
				case VIDE:
					SDL_BlitSurface(vide,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case MUR:
					SDL_BlitSurface(mur,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case CAISSE:
					SDL_BlitSurface(caisse,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case JOUEUR:
					SDL_BlitSurface(joueur,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case ARRIVE:
					SDL_BlitSurface(arrive,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case JOUEUR_ARRIVE:
					SDL_BlitSurface(joueur_arrive,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				case CAISSE_ARRIVE:
					SDL_BlitSurface(caisse_arrive,NULL,ecran,&positionCase);
					//SDL_Flip(ecran);
					break;
				default :
					printf("you forgot to blit a surface");
					break;
			}
		}
	}
	
	SDL_Flip(ecran);
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(joueur);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(arrive);
	SDL_FreeSurface(joueur_arrive);
	SDL_FreeSurface(caisse_arrive);
	SDL_FreeSurface(fond);
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
	
	if(lvl_num == 0)
    {
		texte = TTF_RenderText_Blended(police,"aucun niveau dispo",couleurblanche);
		positionTexte.x = largeur_fenetre/2 - (18/2*30/2);
	}
	
	else
	{
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
	}
	positionTexte.y = hauteur_fenetre/2 - 15;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    SDL_Flip(ecran);
}

void affiche_main_menu(SDL_Surface *ecran)
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
}


