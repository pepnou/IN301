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
#include "deplacement.h"

int NBR_NIVEAUX = 0;

char* fichier_a_lire = "default.xsb";
char* fichier_pour_ecrire = "default.xsb";

int victoire(LEVEL niveau);

void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void menu_taille_lvl(SDL_Surface *ecran);
void creation_lvl(SDL_Surface *ecran,int width,int height);
void play_mode(SDL_Surface *ecran,int num_lvl);
LEVEL play_mode_invert(SDL_Surface *ecran,LEVEL lvl);
LEVEL play_mode_invert_auto(SDL_Surface *ecran,LEVEL lvl);
POS deplacement_aleatoire();

TOUR action(TOUR coup,Play_Event PE);
TOUR action_invert(TOUR coup,Play_Event PE);
void modif_niveau(LEVEL niveau,SDL_Surface *ecran);

void creation_fichier(char* nom);

int main(int argc, char** argv)
{
	creation_fichier(fichier_pour_ecrire);
		
	srand(time(NULL));
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
	SDL_Surface *ecran = NULL;
	
	SDL_WM_SetCaption("Sokoban vBeta1",NULL);
	
	gestion_ligne_commande(argc,argv,ecran);

	SDL_FreeSurface(ecran);
	
	TTF_Quit();
	SDL_Quit();
	
	exit(EXIT_SUCCESS);
}

void creation_fichier(char* nom)
{
	FILE* tmp;
	
	tmp = fopen(nom,"a+");
	
	fclose(tmp);
}

void menu_taille_lvl(SDL_Surface *ecran)
{
	int width = 3;
	int height = 3;
	
	SDL_Event event;
		
	affiche_menu_taille_lvl(&ecran,width,height);
	
	int continuer = 1;
	
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_RETURN:
						creation_lvl(ecran,width,height);
						continuer = 0;
						break;
					case SDLK_ESCAPE:
						continuer = 0;
						main_menu(ecran);
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(65,104,197,236,event))
				{
					if(width > 3) width --;
					affiche_menu_taille_lvl(&ecran,width,height);
				}
				if(position_clic_encadre(335,374,198,237,event))
				{
					if(width < 56) width ++;
					affiche_menu_taille_lvl(&ecran,width,height);
				}
				if(position_clic_encadre(65,104,267,306,event))
				{
					if(height > 3) height --;
					affiche_menu_taille_lvl(&ecran,width,height);
				}
				if(position_clic_encadre(335,374,268,307,event))
				{
					if(height < 30) height ++;
					affiche_menu_taille_lvl(&ecran,width,height);
				}
				if(position_clic_encadre(150,189,351,390,event))
				{
					continuer = 0;
					main_menu(ecran);
				}
				if(position_clic_encadre(250,289,351,390,event))
				{
					creation_lvl(ecran,width,height);
					continuer = 0;
				}
				break;
		}
	}
}

void creation_lvl(SDL_Surface *ecran,int width,int height)
{	
	LEVEL niveau;
	niveau.width=width;
	niveau.height=height;
	
	modif_niveau(init_lvl(niveau),ecran);
	
	main_menu(ecran);
}

void modif_niveau(LEVEL niveau,SDL_Surface *ecran)
{
	affichelvl(&ecran,niveau,2);
	
	SDL_Event event;
	int continuer = 1;
	int tmp_i,tmp_j;
	
	int position_bandeau = (ecran->w)/2 - 150;
	
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
					case SDLK_RETURN:
						if(lvl_correct(niveau))
						{
							niveau.joueur = recherche_joueur(niveau);
							enregistrer_lvl(niveau);
							
							continuer = 0;
						}
						break;
				}
				break;				
			case SDL_MOUSEBUTTONUP:
				if((position_clic_encadre(position_bandeau+8,position_bandeau+119,20+9,20+50,event))&&(lvl_correct(niveau)))
				{
					niveau.joueur = recherche_joueur(niveau);
					niveau = play_mode_invert_auto(ecran,niveau);
					niveau.direction_joueur = 1;
					affichelvl(&ecran,niveau,2);
				}
				if((position_clic_encadre(position_bandeau+121,position_bandeau+208,20+9,20+50,event))&&(lvl_correct(niveau)))
				{
					niveau.joueur = recherche_joueur(niveau);
					niveau = play_mode_invert(ecran,niveau);
					niveau.direction_joueur = 1;
					affichelvl(&ecran,niveau,2);
				}
				if(position_clic_encadre(position_bandeau+210,position_bandeau+250,20+10,20+49,event))
				{
					if(lvl_correct(niveau))
					{
						niveau.joueur = recherche_joueur(niveau);
						enregistrer_lvl(niveau);
						
						continuer = 0;
					}
				}
				if(position_clic_encadre(position_bandeau+252,position_bandeau+291,20+10,20+49,event))
				{
					continuer = 0;
				}
				if(position_clic_encadre(20,20+32*niveau.width,100,100+32*niveau.height,event))
				{
					tmp_i = (event.button.x-20)/32;
					tmp_j = (event.button.y-100)/32;
					
					niveau.T[tmp_i][tmp_j] = (niveau.T[tmp_i][tmp_j] + 1 ) % 7;
					
					affichelvl(&ecran,niveau,2);
				}
				break;
			default:
				break;
		}
	}
}

void main_menu(SDL_Surface *ecran)
{
	affiche_main_menu(&ecran);
	
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
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(110,429,160,279,event))
				{
					play_menu(ecran);
					continuer = 0;
				}
				if(position_clic_encadre(110,429,300,419,event))
				{
					menu_taille_lvl(ecran);
					continuer = 0;
				}
				break;
		}
	}
}

void play_menu(SDL_Surface *ecran)
{
	NBR_NIVEAUX = lecture_nbr_lvl();
	SDL_Event event;
	
	LEVEL lvl;
	
	if(NBR_NIVEAUX == 0)
	{
		affiche_play_menu(&ecran,NBR_NIVEAUX);
		SDL_Delay(2000);
		main_menu(ecran);
	}
	else
	{
		int niveau_a_lire = 1;
		
		affiche_play_menu(&ecran,niveau_a_lire);
		
		int continuer = 1;
		
		while(continuer)
		{
			SDL_WaitEvent(&event);
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_RETURN:
							play_mode(ecran,niveau_a_lire);
							continuer = 0;
							break;
						case SDLK_ESCAPE:
							continuer = 0;
							main_menu(ecran);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(position_clic_encadre(35,104,197,236,event))
					{
						if(niveau_a_lire>1) niveau_a_lire --;
						affiche_play_menu(&ecran,niveau_a_lire);
					}
					if(position_clic_encadre(335,375,198,237,event))
					{
						if(niveau_a_lire<NBR_NIVEAUX) niveau_a_lire ++;
						affiche_play_menu(&ecran,niveau_a_lire);
					}
					if(position_clic_encadre(150,189,281,320,event))
					{
						continuer = 0;
						main_menu(ecran);
					}
					if(position_clic_encadre(250,289,281,320,event))
					{
						play_mode(ecran,niveau_a_lire);
						continuer = 0;
					}
					break;
			}
		}
	}
}

void play_mode(SDL_Surface *ecran,int num_lvl)
{	
	TOUR coup;
	coup = init_tour(coup,num_lvl);
	Play_Event evenement;
	
	affichelvl(&ecran,coup.fait -> val,0);
	
	while((coup.continuer) && (!(victoire(coup.fait -> val))))
	{
		evenement = attendre_evenement(coup.fait -> val,ecran);
		coup = action(coup,evenement);
		affichelvl(&ecran,coup.fait -> val,0);
	}
	if(evenement.event == E_QUIT) main_menu(ecran);
	else if(coup.num_level < NBR_NIVEAUX) play_mode(ecran,coup.num_level + 1);
	else main_menu(ecran);
}

LEVEL play_mode_invert(SDL_Surface *ecran,LEVEL lvl)
{	
	TOUR coup;
	Play_Event evenement;
	
	coup = init_tour_invert(coup,lvl);
	
	affichelvl(&ecran,coup.fait -> val,1);
	
	while(coup.continuer)
	{
		evenement = attendre_evenement_invert(coup.fait -> val,ecran);
		coup = action_invert(coup,evenement);
		affichelvl(&ecran,coup.fait -> val,1);
	}
	if(evenement.event == E_CONFIRM) return (coup.fait -> val);
	else return lvl;
}

LEVEL play_mode_invert_auto(SDL_Surface *ecran,LEVEL lvl)
{	
	TOUR coup;
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	coup = init_tour_invert(coup,lvl);
	
	int i;
	
	for(i=0;i<50;i++)
	{
		evenement.deplacement = deplacement_aleatoire();
		coup = action_invert(coup,evenement);
	}
	return (coup.fait -> val);
}

POS deplacement_aleatoire()
{
	int tmp = rand() % 4;
	POS deplacement;
	deplacement.x = 0;deplacement.y = 0;
	switch(tmp)
	{
		case 0:
			deplacement.y=-1;
			break;
		case 1:
			deplacement.y=1;
			break;
		case 2:
			deplacement.x=1;
			break;
		case 3:
			deplacement.x=-1;
			break;
	}
	return deplacement;
}

int victoire(LEVEL niveau)
{
	int i,j;
	
	for(i=1;i<niveau.width-1;i++)
	{
		for(j=1;j<niveau.height-1;j++)
		{
			if((niveau.T[i][j] == ARRIVE)||(niveau.T[i][j] == JOUEUR_ARRIVE))return 0;
		}
	}
	return 1;
}

TOUR action(TOUR coup,Play_Event PE)
{
	switch(PE.event)
	{
		case E_MOVE:
			coup.fait = insere_debut(coup.fait,deplacer_joueur(coup.fait -> val, PE.deplacement));
			suppr_liste(coup.deplace);
			coup.deplace = NULL;
			break;
		case E_UNDO:
			if(coup.fait ->suiv != NULL) coup.deplace = insere_debut(coup.deplace,suppr_debut(&(coup.fait)));
			break;
		case E_REDO:
			if(coup.deplace != NULL) coup.fait = insere_debut(coup.fait,suppr_debut(&(coup.deplace)));
			break;
		case E_INIT:
			while(coup.fait -> suiv != NULL) coup.deplace = insere_debut(coup.deplace,suppr_debut(&(coup.fait)));
			break;
		case E_PREVIOUS:
			if(coup.num_level > 1) coup = init_tour(coup,coup.num_level-1);
			break;
		case E_NEXT:
			if(coup.num_level < NBR_NIVEAUX) coup = init_tour(coup,coup.num_level+1);
			break;
		case E_QUIT:
			coup.continuer = 0;
			break;
	}
	return coup;
}

TOUR action_invert(TOUR coup,Play_Event PE)
{
	switch(PE.event)
	{
		case E_MOVE:
			coup.fait = insere_debut(coup.fait,deplacer_joueur_invert(coup.fait -> val, PE.deplacement));
			suppr_liste(coup.deplace);
			coup.deplace = NULL;
			break;
		case E_UNDO:
			if(coup.fait ->suiv != NULL) coup.deplace = insere_debut(coup.deplace,suppr_debut(&(coup.fait)));
			break;
		case E_REDO:
			if(coup.deplace != NULL) coup.fait = insere_debut(coup.fait,suppr_debut(&(coup.deplace)));
			break;
		case E_INIT:
			while(coup.fait -> suiv != NULL) coup.deplace = insere_debut(coup.deplace,suppr_debut(&(coup.fait)));
			break;
		case E_PREVIOUS:
			if(coup.num_level > 1) coup = init_tour(coup,coup.num_level-1);
			break;
		case E_NEXT:
			if(coup.num_level < NBR_NIVEAUX) coup = init_tour(coup,coup.num_level+1);
			break;
		case E_QUIT:
			coup.continuer = 0;
			break;
		case E_CONFIRM:
			coup.continuer = 0;
			break;
	}
	
	return coup;
}


