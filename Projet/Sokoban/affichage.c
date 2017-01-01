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

void affiche_image(char* nom_image,int x,int y,SDL_Surface *ecran)
{
	SDL_Rect positionCase;
	
	positionCase.x = x;
	positionCase.y = y;
	
	SDL_Surface *image = SDL_LoadBMP(nom_image);
	
	SDL_BlitSurface(image,NULL,ecran,&positionCase);
	
	SDL_FreeSurface(image);
}

void affiche_image_2(char* nom_image,int x,int y,int rouge,int vert,int bleu,SDL_Surface *ecran)
{
	SDL_Rect positionCase;
	
	positionCase.x = x;
	positionCase.y = y;
	
	SDL_Surface *image = SDL_LoadBMP(nom_image);
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, rouge, vert, bleu));
	
	SDL_BlitSurface(image,NULL,ecran,&positionCase);
	
	SDL_FreeSurface(image);
}

void affiche_fond(int rouge,int vert,int bleu,SDL_Surface *ecran)
{
	SDL_Rect positionCase;
	
	positionCase.x = 0;
	positionCase.y = 0;
	
	SDL_Surface *fond = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w, ecran->h, 32, 0, 0, 0, 0);;
	
	SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, rouge,vert,bleu));
	
	SDL_BlitSurface(fond,NULL,ecran,&positionCase);
	
	SDL_FreeSurface(fond);
}

char* selection_image_joueur(int direction_joueur)
{
	switch(direction_joueur)
	{
		case -2:
			return "perso1_gauche.bmp";
			break;
		case -1:
			return "perso1_haut.bmp";
			break;
		case 2:
			return "perso1_droite.bmp";
			break;
		case 1:
			return "perso1_bas.bmp";
			break;
	}
	return "perso1_bas.bmp";
}

void affiche_interface(int invert,int x,int y,SDL_Surface *ecran)
{
	switch(invert)
	{
		case 0:
			affiche_image_2("interface_mode_jeu.bmp",x,y,255,0,0,ecran);
			break;
		case 1:
			affiche_image_2("interface_mode_jeu_invert.bmp",x,y,255,0,0,ecran);
			break;
		case 2:
			affiche_image_2("interface_mode_creation.bmp",x,y,255,0,0,ecran);
			break;
	}
}

void affiche_grille_niveau(SDL_Surface *ecran,LEVEL niveau)
{
	int case_x, case_y, i, j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			case_x=i*32 + 20;
			case_y=j*32 + 100;
			switch(niveau.T[i][j])
			{
				case VIDE:
					affiche_image("parquet_32.bmp",case_x,case_y,ecran);
					break;
				case MUR:
					affiche_image("mur_haut_32.bmp",case_x,case_y,ecran);
					break;
				case CAISSE:
					affiche_image("caisse_2.bmp",case_x,case_y,ecran);
					break;
				case JOUEUR:
					affiche_image("parquet_32.bmp",case_x,case_y,ecran);
					affiche_image_2(selection_image_joueur(niveau.direction_joueur),case_x,case_y,255,255,0,ecran);
					break;
				case ARRIVE:
					affiche_image("tapis.bmp",case_x,case_y,ecran);
					break;
				case JOUEUR_ARRIVE:
					affiche_image("tapis.bmp",case_x,case_y,ecran);
					affiche_image_2(selection_image_joueur(niveau.direction_joueur),case_x,case_y,255,255,0,ecran);
					break;
				case CAISSE_ARRIVE:
					affiche_image("caisse_2_arrive.bmp",case_x,case_y,ecran);
					break;
			}
		}
	}
}

void affichelvl(SDL_Surface **ecran,LEVEL niveau,int invert)
{
	int largeur = niveau.width*32 + 40;
	int hauteur = niveau.height*32 + 120;
	if(largeur<340) largeur = 340;
	
	*ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
	
	affiche_fond(COULEUR_FOND,*ecran);
	
	affiche_interface(invert,largeur/2 - 150,20,*ecran);
	
	affiche_grille_niveau(*ecran,niveau);
	
	SDL_Flip(*ecran);
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












