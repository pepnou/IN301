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
int largeur_fenetre = 300;
int hauteur_fenetre = 150;

void creation_lvl(SDL_Surface *ecran);

int victoire(LEVEL niveau);

void main_menu(SDL_Surface *ecran);
void play_menu(SDL_Surface *ecran);
void editor_menu(SDL_Surface *ecran);
void play_mode(SDL_Surface *ecran,int num_lvl);
void play_mode_invert(SDL_Surface *ecran,LEVEL lvl);

LEVEL deplacer_joueur(LEVEL niveau,POS deplacement);
LEVEL deplacer_joueur_invert(LEVEL niveau,POS deplacement);
Play_Event attendre_evenement();
Play_Event attendre_evenement_invert();
TOUR action(TOUR coup,Play_Event PE);
TOUR action_invert(TOUR coup,Play_Event PE);
void modif_niveau(LEVEL niveau,SDL_Surface *ecran);
void position_depart(LEVEL lvl,SDL_Surface *ecran);

int lvl_correct(LEVEL lvl);
int* contenu_lvl(LEVEL lvl);
POS recherche_joueur(LEVEL lvl);
int joueur_encadre(LEVEL lvl,int x,int y);
int joueur_encadre_etape_2(LEVEL* lvl,int x,int y);

void changement_resolution(SDL_Surface **ecran);
void choix_resolution(SDL_Surface *ecran);
void affiche_resolution(SDL_Surface *ecran,int tmpw,int tmph);

int main()
{	
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_WM_SetCaption("Sokoban vAlpha2",NULL);

    //~ ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	//~ choix_resolution(ecran);
	//~ ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
	
	changement_resolution(&ecran);
	
	main_menu(ecran);
	
	SDL_Quit();
	
	exit(EXIT_SUCCESS);
}

void changement_resolution(SDL_Surface **ecran)
{
	int i,j;
	FILE* fichier = NULL;
	
	if((fichier = fopen("taille_fenetre.txt","r")) == NULL)
	{
		*ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
		choix_resolution(*ecran);
		*ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
		i=largeur_fenetre;j=hauteur_fenetre;
		
		fichier = fopen("taille_fenetre.txt","w+");
		fprintf(fichier,"%d %d",i,j);
		fclose(fichier);
	}
	else
	{
		fscanf(fichier,"%d %d",&i,&j);
		largeur_fenetre=i;hauteur_fenetre=j;
		*ecran = SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE);
		fclose(fichier);
	}
}

void choix_resolution(SDL_Surface *ecran)
{		
	//~ int largeur_fenetre_tmp = largeur_fenetre;
	//~ int hauteur_fenetre_tmp = hauteur_fenetre;
	
	int largeur_fenetre_tmp = 600;
	int hauteur_fenetre_tmp = 600;
	
	affiche_resolution(ecran,largeur_fenetre_tmp,hauteur_fenetre_tmp);
	
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
					case SDLK_RETURN:
						largeur_fenetre = largeur_fenetre_tmp;
						hauteur_fenetre = hauteur_fenetre_tmp;
						continuer = 0;
						break;
					case SDLK_ESCAPE:
						exit(EXIT_SUCCESS);
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(0,largeur_fenetre/2,hauteur_fenetre/3,hauteur_fenetre*2/3,event))
				{
					if(largeur_fenetre_tmp >100) largeur_fenetre_tmp -= 50;
				}
				if(position_clic_encadre(largeur_fenetre/2,largeur_fenetre,hauteur_fenetre/3,hauteur_fenetre*2/3,event))
				{
					largeur_fenetre_tmp += 50;
				}
				if(position_clic_encadre(0,largeur_fenetre/2,hauteur_fenetre*2/3,hauteur_fenetre,event))
				{
					if(hauteur_fenetre_tmp >100) hauteur_fenetre_tmp -= 50;
				}
				if(position_clic_encadre(largeur_fenetre/2,largeur_fenetre,hauteur_fenetre*2/3,hauteur_fenetre,event))
				{
					hauteur_fenetre_tmp += 50;
				}
				
				affiche_resolution(ecran,largeur_fenetre_tmp,hauteur_fenetre_tmp);
				break;
			}
		}
}

void affiche_resolution(SDL_Surface *ecran,int tmpw,int tmph)
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
	
	texte = TTF_RenderText_Blended(police,"-",couleurblanche);

	positionTexte.x = largeur_fenetre/4 - 15;
	positionTexte.y = hauteur_fenetre/3 + 10;

	SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
	
	positionTexte.y = hauteur_fenetre*2/3 + 10;

	SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
		
	texte = TTF_RenderText_Blended(police,"+",couleurblanche);

	positionTexte.x = largeur_fenetre*3/4 - 15;
	positionTexte.y = hauteur_fenetre/3 + 10;

	SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
	
	positionTexte.y = hauteur_fenetre*2/3 + 10;

	SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
		
	char Tmp[10] = "";
	sprintf(Tmp,"%d",tmpw);	
		
	texte = TTF_RenderText_Blended(police,Tmp,couleurblanche);
	
	positionTexte.x = largeur_fenetre/2 - 35;
	positionTexte.y = hauteur_fenetre/3 + 10;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    sprintf(Tmp,"%d",tmph);	
		
	texte = TTF_RenderText_Blended(police,Tmp,couleurblanche);
	
	positionTexte.y = hauteur_fenetre*2/3 + 10;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    texte = TTF_RenderText_Blended(police,"Resolution",couleurblanche);

	positionTexte.x = largeur_fenetre/2 - 100;
	positionTexte.y = 10;

	SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    
    SDL_Flip(ecran);
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
							position_depart(niveau,ecran);
							//enregistrer_lvl(niveau);
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
				
				affichelvl(ecran,niveau);
				break;
			default:
				break;
		}
	}
}

void position_depart(LEVEL lvl,SDL_Surface *ecran)
{
	play_mode_invert(ecran,lvl);
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
	
	
	//~ play_mode(ecran,50);
}

void play_mode(SDL_Surface *ecran,int num_lvl)
{	
	TOUR coup;
	
	coup = init_tour(coup,num_lvl);
	
	
	affichelvl(ecran,coup.fait -> val);
	
	
	while((coup.continuer) && (!(victoire(coup.fait -> val))))
	{
		coup = action(coup,attendre_evenement());
		affichelvl(ecran,coup.fait -> val);
	}
}

void play_mode_invert(SDL_Surface *ecran,LEVEL lvl)
{	
	TOUR coup;
	
	coup = init_tour_invert(coup,lvl);
	
	affichelvl(ecran,coup.fait -> val);
	
	while(coup.continuer)
	{
		coup = action_invert(coup,attendre_evenement_invert());
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

Play_Event attendre_evenement_invert()
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
				case SDLK_RETURN:
					continuer = 0;
					evenement.event = E_CONFIRM;
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
			//~ coup.fait = insere_debut(coup.fait,deplacer_joueur_invert(coup.fait -> val, PE.deplacement));
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
			//~ coup.fait = insere_debut(coup.fait,deplacer_joueur(coup.fait -> val, PE.deplacement));
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
			enregistrer_lvl(coup.fait -> val);
			coup.continuer = 0;
			break;
	}
	
	return coup;
}













