#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct elem
{
	int val;
	struct elem *suiv;
	
};
typedef struct elem elem;
typedef elem* liste;

liste creer_liste_vide()
{
	return NULL;
}

int est_vide(liste)
{
	return liste==NULL;
}

void afficher_liste(liste a)
{
	liste b=a
	while((*b).suiv!=NULL)
	{
		printf("%d\n",(*b).val);
		b=(*b).suiv;
	}
	printf("%d\n",(*a).val);
}

void lib_mem(liste a)
{
	if((a->suiv->suiv)==NULL)
	{
		free(a->suiv);
		a.suiv=NULL;
	}
	else
	{
		lib_mem(a->suiv);
		free(a);
	}
}

liste ajout_debut(liste a,int c)
{
	liste b;
	if((b=malloc(sizeof(elem)))==NULL) exit(EXIT_FAILURE);
	(*b).val=c;
	(*b).suiv=a;
	return b;
}

liste ajout_fin(liste a,int c)
{
	liste b;
	if(!(b=malloc(sizeof(elem)))) exit(EXIT_FAILURE);
	while
}

int main()
{
	
	
	
	
	
	
	
	
	return EXIT_SUCCESS;
}
