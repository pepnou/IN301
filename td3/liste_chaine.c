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

int est_vide(liste a)
{
	return a==NULL;
}

/*
void afficher_liste(liste a)
{
	liste b=a;
	while((*b).suiv!=NULL)
	{
		printf("%d\n",(*b).val);
		b=(*b).suiv;
	}
	printf("%d\n",(*a).val);
}
*/

void afficher_liste(liste a)
{
	while(!(a==NULL))
	{
		printf("%d\n",a->val);
		a=a->suiv;
	}
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
	while(!est_vide(b))
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

liste ajout_fin(liste a,int c)
{
	if(est_vide(a)) return ajout_debut(a,c);
	a->suiv=ajout_fin(a->suiv,c);
	return a;
}

int est_trie(liste a)
{
	if((a==NULL)||(a->suiv==NULL)) return 1;
	while(!(a->suiv == NULL))
	{
		if(a->val > a->suiv->val)
		{
			printf("a->val : %d , a->suiv->val : %d\n",a->val,a->suiv->val);
			return 0;
		}
		a = a->suiv;
	}
	return 1;
}

liste insertion_trie(liste b,int c)
{
	liste e=b;
	liste d;
	
	if(b==NULL) return ajout_debut(b,c);
	if(!est_trie(b))return b;
	
	if(!(d=malloc(sizeof(elem)))) exit(EXIT_FAILURE);
	d->val=c;
	
	while(b->val>c)b=b->suiv;
	
	d->suiv=b->suiv;
	b=d;
	
	return e;	
}

liste liste_alea(int n)
{
	liste a=NULL;
	int c;
	while(c=rand()%n)
	{
		a = ajout_debut(a,c);
	}
	return a;
}

int nbr_elem(liste a)
{
	int res=0;
	while(!(a==NULL))
	{
		a=a->suiv;
		res++;
	}
	return res;
}

int recherche_elem(liste a, int b)
{
	while(!(a==NULL))
	{
		if(a->val == b)return 1;
		a=a->suiv;
	}
	return 0;
}

liste suppr_elem(liste a,int b)
{
	liste c,d;
	d=a;
	while(!(a==NULL))
	{
		if(a->val == b)
		{
			c=a->suiv;
			free(a);
			a=c;
		}
		a=a->suiv;
	}
	return d;
}

liste suppr_elem2(liste a,int b)
{
	if(est_vide(a)) return a;
	if(a->val==b) return suppr_elem2(a->suiv,b);
	a->suiv=suppr_elem2(a->suiv,b);
	return a;
}

liste concat_liste(liste l1,liste l2)
{
	liste a=l1;
	while(!(l1->suiv == NULL)) l1 = l1->suiv;
	l1->suiv=l2;
	return a;
}

liste entrela_liste_trie(liste l1,liste l2)
{
	liste l3=NULL;
	
	if(l1==NULL)return l2;
	if(l2==NULL)return l1;
	if(l1->val<=l2->val)
	{
		if(!(l3=malloc(sizeof(elem)))) exit(EXIT_FAILURE);
		l3->val=l1->val;
		l3->suiv=entrela_liste_trie(l1->suiv,l2);
		return l3;
	}
	else
	{
		if(!(l3=malloc(sizeof(elem)))) exit(EXIT_FAILURE);
		l3->val=l2->val;
		l3->suiv=entrela_liste_trie(l1,l2->suiv);
		return l3;
	}
}

liste crea_liste_trie(int n)
{
	int i;
	liste a=NULL;
	
	for(i=0;i<n;i++)
	{
		a = ajout_fin(a,10*i+((rand()%10)));
	}
	return a;
}

liste tri_bulle_liste(liste a)
{
	liste e=a;
	liste temp;
	while(!(a->suiv==NULL))
	{
		if(a->val>a->suiv->val)
		{
			temp=a->suiv->suiv;
			a->suiv->suiv=a;
			a->suiv=temp;
			a=e;
		}
	}
	return a;
}

int main()
{
	srand(time(NULL));
	liste li;
	li=liste_alea(20);
	
	/*
	afficher_liste(li);
	printf("est trié ? : %d\nnbr element : %d\n",est_trie(li),nbr_elem(li));
	int c = rand()%50;
	printf("est %d present ? : %d\n",c,recherche_elem(li,c));
	if(recherche_elem(li,c))
	{
		li=suppr_elem2(li,c);
		printf("\n");
		afficher_liste(li);
	}
	*/
	
	/*
	li=crea_liste_trie(10);
	liste li2;
	li2=crea_liste_trie(10);
	liste li3;
	li3=entrela_liste_trie(li,li2);
	
	afficher_liste(li);
	printf("\n");
	afficher_liste(li2);
	printf("\n");
	afficher_liste(li3);
	*/
	
	li=tri_bulle_liste(li);
	afficher_liste(li);
	
	return EXIT_SUCCESS;
}
