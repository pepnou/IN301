#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "lecture_ecriture.h"

liste insere_debut(liste l,LEVEL lvl)
{
	liste ltmp;
	if(!(ltmp = malloc(sizeof(struct elem)))) exit(EXIT_FAILURE);
	
	ltmp->val = lvl;
	ltmp->suiv = l;
	
	return ltmp;
}

TOUR init_tour(TOUR coup , int num_lvl)
{
	coup.fait = NULL;
	coup.deplace = NULL;	
	coup.num_level = num_lvl;
	coup.base_lvl = lecture_fichier(num_lvl);
	coup.fait = insere_debut(coup.fait,coup.base_lvl);
	coup.continuer = (victoire(coup.fait -> val) + 1) % 2;
	coup.nbr_tour = 0;
	return coup;
}

TOUR init_tour_invert(TOUR coup , LEVEL lvl)
{
	coup.fait = NULL;
	coup.deplace = NULL;	
	coup.num_level = 42;
	coup.base_lvl = lvl;
	coup.fait = insere_debut(coup.fait,coup.base_lvl);
	coup.continuer = 1;
	return coup;
}

LEVEL suppr_debut(liste* l)
{
	LEVEL tmp = (*l)->val;
	liste ltmp = *l;
	(*l) = (*l)->suiv;
	free(ltmp);
	
	return tmp;
}

void suppr_liste(liste l)
{
	if(!(l == NULL))
	{
		suppr_liste(l->suiv);
		free(l);
	}
}
