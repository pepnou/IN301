#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"

void affichelvl(SDL_Surface *ecran,LEVEL niveau)
{
	SDL_Surface *vide = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *caisse = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *arrive = NULL;
	SDL_Surface *joueur_arrive = NULL;
	SDL_Surface *caisse_arrive = NULL;

	vide = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	mur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	joueur_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	caisse_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur_fenetre/niveau.width, hauteur_fenetre/niveau.height, 32, 0, 0, 0, 0);
	
	SDL_FillRect(vide, NULL, SDL_MapRGB(ecran->format, 100, 247, 255));
	SDL_FillRect(mur, NULL, SDL_MapRGB(ecran->format, 142, 142, 142));
	SDL_FillRect(caisse, NULL, SDL_MapRGB(ecran->format, 237, 161, 55));
	SDL_FillRect(joueur, NULL, SDL_MapRGB(ecran->format, 58, 255, 77));
	SDL_FillRect(arrive, NULL, SDL_MapRGB(ecran->format, 228, 0, 8));
	SDL_FillRect(joueur_arrive, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
	SDL_FillRect(caisse_arrive, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
	
	SDL_Rect positionCase;
	
	int i,j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			positionCase.x=i*(largeur_fenetre/niveau.width);
			positionCase.y=j*(hauteur_fenetre/niveau.height);
			
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
}
