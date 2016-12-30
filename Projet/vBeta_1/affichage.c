#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"



void affichelvl(SDL_Surface **ecran,LEVEL niveau,int invert)
{
	int largeur = niveau.width*32 + 40;
	int hauteur = niveau.height*32 + 120;
	
	*ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
	SDL_Surface *vide = SDL_LoadBMP("parquet_32.bmp");
	SDL_Surface *mur = SDL_LoadBMP("mur_haut_32.bmp");
	SDL_Surface *caisse = SDL_LoadBMP("caisse_2.bmp");
	SDL_Surface *arrive = SDL_LoadBMP("tapis.bmp");
	SDL_Surface *caisse_arrive = SDL_LoadBMP("caisse_2_arrive.bmp");
	
	SDL_Surface *joueur = NULL;
	SDL_Surface *bandeau = NULL;
	
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
	
	
	SDL_Surface *fond = NULL;
	
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
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
				default :
					printf("you forgot to blit a surface");
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
}


/*
void affiche_play_menu(SDL_Surface **ecran,int lvl_num)
{
	*ecran = SDL_SetVideoMode(540,440,32,SDL_HWSURFACE);
	
	SDL_Surface *plus = SDL_LoadBMP("bouton_plus.bmp");
	SDL_Surface *moins = SDL_LoadBMP("bouton_moins.bmp");
	SDL_Surface *validation = SDL_LoadBMP("bouton_okay.bmp");
	SDL_Surface *retour = SDL_LoadBMP("bouton_nope.bmp");
	
	SDL_SetColorKey(plus, SDL_SRCCOLORKEY, SDL_MapRGB(plus->format, 255, 0, 0));
	SDL_SetColorKey(moins, SDL_SRCCOLORKEY, SDL_MapRGB(moins->format, 255, 0, 0));
	SDL_SetColorKey(validation, SDL_SRCCOLORKEY, SDL_MapRGB(validation->format, 255, 0, 0));
	SDL_SetColorKey(retour, SDL_SRCCOLORKEY, SDL_MapRGB(retour->format, 255, 0, 0));

	SDL_Surface *fond = NULL;
	
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, (*ecran) -> w, (*ecran) -> h, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB((*ecran) -> format, COULEUR_FOND));
	
	SDL_Rect position;
	position.x=0;
	positionC.y=0;
	
	SDL_BlitSurface(fond,NULL,*ecran,&position);
	
	SDL_Surface *texte = NULL;
	
    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",30);

    SDL_Color couleurnoire = {0,0,0};

	if(lvl_num == 0)
    {
		texte = TTF_RenderText_Blended(police,"aucun niveau dispo",couleurnoire);
		
		position.x = ((*ecran) -> w) - (18/2 * 30/2);
		position.y = ((*ecran) -> h)/2 - 15;
		
		SDL_BlitSurface(texte,NULL,*ecran,&position);
	}
	
	else
	{
		texte = TTF_RenderText_Blended(police,"Niveau :",couleurnoire);

		position.x = ((*ecran) -> w) - (8/2 * 30/2);
		position.y = 20;

		SDL_BlitSurface(texte,NULL,*ecran,&position);
		
		positionCase.x = 0;
		positionCase.y = 0;
		
		SDL_BlitSurface(plus,NULL,*ecran,&position);
		
		positionCase.x = 0;
		positionCase.y = 0;
		
		SDL_BlitSurface(moins,NULL,*ecran,&position);
		
		positionCase.x = 0;
		positionCase.y = 0;
		
		SDL_BlitSurface(validation,NULL,*ecran,&position);
		
		positionCase.x = 0;
		positionCase.y = 0;
		
		SDL_BlitSurface(retour,NULL,*ecran,&position);
		
		char Tmp[10] = "";
		sprintf(Tmp,"%d",lvl_num);
		texte = TTF_RenderText_Blended(police,Tmp,couleurnoire);
		
		position.x = largeur_fenetre/2 - 15;
		position.y = 20*2 + 30;

		SDL_BlitSurface(texte,NULL,*ecran,&position);
	}
	
	
	SDL_Flip(*ecran);
	
	SDL_FreeSurface(plus);
	SDL_FreeSurface(moins);
	SDL_FreeSurface(validation);
	SDL_FreeSurface(retour);
}
*/

void affiche_play_menu(SDL_Surface **ecran,int lvl_num)
{
	SDL_Surface *menu = NULL;
	
	SDL_Rect position;
	position.x=0;
	position.y=0;
	
	if(lvl_num == 0)
    {
		menu = SDL_LoadBMP("play_menu.bmp");
		
		*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
		
		SDL_BlitSurface(menu,NULL,*ecran,&position);
	}
	
	else
	{
		menu = SDL_LoadBMP("play_menu.bmp");
		
		*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
		
		SDL_BlitSurface(menu,NULL,*ecran,&position);
		
		
		SDL_Surface *texte = NULL;
		
		TTF_Font *police = TTF_OpenFont("unispace_rg.ttf",30);
		SDL_Color couleurnoire = {0,0,0};
		
		char Tmp[10] = "";
		sprintf(Tmp,"%d",lvl_num);
		texte = TTF_RenderText_Blended(police,Tmp,couleurnoire);
		
		position.x = 152 + 50;
		position.y = 202;

		SDL_BlitSurface(texte,NULL,*ecran,&position);
	}
	
	SDL_Flip(*ecran);
}

/*
void affiche_main_menu(SDL_Surface **ecran)
{
	*ecran = SDL_SetVideoMode(540,440,32,SDL_HWSURFACE);
	
	SDL_Surface *titre = SDL_LoadBMP("titre.bmp");
	SDL_Surface *jouer = SDL_LoadBMP("boutons_menu_jouer.bmp");
	SDL_Surface *creer = SDL_LoadBMP("boutons_menu_creer_niveau.bmp");
	
	SDL_SetColorKey(jouer, SDL_SRCCOLORKEY, SDL_MapRGB(jouer->format, 255, 0, 0));
	SDL_SetColorKey(creer, SDL_SRCCOLORKEY, SDL_MapRGB(creer->format, 255, 0, 0));
	
	SDL_Surface *fond = NULL;
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, (*ecran) -> w, (*ecran) -> h, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB((*ecran)->format, COULEUR_FOND));
	
	SDL_Rect positionCase;
	
	positionCase.x = 0;
	positionCase.y = 0;
	
	SDL_BlitSurface(fond,NULL,*ecran,&positionCase);

    positionCase.x = 20;
	positionCase.y = 20 * 1 + 120 * 0;
	
	SDL_BlitSurface(titre,NULL,*ecran,&positionCase);
	
	positionCase.x = 20 + 500/2 - 320/2;
	positionCase.y = 20 * 2 + 120 * 1;
	
	SDL_BlitSurface(jouer,NULL,*ecran,&positionCase);
	
	positionCase.x = 20 + 500/2 - 320/2;
	positionCase.y = 20 * 3 + 120 * 2;
	
	SDL_BlitSurface(creer,NULL,*ecran,&positionCase);
    
	SDL_Flip(*ecran);
	
	SDL_FreeSurface(fond);
	SDL_FreeSurface(titre);
	SDL_FreeSurface(jouer);
	SDL_FreeSurface(creer);
}
*/

void affiche_main_menu(SDL_Surface **ecran)
{
	SDL_Surface *menu = SDL_LoadBMP("main_menu.bmp");
	*ecran = SDL_SetVideoMode(menu -> w,menu -> h,32,SDL_HWSURFACE);
	
	SDL_Rect position;
	position.x=0;
	position.y=0;
	
	SDL_BlitSurface(menu,NULL,*ecran,&position);
	
	SDL_Flip(*ecran);
}




