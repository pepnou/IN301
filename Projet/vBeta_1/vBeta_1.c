#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "constantes.h"
#include "gestion_event.h"
#include "affichage.h"
#include "lecture_ecriture.h"
#include "manipulation_liste.h"

int NBR_NIVEAUX = 0;
int largeur_fenetre = 300;
int hauteur_fenetre = 150;

void creation_lvl(SDL_Surface *ecran);

int victoire(LEVEL niveau);

void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void editor_menu(SDL_Surface *ecran);
void play_mode(SDL_Surface *ecran,int num_lvl);
LEVEL play_mode_invert(SDL_Surface *ecran,LEVEL lvl);
LEVEL play_mode_invert_auto(SDL_Surface *ecran,LEVEL lvl);

LEVEL deplacer_joueur(LEVEL niveau,POS deplacement);
LEVEL deplacer_joueur_invert(LEVEL niveau,POS deplacement);
Play_Event attendre_evenement(LEVEL niveau);
Play_Event attendre_evenement_invert(LEVEL niveau);
TOUR action(TOUR coup,Play_Event PE);
TOUR action_invert(TOUR coup,Play_Event PE);
void modif_niveau(LEVEL niveau,SDL_Surface *ecran);

int lvl_correct(LEVEL lvl);
int* contenu_lvl(LEVEL lvl);
POS recherche_joueur(LEVEL lvl);
int joueur_encadre(LEVEL lvl,int x,int y);
int joueur_encadre_etape_2(LEVEL* lvl,int x,int y);

int main()
{
	srand(time(NULL));
	
	SDL_Surface *ecran = NULL;

	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_Init(SDL_INIT_AUDIO);
	
	SDL_WM_SetCaption("Sokoban vBeta1",NULL);
	
	main_menu(ecran);
	
	SDL_FreeSurface(ecran);
	
	SDL_Quit();
	
	exit(EXIT_SUCCESS);
}

void creation_lvl(SDL_Surface *ecran)
{	
	LEVEL niveau;
	niveau.width=10;
	niveau.height=10;
	
	modif_niveau(init_lvl(niveau),ecran);
	
	main_menu(ecran);
}

void modif_niveau(LEVEL niveau,SDL_Surface *ecran)
{
	affichelvl(&ecran,niveau,2);
	
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
				if((position_clic_encadre(20+8,20+119,20+9,20+50,event))&&(lvl_correct(niveau)))
				{
					niveau.joueur = recherche_joueur(niveau);
					niveau = play_mode_invert_auto(ecran,niveau);
					niveau.direction_joueur = 1;
					affichelvl(&ecran,niveau,2);
				}
				if((position_clic_encadre(20+121,20+208,20+9,20+50,event))&&(lvl_correct(niveau)))
				{
					niveau.joueur = recherche_joueur(niveau);
					niveau = play_mode_invert(ecran,niveau);
					niveau.direction_joueur = 1;
					affichelvl(&ecran,niveau,2);
				}
				if(position_clic_encadre(20+210,20+250,20+10,20+49,event))
				{
					if(lvl_correct(niveau))
					{
						niveau.joueur = recherche_joueur(niveau);
						enregistrer_lvl(niveau);
						
						continuer = 0;
					}
				}
				if(position_clic_encadre(20+252,20+291,20+10,20+49,event))
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

POS recherche_joueur(LEVEL lvl)
{
	POS res;
	int i,j;
	
	for(i=0;i<lvl.width;i++)
	{
		for(j=0;j<lvl.height;j++)
		{
			if((lvl.T[i][j]== JOUEUR)||(lvl.T[i][j]== JOUEUR_ARRIVE))
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
	
	if(contenu[JOUEUR] + contenu[JOUEUR_ARRIVE] != 1)
	{
		printf("probleme sur le nombre de joueur : %d joueur(s)\n",contenu[JOUEUR]);
		correct = 0;
	}
	if(contenu[ARRIVE] +  contenu[JOUEUR_ARRIVE] + contenu[CAISSE_ARRIVE] == 0)
	{
		printf("probleme : aucune zone de depot\n");
		correct = 0;
	}
	if(contenu[ARRIVE] + contenu[JOUEUR_ARRIVE] > contenu[CAISSE])
	{
		printf("probleme sur le nombre de zone de depot et de caisse : %d depot(s) pour %d caisse\n",contenu[ARRIVE] + contenu[JOUEUR_ARRIVE],contenu[CAISSE]);
		correct = 0;
	}
	if(contenu[JOUEUR] + contenu[JOUEUR_ARRIVE] == 1)
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
	if((*lvl).T[x][y] == MUR) return 1;
	
	if((x == 0)||(x == (*lvl).width-1)) return 0;
	if((y == 0)||(y == (*lvl).height-1)) return 0;
	
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
					creation_lvl(ecran);
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
	
	
	affichelvl(&ecran,coup.fait -> val,0);
	
	
	while((coup.continuer) && (!(victoire(coup.fait -> val))))
	{
		coup = action(coup,attendre_evenement(coup.fait -> val));
		affichelvl(&ecran,coup.fait -> val,0);
	}
}

LEVEL play_mode_invert(SDL_Surface *ecran,LEVEL lvl)
{	
	TOUR coup;
	Play_Event evenement;
	
	coup = init_tour_invert(coup,lvl);
	
	affichelvl(&ecran,coup.fait -> val,1);
	
	while(coup.continuer)
	{
		evenement = attendre_evenement_invert(coup.fait -> val);
		coup = action_invert(coup,evenement);
		affichelvl(&ecran,coup.fait -> val,1);
	}
	if(evenement.event == E_CONFIRM) return (coup.fait -> val);
	else return lvl;
}

LEVEL play_mode_invert_auto(SDL_Surface *ecran,LEVEL lvl)
{	
	TOUR coup;
	int tmp;
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	coup = init_tour_invert(coup,lvl);
	
	int i;
	
	for(i=0;i<50;i++)
	{
		tmp = rand() % 4;
		switch(tmp)
		{
			case 0:
				evenement.deplacement.y=-1;
				evenement.deplacement.x=0;
				break;
			case 1:
				evenement.deplacement.y=1;
				evenement.deplacement.x=0;
				break;
			case 2:
				evenement.deplacement.x=1;
				evenement.deplacement.y=0;
				break;
			case 3:
				evenement.deplacement.x=-1;
				evenement.deplacement.y=0;
				break;
		}
		coup = action_invert(coup,evenement);
	}
	return (coup.fait -> val);
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
	
	printf("yeah ...\n\n");
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
	
	niveau.direction_joueur = 2*deplacement.x + deplacement.y;
	
	return niveau;
}

LEVEL deplacer_joueur_invert(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	switch(niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y])
	{
		case VIDE:
			niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
			niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
			
			switch(niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y])
			{
				case CAISSE:
					niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = VIDE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
					break;
				case CAISSE_ARRIVE:
					niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = ARRIVE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
					break;
			}
			
			niveau.joueur.x=niveau.joueur.x + deplacement.x;
			niveau.joueur.y=niveau.joueur.y + deplacement.y;
			break;
		case ARRIVE:
			niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
			niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
			
			switch(niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y])
			{
				case CAISSE:
					niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = VIDE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
					break;
				case CAISSE_ARRIVE:
					niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = ARRIVE;
					niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
					break;
			}
			
			niveau.joueur.x=niveau.joueur.x + deplacement.x;
			niveau.joueur.y=niveau.joueur.y + deplacement.y;
			break;
	}
	
	niveau.direction_joueur = (-2)*deplacement.x - deplacement.y;
	
	
	return niveau;
}

Play_Event attendre_evenement(LEVEL niveau)
{
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event event;
	int continuer=1;
	int position_bandeau = niveau.width*16 + 20 - 150;
	int x,y;
	
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
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
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(position_bandeau + 10,position_bandeau + 49,20,80,event))
				{
					continuer = 0;
					evenement.event = E_UNDO;
				}
				if(position_clic_encadre(position_bandeau + 58,position_bandeau + 97,20,80,event))
				{
					continuer = 0;
					evenement.event = E_REDO;
				}
				if(position_clic_encadre(position_bandeau + 106,position_bandeau + 145,20,80,event))
				{
					continuer = 0;
					evenement.event = E_PREVIOUS;
				}
				if(position_clic_encadre(position_bandeau + 154,position_bandeau + 193,20,80,event))
				{
					continuer = 0;
					evenement.event = E_NEXT;
				}
				if(position_clic_encadre(position_bandeau + 202,position_bandeau + 241,20,80,event))
				{
					continuer = 0;
					evenement.event = E_INIT;
				}
				if(position_clic_encadre(position_bandeau + 250,position_bandeau + 289,20,80,event))
				{
					continuer = 0;
					evenement.event = E_QUIT;
				}
				if(position_clic_encadre(20,niveau.width*32 + 20,100,niveau.height*32 + 100,event))
				{
					x = (event.button.x-20)/32;
					y = (event.button.y-100)/32;
					
					if(((x-niveau.joueur.x) + (y-niveau.joueur.y) == -1)||((x-niveau.joueur.x) + (y-niveau.joueur.y) == 1))
					{	
						evenement.deplacement.x= x - niveau.joueur.x;
						evenement.deplacement.y= y - niveau.joueur.y;
						continuer = 0;
					}
				}
				break;
		}
	}
	
	return evenement;
}

Play_Event attendre_evenement_invert(LEVEL niveau)
{
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event event;
	int continuer=1;
	int position_bandeau = niveau.width*16 + 20 - 150;
	int x,y;
	
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
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
					/*case SDLK_p:
						continuer = 0;
						evenement.event = E_PREVIOUS;
						break;
					case SDLK_s:
						continuer = 0;
						evenement.event = E_NEXT;
						break;*/
					case SDLK_q: case SDLK_ESCAPE:
						continuer = 0;
						evenement.event = E_QUIT;
						break;
					case SDLK_RETURN:
						continuer = 0;
						evenement.event = E_CONFIRM;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(position_bandeau + 10,position_bandeau + 49,20,80,event))
				{
					continuer = 0;
					evenement.event = E_UNDO;
				}
				if(position_clic_encadre(position_bandeau + 58,position_bandeau + 97,20,80,event))
				{
					continuer = 0;
					evenement.event = E_REDO;
				}
				/*if(position_clic_encadre(position_bandeau + 106,position_bandeau + 145,20,80,event))
				{
					continuer = 0;
					evenement.event = E_PREVIOUS;
				}*/
				if(position_clic_encadre(position_bandeau + 154,position_bandeau + 193,20,80,event))
				{
					continuer = 0;
					evenement.event = E_INIT;
				}
				if(position_clic_encadre(position_bandeau + 202,position_bandeau + 241,20,80,event))
				{
					continuer = 0;
					evenement.event = E_CONFIRM;
				}
				if(position_clic_encadre(position_bandeau + 250,position_bandeau + 289,20,80,event))
				{
					continuer = 0;
					evenement.event = E_QUIT;
				}
				if(position_clic_encadre(20,niveau.width*32 + 20,100,niveau.height*32 + 100,event))
				{
					x = (event.button.x-20)/32;
					y = (event.button.y-100)/32;
					
					if(((x-niveau.joueur.x) + (y-niveau.joueur.y) == -1)||((x-niveau.joueur.x) + (y-niveau.joueur.y) == 1))
					{	
						evenement.deplacement.x= x - niveau.joueur.x;
						evenement.deplacement.y= y - niveau.joueur.y;
						continuer = 0;
					}
				}
				break;
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
		case E_CONFIRM:
			coup.continuer = 0;
			break;
	}
	
	return coup;
}














