#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"


void affiche_entier(int entier,int x,int y,SDL_Surface *ecran)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	
	TTF_Font *police = TTF_OpenFont("unispace_rg.ttf",30);
	SDL_Color couleurnoire = {0,0,0};
	
	char Tmp[10] = "";
	sprintf(Tmp,"%d",entier);
	
	SDL_Surface *surface_texte = TTF_RenderText_Blended(police,Tmp,couleurnoire);
	
	SDL_BlitSurface(surface_texte,NULL,ecran,&position);
	
	SDL_Flip(ecran);
	
	TTF_CloseFont(police);
	SDL_FreeSurface(surface_texte);
}

void affiche_texte(char* texte,int x,int y,SDL_Surface *ecran)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	
	TTF_Font *police = TTF_OpenFont("unispace_rg.ttf",30);
	SDL_Color couleurnoire = {0,0,0};
	
	SDL_Surface *surface_texte = TTF_RenderText_Blended(police,texte,couleurnoire);
	
	SDL_BlitSurface(surface_texte,NULL,ecran,&position);
	
	SDL_Flip(ecran);
	
	TTF_CloseFont(police);
	SDL_FreeSurface(surface_texte);
}

void affichelvl(SDL_Surface **ecran,LEVEL niveau,int invert)
{
	int largeur = niveau.width*32 + 40;
	int hauteur = niveau.height*32 + 120;
	if(largeur<340) largeur = 340;
	
	*ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
	SDL_Surface *vide = SDL_LoadBMP("parquet_32.bmp");
	SDL_Surface *mur = SDL_LoadBMP("mur_haut_32.bmp");
	SDL_Surface *caisse = SDL_LoadBMP("caisse_2.bmp");
	SDL_Surface *arrive = SDL_LoadBMP("tapis.bmp");
	SDL_Surface *caisse_arrive = SDL_LoadBMP("caisse_2_arrive.bmp");
	
	SDL_Surface *joueur = NULL;
	SDL_Surface *bandeau = NULL;
	
	SDL_Surface *fond = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);;
	
	switch(niveau.direction_joueur)
	{
		case -2:
			joueur = SDL_LoadBMP("perso1_gauche.bmp");
			break;
		case -1:
			joueur = SDL_LoadBMP("perso1_haut.bmp");
			break;
		case 2:
			joueur = SDL_LoadBMP("perso1_droite.bmp");
			break;
		case 1:
			joueur = SDL_LoadBMP("perso1_bas.bmp");
			break;
	}

	switch(invert)
	{
		case 0:
			bandeau = SDL_LoadBMP("interface_mode_jeu.bmp");
			break;
		case 1:
			bandeau = SDL_LoadBMP("interface_mode_jeu_invert.bmp");
			break;
		case 2:
			bandeau = SDL_LoadBMP("interface_mode_creation.bmp");
			break;
	}
	SDL_FillRect(fond, NULL, SDL_MapRGB((*ecran)->format, COULEUR_FOND));
	
	SDL_SetColorKey(joueur, SDL_SRCCOLORKEY, SDL_MapRGB(joueur->format, 255, 255, 0));
	SDL_SetColorKey(bandeau, SDL_SRCCOLORKEY, SDL_MapRGB(bandeau->format, 255, 0, 0));
	
	SDL_Rect positionCase;
	
	positionCase.x = 0;
	positionCase.y = 0;
	
	SDL_BlitSurface(fond,NULL,*ecran,&positionCase);
	
	positionCase.x = largeur/2 - (bandeau -> w)/2;
	positionCase.y = 20;
	
	SDL_BlitSurface(bandeau,NULL,*ecran,&positionCase);
	
	int i,j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			positionCase.x=i*32 + 20;
			positionCase.y=j*32 + 100;
			
			switch(niveau.T[i][j])
			{
				case VIDE:
					SDL_BlitSurface(vide,NULL,*ecran,&positionCase);
					break;
				case MUR:
					SDL_BlitSurface(mur,NULL,*ecran,&positionCase);
					break;
				case CAISSE:
					SDL_BlitSurface(caisse,NULL,*ecran,&positionCase);
					break;
				case JOUEUR:
					SDL_BlitSurface(vide,NULL,*ecran,&positionCase);
					SDL_BlitSurface(joueur,NULL,*ecran,&positionCase);
					break;
				case ARRIVE:
					SDL_BlitSurface(arrive,NULL,*ecran,&positionCase);
					break;
				case JOUEUR_ARRIVE:
					SDL_BlitSurface(arrive,NULL,*ecran,&positionCase);
					SDL_BlitSurface(joueur,NULL,*ecran,&positionCase);
					break;
				case CAISSE_ARRIVE:
					SDL_BlitSurface(caisse_arrive,NULL,*ecran,&positionCase);
					break;
			}
		}
	}
	
	SDL_Flip(*ecran);
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(joueur);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(arrive);
	SDL_FreeSurface(caisse_arrive);
	SDL_FreeSurface(fond);
	SDL_FreeSurface(bandeau);
}

void affiche_play_menu(SDL_Surface **ecran,int lvl_num)
{
	SDL_Surface *menu = NULL;
	
	SDL_Rect position;
	position.x=0;
	position.y=0;
	
	if(lvl_num == 0)
    {
		menu = SDL_LoadBMP("boutons_menu_niveau_indisponible.bmp");
		*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
		SDL_BlitSurface(menu,NULL,*ecran,&position);
	}
	else
	{
		menu = SDL_LoadBMP("play_menu.bmp");
		*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
		SDL_BlitSurface(menu,NULL,*ecran,&position);
		affiche_entier(lvl_num,152+50,202,*ecran);
	}
	SDL_Flip(*ecran);
	SDL_FreeSurface(menu);
}

void affiche_main_menu(SDL_Surface **ecran)
{
	SDL_Surface *menu = SDL_LoadBMP("main_menu.bmp");
	*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
	
	SDL_Rect position;
	position.x=0;
	position.y=0;
	
	SDL_BlitSurface(menu,NULL,*ecran,&position);
	
	SDL_Flip(*ecran);
	
	SDL_FreeSurface(menu);
}

void affiche_menu_taille_lvl(SDL_Surface **ecran, int width, int height)
{
	SDL_Surface *menu = NULL;
	
	SDL_Rect position;
	position.x=0;
	position.y=0;
	
	menu = SDL_LoadBMP("creation_menu.bmp");
	*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
	SDL_BlitSurface(menu,NULL,*ecran,&position);
	
	affiche_entier(width,153+50,200,*ecran);
	affiche_entier(height,153+50,270,*ecran);

	SDL_Flip(*ecran);
	SDL_FreeSurface(menu);
}












