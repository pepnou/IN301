#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tableau
	{
		int taille;
		int T[1500];
	};
typedef struct tableau tableau;

int comp_selection;
int comp_insertion;
int comp_bulle;

int alea(int n)
{
	return rand()%n;
}

void ini_struct_tab(tableau *a,int tail)
{
	int i;
	(*a).taille=tail;
	for(i=0;i<(*a).taille;i++) (*a).T[i]=alea(20);
}

void affiche_tableau_struct_tab(tableau b)
{
	printf("\n");
	int i;
	for(i=0;i<b.taille;i++) printf("%d\n",b.T[i]);
}

int decale_droite_tableau_struct_tab_modif(tableau *e,int rang)
{
	if(rang>(*e).taille)return -1;
	
	int i;
	for(i=(*e).taille;i>rang;i--)
	{
		(*e).T[i]=(*e).T[i-1];
	}
	(*e).T[rang]=0;
	(*e).taille++;
	
	return 1;
}

int inser_tableau_struct_tab(tableau *g,int x)
{
	int i;
	for(i=0;i<(*g).taille;i++)
	{
		if((*g).T[i]>x)
		{
			decale_droite_tableau_struct_tab_modif(g,i);
			(*g).T[i]=x;
			//(*g).taille++;
			return 1;
		}
	}
	(*g).T[(*g).taille]=x;
	(*g).taille++;
	return 1;
}

void min_tableau_struct_tab_modif(tableau *d,int debut,int fin)
{	
	int min=debut;
	int i;
	int tmp;
	
	comp_selection++;
	
	for(i=debut+1;i<(*d).taille;i++)
	{
		comp_selection+=2;
		if((*d).T[i]<(*d).T[min]) min=i;
	}
	
	tmp=(*d).T[debut];
	(*d).T[debut]=(*d).T[min];
	(*d).T[min]=tmp;
}

void tri_selection_tableau_struct_tab(tableau *k,int debut,int fin)
{
	comp_selection++;
	
	if(debut == fin);
	else
	{
		min_tableau_struct_tab_modif(k,debut,fin);
		tri_selection_tableau_struct_tab(k,debut+1,fin);
		
		//affiche_tableau_struct_tab(*k);
	}
}

void inser_tableau_struct_tab_modif(tableau *g,int x)
{
	int a = (*g).T[x];
	int i,j;
	
	comp_insertion++;
	
	for(i=0;i<x;i++)
	{
		comp_insertion+=2;
		if((*g).T[i]>(*g).T[x])
		{
			comp_insertion++;
			for(j=x;j>i;j--)
			{
				comp_insertion++;
				(*g).T[j] = (*g).T[j-1];
			}
			(*g).T[i]=a;
		}
	}
}

void tri_insertion_tableau_struct_tab(tableau *l,int n)
{
	comp_insertion++;
	if(!(n>((*l).taille-1)))
	{
		inser_tableau_struct_tab_modif(l,n);
		tri_insertion_tableau_struct_tab(l,n+1);
	}
}

void tri_bulle_tableau_struct_tab(tableau *m)
{
	int tmp;
	int i,j;
	
	comp_bulle++;
	
	for(i=0;i<(*m).taille;i++)
	{
		comp_bulle+=2;
		for(j=0;j<(*m).taille-1;j++)
		{
			comp_bulle+=2;
			if((*m).T[j]>(*m).T[j+1])
			{
				tmp=(*m).T[j];
				(*m).T[j]=(*m).T[j+1];
				(*m).T[j+1]=tmp;
			}
		}
	}
}

void re_init_cont()
{
	comp_selection = 0;
	comp_insertion = 0;
	comp_bulle = 0;
}

void affiche_comp()
{
	printf("nombre de comparaison moyen du tri par selection : %d\n",comp_selection);
	printf("nombre de comparaison moyen du tri par insertion : %d\n",comp_insertion);
	printf("nombre de comparaison moyen du tri a bulle : %d\n",comp_bulle);
}

void moy_comp(int n)
{
	comp_selection /= n;
	comp_insertion /= n;
	comp_bulle /= n;
}

int main()
{
	srand(time(NULL));
	
	tableau tab;
	int nombre_tri = 10;
	int i,j;
	
	
	
	printf("sizeof(tableau) : %lu\n\n",sizeof(tableau));
	
	//printf("%d\n",alea(100));
	
	//ini_struct_tab(&tab,10);
	//affiche_tableau_struct_tab(tab);
	
	printf("taille\ttri_selection\ttri_insertion\ttri_bulle\n");
	printf("\n");
	
	for(j=100;j<=1500;j+=100)
	{
		re_init_cont();
		
		for(i=0;i<nombre_tri;i++)
		{
			ini_struct_tab(&tab,j);
			tri_selection_tableau_struct_tab(&tab,0,tab.taille-1);	
			ini_struct_tab(&tab,j);
			tri_insertion_tableau_struct_tab(&tab,1);
			ini_struct_tab(&tab,j);
			tri_bulle_tableau_struct_tab(&tab);
		}
		moy_comp(i);
		
		printf("%d\t%d\t%d\t%d\n",j,comp_selection,comp_insertion,comp_bulle);
	}
	
	printf("\n");
	return 0;
}
