#include "Sokoban.h"

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

void menu_taille_lvl(SDL_Surface *ecran)
{
	int width = 6;
	int height = 6;
	
	Play_Event PE;
		
	affiche_menu_taille_lvl(&ecran,width,height);
	
	int continuer = 1;
	
	while(continuer)
	{
		PE = attendre_event_menu_taille_lvl();
		switch(PE.event)
		{
			case E_BOUTTON_1:
				if(width > 6) width --;
				affiche_menu_taille_lvl(&ecran,width,height);
				break;
			case E_BOUTTON_2:
				if(width < 56) width ++;
				affiche_menu_taille_lvl(&ecran,width,height);
				break;
			case E_BOUTTON_3:
				if(height > 6) height --;
				affiche_menu_taille_lvl(&ecran,width,height);
				break;
			case E_BOUTTON_4:
				if(height < 25) height ++;
				affiche_menu_taille_lvl(&ecran,width,height);
				break;
			case E_CONFIRM:
				creation_lvl(ecran,width,height);
				continuer = 0;
				break;
			case E_QUIT:
				main_menu(ecran);
				continuer = 0;
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
	
	Play_Event PE;	
	int continuer = 1;
	int tmp_i,tmp_j;
		
	while(continuer)
	{
		PE = attendre_event_modif_niveau((ecran->w)/2 - 150,niveau.width,niveau.height);
		switch(PE.event)
		{
			case E_BOUTTON_1:
				if(!(lvl_correct(niveau))) break;
				niveau.joueur = recherche_joueur(niveau);
				niveau = play_mode_invert_auto(ecran,niveau);
				niveau.direction_joueur = 1;
				affichelvl(&ecran,niveau,2);
				break;
			case E_BOUTTON_2:
				if(!(lvl_correct(niveau))) break;
				niveau.joueur = recherche_joueur(niveau);
				niveau = play_mode_invert(ecran,niveau);
				niveau.direction_joueur = 1;
				affichelvl(&ecran,niveau,2);
				break;
			case E_BOUTTON_3:
				tmp_i = (PE.deplacement.x-20)/32;
				tmp_j = (PE.deplacement.y-100)/32;
				niveau.T[tmp_i][tmp_j] = (niveau.T[tmp_i][tmp_j] + 1 ) % 7;
				
				affichelvl(&ecran,niveau,2);
				break;
			case E_CONFIRM:
				if(!(lvl_correct(niveau))) break;
				niveau.joueur = recherche_joueur(niveau);
				enregistrer_lvl(niveau);
				continuer = 0;
				break;
			case E_QUIT:
				continuer = 0;
				break;
		}
	}
}

void main_menu(SDL_Surface *ecran)
{
	affiche_main_menu(&ecran);
	Play_Event PE;
	int continuer = 1;
	
	while(continuer)
	{
		PE = attendre_event_main_menu();
		switch(PE.event)
		{
			case E_QUIT:
				continuer = 0;
				break;
			case E_BOUTTON_1:
				play_menu(ecran);
				continuer = 0;
				break;
			case E_BOUTTON_2:
				menu_taille_lvl(ecran);
				continuer = 0;
				break;
		}
	}
}

void play_menu(SDL_Surface *ecran)
{
	NBR_NIVEAUX = lecture_nbr_lvl();
	int continuer = 1;
	int niveau_a_lire = 1;
	LEVEL lvl;
	Play_Event PE;
	
	if(NBR_NIVEAUX == 0)
	{
		affiche_play_menu(&ecran,NBR_NIVEAUX);
		SDL_Delay(2000);
		main_menu(ecran);
	}
	else
	{
		affiche_play_menu(&ecran,niveau_a_lire);
		while(continuer)
		{
			PE = attendre_event_play_menu();
			switch(PE.event)
			{
				case E_CONFIRM:
					play_mode(ecran,niveau_a_lire);
					continuer = 0;
					break;
				case E_QUIT:
					continuer = 0;
					main_menu(ecran);
					break;
				case E_BOUTTON_1:
					if(niveau_a_lire>1) niveau_a_lire --;
					affiche_play_menu(&ecran,niveau_a_lire);
					break;
				case E_BOUTTON_2:
					if(niveau_a_lire<NBR_NIVEAUX) niveau_a_lire ++;
					affiche_play_menu(&ecran,niveau_a_lire);
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
	affiche_interface_bas((ecran->w)/2 - 160,(ecran->h) - 140,coup.num_level,coup.nbr_tour,ecran);
	
	while((coup.continuer) && (!(victoire(coup.fait -> val))))
	{
		evenement = attendre_evenement(coup.fait -> val,ecran);
		coup = action(coup,evenement);
		affichelvl(&ecran,coup.fait -> val,0);
		affiche_interface_bas((ecran->w)/2 - 160,(ecran->h) - 140,coup.num_level,coup.nbr_tour,ecran);
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

