#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tableau
	{
		int taille;
		int T[100];
	};
typedef struct tableau tableau;

int alea(int n)
{
	return rand()%n;
}

void ini_struct_tab(tableau *a)
{
	int i;
	(*a).taille=10;
	for(i=0;i<(*a).taille;i++) (*a).T[i]=alea(20);
}

void affiche_tableau_struct_tab(tableau b)
{
	printf("\n");
	int i;
	for(i=0;i<b.taille;i++) printf("%d\n",b.T[i]);
}

int prod_tableau_struct_tab(tableau c)
{
	int res=1;
	int i;
	for(i=0;i<c.taille;i++)
	{
		res*=c.T[i];
	}
	
	printf("\nsomme element tableau : %d\n",res);
	return res;
}

int min_tableau_struct_tab(tableau d)
{
	int min=d.T[0];
	int i;
	for(i=1;i<d.taille;i++)
	{
		if(d.T[i]<min) min=d.T[i];
	}
	
	printf("\nminimum tableau : %d\n",min);
	return min;
}

void decale_droite_tableau_struct_tab(tableau *e)
{
	int i;
	for(i=(*e).taille;i>0;i--)
	{
		(*e).T[i]=(*e).T[i-1];
	}
	(*e).T[0]=0;
	(*e).taille++;
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

int decale_gauche_tableau_struct_tab_modif(tableau *e,int rang)
{
	if(rang>(*e).taille)return -1;
	
	int i;
	for(i=rang;i<(*e).taille-1;i++)
	{
		(*e).T[i]=(*e).T[i+1];
	}
	(*e).taille--;
	
	return 1;
}

void trie_tableau_struct_tab(tableau *f)
{
	int tmp;
	int i=0;
	while(i<(*f).taille)
	{
		if((*f).T[i]>(*f).T[i+1])
		{
			tmp=(*f).T[i];
			(*f).T[i]=(*f).T[i+1];
			(*f).T[i+1]=tmp;
			i=0;
		}
		else
		{
			i++;
		}
	}
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

void invert_tableau_struct_tab(tableau *h)
{
	int tmp;
	int i;
	int mil=(*h).taille/2;
	for(i=0;i<mil;i++)
	{
		tmp=(*h).T[i];
		(*h).T[i]=(*h).T[(*h).taille-i-1];
		(*h).T[(*h).taille-1-i]=tmp;
	}
}

void elim_alea_struct_tab(tableau *i)
{
	decale_gauche_tableau_struct_tab_modif(i,alea(((*i).taille)-1));
}

void elim_doublon_tableau_struct_tab(tableau *j)
{
	int i;
	for(i=0;i<((*j).taille)-1;i++)
	{
		if((*j).T[i]==(*j).T[i+1])
		{
			decale_gauche_tableau_struct_tab_modif(j,i);
			i--;
		}
	}
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

int inser_tableau_struct_tab_modif(tableau *g,int x,int fin)
{
	int i;
	for(i=0;i<=fin;i++)
	{
		if((*g).T[i]>x)
		{
			decale_droite_tableau_struct_tab_modif(g,i);
			(*g).T[i]=x;
			return 1;
		}
	}
	decale_droite_tableau_struct_tab_modif(g,i);
	(*g).T[i]=x;
	(*g).taille++;
	return 1;
	
}

void tri_insertion_tableau_struct_tab(tableau *l,int n)
{
	if(n==((*l).taille-1));
	else
	{
		inser_tableau_struct_tab_modif(l,(*l).T[n+1],n);
		decale_gauche_tableau_struct_tab_modif(l,n+2);
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
	
	ini_struct_tab(&tab);
	affiche_tableau_struct_tab(tab);
	
	//prod_tableau_struct_tab(tab);
	//min_tableau_struct_tab(tab);
	
	//decale_droite_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//decale_droite_tableau_struct_tab_modif(&tab,5);
	//affiche_tableau_struct_tab(tab);
	
	//trie_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//inser_tableau_struct_tab(&tab,alea(20));
	//affiche_tableau_struct_tab(tab);
	
	//invert_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//elim_alea_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//elim_doublon_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//tri_selection_tableau_struct_tab(&tab,0,tab.taille-1);
	//affiche_tableau_struct_tab(tab);
	
	tri_insertion_tableau_struct_tab(&tab,0);
	affiche_tableau_struct_tab(tab);
	
	//tri_bulle_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	
	printf("\n");
	return 0;
}
