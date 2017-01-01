#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

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

int nbr_joueur_correct(int* contenu)
{
	int correct = 1;
	
	if(contenu[JOUEUR] + contenu[JOUEUR_ARRIVE] != 1)
	{
		printf("probleme sur le nombre de joueur : %d joueur(s)\n",contenu[JOUEUR] + contenu[JOUEUR_ARRIVE]);
		correct = 0;
	}
	return correct;
}

int nbr_arrive_correct(int* contenu)
{
	int correct = 1;
	
	if(contenu[ARRIVE] +  contenu[JOUEUR_ARRIVE] + contenu[CAISSE_ARRIVE] == 0)
	{
		printf("probleme : aucune zone de depot\n");
		correct = 0;
	}
	return correct;
}

int nbr_caisse_arrive_correct(int* contenu)
{
	int correct = 1;
	
	if(contenu[ARRIVE] + contenu[JOUEUR_ARRIVE] > contenu[CAISSE])
	{
		printf("probleme sur le nombre de zone de depot et de caisse : %d depot(s) pour %d caisse\n",contenu[ARRIVE] + contenu[JOUEUR_ARRIVE] + contenu[CAISSE_ARRIVE],contenu[CAISSE] + contenu[CAISSE_ARRIVE]);
		correct = 0;
	}
	return correct;
}

int joueur_encadre_etape_2(LEVEL* lvl,int x,int y)
{
	if((*lvl).T[x][y] == MUR) return 1;
	
	if((x == 0)||(x == (*lvl).width-1)) return 0;
	if((y == 0)||(y == (*lvl).height-1)) return 0;
	
	(*lvl).T[x][y] = MUR;
	
	return((joueur_encadre_etape_2(lvl,x-1,y))&(joueur_encadre_etape_2(lvl,x+1,y))&(joueur_encadre_etape_2(lvl,x,y-1))&(joueur_encadre_etape_2(lvl,x,y+1)));
}

int joueur_encadre(LEVEL lvl)
{
	int correct = 1;
	
	POS pos_j;
	pos_j = recherche_joueur(lvl);
	
	if(!(joueur_encadre_etape_2(&lvl,pos_j.x,pos_j.y)))
	{
		printf("probleme :le joueur n est pas encadré par des murs\n");
		correct = 0;
	}
	
	return correct;
}

int lvl_correct(LEVEL lvl)
{
	int correct = 1;
	POS pos_j;
	
	int* contenu = contenu_lvl(lvl);
	
	return nbr_joueur_correct(contenu)&nbr_arrive_correct(contenu)&nbr_caisse_arrive_correct(contenu)&joueur_encadre(lvl);
}

