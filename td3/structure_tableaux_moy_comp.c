#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tableau
	{
		int taille;
		int T[100];
	};
typedef struct tableau tableau;

int comp_selection = 0;
int comp_insertion = 0;
int comp_bulle = 0;

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
	for(i=debut+1;i<(*d).taille;i++)
	{
		if((*d).T[i]<(*d).T[min]) min=i;
	}
	
	tmp=(*d).T[debut];
	(*d).T[debut]=(*d).T[min];
	(*d).T[min]=tmp;
}

void tri_selection_tableau_struct_tab(tableau *k,int debut,int fin)
{
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
	for(i=0;i<x;i++)
	{
		if((*g).T[i]>(*g).T[x])
		{
			for(j=x;j>i;j--)
			{
				(*g).T[j] = (*g).T[j-1];
			}
			(*g).T[i]=a;
		}
	}
}

void tri_insertion_tableau_struct_tab(tableau *l,int n)
{
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
	
	for(i=0;i<(*m).taille;i++)
	{
		for(j=0;j<(*m).taille-1;j++)
		{
			if((*m).T[j]>(*m).T[j+1])
			{
				tmp=(*m).T[j];
				(*m).T[j]=(*m).T[j+1];
				(*m).T[j+1]=tmp;
			}
		}
	}
}


int main()
{
	srand(time(NULL));
	
	tableau tab;
	
	
	printf("sizeof(tableau) : %lu\n\n",sizeof(tableau));
	
	//printf("%d\n",alea(100));
	
	ini_struct_tab(&tab,10);
	affiche_tableau_struct_tab(tab);

	
	tri_selection_tableau_struct_tab(&tab,0,tab.taille-1);	
	tri_insertion_tableau_struct_tab(&tab,1);
	tri_bulle_tableau_struct_tab(&tab);

	
	
	printf("\n");
	return 0;
}
