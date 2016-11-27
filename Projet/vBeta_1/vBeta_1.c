#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"
#include "manipulation_liste.h"

int NBR_NIVEAUX = 0;

LEVEL init_lvl(LEVEL niveau);
void creation_lvl(SDL_Surface *ecran);

int victoire(LEVEL niveau);

void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void editor_menu(SDL_Surface *ecran);
void play_mode(SDL_Surface *ecran,int num_lvl);

LEVEL deplacer_joueur(LEVEL niveau,POS deplacement);
Play_Event attendre_evenement();
TOUR action(TOUR coup,Play_Event PE);

int lvl_correct(LEVEL lvl);
int* contenu_lvl(LEVEL lvl);
POS recherche_joueur(LEVEL lvl);
int joueur_encadre(LEVEL lvl,int x,int y);

int main()
{	
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	main_menu(ecran);
	
	exit(EXIT_SUCCESS);
}

void creation_lvl(SDL_Surface *ecran)
{	
	LEVEL niveau;
	niveau.width=10;
	niveau.height=10;
	
	niveau = init_lvl(niveau);
	
	affichelvl(ecran,niveau);
	
	SDL_Event event;
	int continuer = 1;
	int tmp_i,tmp_j;
	
	
	while(continuer)
	{
		
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_RETURN:
						if(lvl_correct(niveau))
						{
							niveau.joueur = recherche_joueur(niveau);
							enregistrer_lvl(niveau);
							continuer = 0;
							
						}
						break;
					case SDLK_ESCAPE:
						continuer = 0;
						break;
				}
				break;				
			case SDL_MOUSEBUTTONUP:
				tmp_i = event.button.x/(largeur_fenetre/niveau.width);
				tmp_j = event.button.y/(hauteur_fenetre/niveau.height);
				
				niveau.T[tmp_i][tmp_j] = (niveau.T[tmp_i][tmp_j] + 1 ) % 7;
				//~ if(niveau.T[tmp_i][tmp_j] == JOUEUR)
				//~ {
					//~ niveau.joueur.x = tmp_i;
					//~ niveau.joueur.y = tmp_j;
				//~ }
				
				affichelvl(ecran,niveau);
				break;
			default:
				break;
		}
	}
	main_menu(ecran);
}

POS recherche_joueur(LEVEL lvl)
{
	POS res;
	int i,j;
	
	for(i=0;i<lvl.width;i++)
	{
		for(j=0;j<lvl.height;j++)
		{
			if(lvl.T[i][j]== JOUEUR)
			{
				res.x = i;
				res.y = j;
			}
		}
	}
	
	return res;
}

int lvl_correct(LEVEL lvl)
{
	int correct = 1;
	POS pos_j;
	
	int* contenu = NULL;
	contenu = contenu_lvl(lvl);
	
	if(contenu[JOUEUR] != 1)
	{
		printf("probleme sur le nombre de joueur : %d joueur(s)\n",contenu[JOUEUR]);
		correct = 0;
	}
	if(contenu[ARRIVE] == 0)
	{
		printf("probleme : aucune zone de depot\n");
		correct = 0;
	}
	if(contenu[ARRIVE] + contenu[JOUEUR_ARRIVE] > contenu[CAISSE])
	{
		printf("probleme sur le nombre de zone de depot et de caisse : %d depot(s) pour %d caisse\n",contenu[ARRIVE] + contenu[JOUEUR_ARRIVE],contenu[CAISSE]);
		correct = 0;
	}
	if(contenu[JOUEUR] == 1)
	{
		pos_j = recherche_joueur(lvl);
		if(!(joueur_encadre(lvl,pos_j.x,pos_j.y)))
		{
			printf("probleme :le joueur n est pas encadré par des murs\n");
			correct = 0;
		}
	}
	
	return correct;
}

int joueur_encadre(LEVEL lvl,int x,int y)
{	
	return joueur_encadre_etape_2(&lvl,x,y);
}

int joueur_encadre_etape_2(LEVEL* lvl,int x,int y)
{	
	if((x == 0)||(x == (*lvl).width-1)) return 0;
	if((y == 0)||(y == (*lvl).height-1)) return 0;
	
	if((*lvl).T[x][y] == MUR) return 1;
	
	(*lvl).T[x][y] = MUR;
	
	return((joueur_encadre_etape_2(lvl,x-1,y))&(joueur_encadre_etape_2(lvl,x+1,y))&(joueur_encadre_etape_2(lvl,x,y-1))&(joueur_encadre_etape_2(lvl,x,y+1)));
}

int* contenu_lvl(LEVEL lvl)
{
	int* content;
	
	if(!(content = calloc(7 , sizeof(int)))) exit(EXIT_FAILURE);
	
	int i,j;
	
	for(i=0;i<lvl.width;i++)
	{
		for(j=0;j<lvl.height;j++)
		{
			content[lvl.T[i][j]]++;
		}
	}
	
	return content;
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
	affiche_main_menu(ecran);
	
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
						
					case SDLK_c:
						efface_lvl();
						break;
						
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if(encadrement(event.button.x,0,largeur_fenetre/2))
				{
					play_menu(ecran);
					continuer = 0;
				}
				else
				{
					creation_lvl(ecran);
					continuer = 0;
					//editor_menu(ecran);
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
		affiche_play_menu(ecran,NBR_NIVEAUX);
		SDL_Delay(2000);
		main_menu(ecran);
	}
	else
	{
		int niveau_a_lire = 1;
		
		affiche_play_menu(ecran,niveau_a_lire);
		
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
					if(encadrement(event.button.x,0,largeur_fenetre/2))
					{
						if(niveau_a_lire>1) niveau_a_lire --;
					}
					else
					{
						if(niveau_a_lire<NBR_NIVEAUX) niveau_a_lire ++;
					}
					
					affiche_play_menu(ecran,niveau_a_lire);
					break;
			}
		}
	}
}

void play_mode(SDL_Surface *ecran,int num_lvl)
{
	TOUR coup;
	
	
	coup = init_tour(coup,num_lvl);
	
	
	affichelvl(ecran,coup.fait -> val);
	
	
	while(coup.continuer)
	{
		coup.continuer = (victoire(coup.fait -> val) + 1) % 2;
		
		coup = action(coup,attendre_evenement());
		affichelvl(ecran,coup.fait -> val);
	}
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

LEVEL deplacer_joueur(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	switch(niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y])
	{
		case VIDE:
			niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
			niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
			niveau.joueur.x=niveau.joueur.x + deplacement.x;
			niveau.joueur.y=niveau.joueur.y + deplacement.y;
			break;
		case CAISSE:
			switch(niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y])
			{
				case VIDE:
					niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
					niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE;
					niveau.joueur.x=niveau.joueur.x + deplacement.x;
					niveau.joueur.y=niveau.joueur.y + deplacement.y;
					break;
				case ARRIVE:
					niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
					niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE_ARRIVE;
					niveau.joueur.x=niveau.joueur.x + deplacement.x;
					niveau.joueur.y=niveau.joueur.y + deplacement.y;
					break;
			}
			break;
		case CAISSE_ARRIVE:
			switch(niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y])
			{
				case VIDE:
					niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
					niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE;
					niveau.joueur.x=niveau.joueur.x + deplacement.x;
					niveau.joueur.y=niveau.joueur.y + deplacement.y;
					break;
				case ARRIVE:
					niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
					niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE_ARRIVE;
					niveau.joueur.x=niveau.joueur.x + deplacement.x;
					niveau.joueur.y=niveau.joueur.y + deplacement.y;
					break;
			}
			break;
		case ARRIVE:
			niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
			niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
			niveau.joueur.x=niveau.joueur.x + deplacement.x;
			niveau.joueur.y=niveau.joueur.y + deplacement.y;
			break;
	}
	return niveau;
}

Play_Event attendre_evenement()
{
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event action;
	int continuer=1;
	
	
	while(continuer)
	{
		SDL_WaitEvent(&action);
		if(action.type==SDL_KEYDOWN)
        {
			switch(action.key.keysym.sym)
            {
				case SDLK_UP:
					continuer = 0;
					evenement.deplacement.y=-1;
					evenement.deplacement.x=0;
					break;
				case SDLK_DOWN:
                    continuer = 0;
                    evenement.deplacement.y=1;
                    evenement.deplacement.x=0;
                    break;
				case SDLK_RIGHT:
                    continuer = 0;
                    evenement.deplacement.x=1;
                    evenement.deplacement.y=0;
                    break;
                case SDLK_LEFT:
                    continuer = 0;
                    evenement.deplacement.x=-1;
                    evenement.deplacement.y=0;
                    break;
				case SDLK_u:
					continuer = 0;
					evenement.event = E_UNDO;
					break;
				case SDLK_r:
					continuer = 0;
					evenement.event = E_REDO;
					break;
				case SDLK_i:
					continuer = 0;
					evenement.event = E_INIT;
					break;
				case SDLK_p:
					continuer = 0;
					evenement.event = E_PREVIOUS;
					break;
				case SDLK_s:
					continuer = 0;
					evenement.event = E_NEXT;
					break;
				case SDLK_q: case SDLK_ESCAPE:
					continuer = 0;
					evenement.event = E_QUIT;
					break;
            }
		}
	}
	
	return evenement;
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
			coup.fait = insere_debut(coup.fait,coup.base_lvl);
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















