#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille=100;

int nombre_valeur_tab(int *tab)
{
	
}

int main()
{
	int i;
	int tab[taille];
	
	srand(time(NULL));
	int a;
	
	for(i=0;i<taille;i++)
	{
		tab[i]=rand()%100;
	}
	
	
	
	return 0;
}
