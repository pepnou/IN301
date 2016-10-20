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
	if(!est_vide(a))
	{
		lib_mem(a->suiv);
		free(a);
	}
}

void lib_mem2(liste a)
{
	liste b;
	while(!est_vide(l))
	{
		b=a->suiv;
		free(a);
		a=b;
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

void ajout_fin(liste a,int c)
{
	liste b;
	if(!(b=malloc(sizeof(elem)))) exit(EXIT_FAILURE);
	b->val=c;
	b->suiv=NULL;
	while(a->suiv !=NULL)
	{
		a=a->suiv;
	}
	a->suiv=b;
}

int main()
{
	
	
	
	
	
	
	
	
	return EXIT_SUCCESS;
}
