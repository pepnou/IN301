#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille=100;

void elim_double_tab(int *tab)
{
	int j;
	int i;
	
	for(j=0;j<taille;j++)
	{
		if(tab[j]>0)
		{
			for(i=j+1;i<taille;i++)
			{
				if(tab[i] == tab[j]) tab[i]=tab[i]*(-1);
			}
		}
	}
}

void tab_pos(int *tab)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		if(tab[i]<0) tab[i] = tab[i]*(-1);
	}
}

int compte_valeur(int *tab)
{
	int i;
	int res=0;
	
	for(i=0;i<taille;i++)
	{
		if(tab[i]<0) res++;
	}
	return res;
}

int compte_valeur_inter(int *tab,int min,int max)
{
	int i;
	int res=0;
	
	for(i=0;i<taille;i++)
	{
		if((tab[i]<0)&&(tab[i]>=min)&&(tab[i]<max)) res++;
	}
	return res;
}

int nombre_valeur_tab(int *tab)
{
	int res;
	elim_double_tab(tab);
	res = compte_valeur(tab);
	tab_pos(tab);
	return res;
}

int nombre_valeur_inter_tab(int *tab,int min,int max)
{
	int res;
	elim_double_tab(tab);
	res = compte_valeur_inter(tab,min,max);
	tab_pos(tab);
	return res;
}

int main()
{
	int i;
	int j;
	int tab[taille];
	int tab2[10];
	
	srand(time(NULL));
	int a;
	
	for(i=0;i<taille;i++)
	{
		tab[i]=rand()%100;
	}
	
	printf("nombre de valeur dans le tableau : %d\n",nombre_valeur_tab(tab));
	
	for(i=0;j=0;i<taille;i=i+10;j++)
	{
		tab[j]=nombre_valeur_inter_tab(tab,i,i+10);
	}
	
	return 0;
}
