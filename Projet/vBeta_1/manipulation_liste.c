#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

liste insere_debut(liste l,LEVEL lvl)
{
	liste ltmp;
	if(!(ltmp=malloc(sizeof(LEVEL)))) exit(EXIT_FAILURE);
	
	ltmp->val = lvl;
	ltmp->suiv = l;
	
	return ltmp;
}

LEVEL suppr_debut(liste* l)
{
	LEVEL tmp = (*l)->val;
	liste ltmp = *l;
	(*l) = (*l)->suiv;
	free(ltmp);
	
	return tmp;
}

TOUR init_tour(TOUR coup)
{
	coup.fait = NULL;
	coup.deplace = NULL;
	
	return coup;
}

void suppr_liste(liste l)
{
	if(!(l == NULL))
	{
		suppr_liste(l->suiv);
		free(l);
	}
}
