#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int taille = 100;
int comparaisons = 0;

void remplir_tableau_trie(int *tab,int m)
{
	int i;
	
	srand(time(NULL));
	
	tab[0]=rand()%100;
	
	for(i=1;i<m;i++)
	{
		tab[i]= tab[i-1]+rand()%100;
	}
	
	tab[m]=rand()%100;
	
	for(i=m+1;i<taille;i++)
	{
		tab[i]= tab[i-1]+rand()%100;
	}
	
}

void affiche_tab(int *tab)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		printf("%d : %d\n",i,tab[i]);
	}
}

void tri_tab(int *tab,int c1,int c2,int c3,int c4)
{
	if(c1+1==c2)
	{
		
	}
	else
	{
		
	}
}

int est_tab_trie(int *tab)
{
	int i;
	
	for(i=1;i<taille;i++)
	{
		if(tab[i]<tab[i-1]) return 0;
	}
	return 1;
}

int main()
{
	int mil;
	
	printf("veuillez entrer la taille du tableau en puissance de 2 : 2^");
	scanf("%d",&taille);
	taille = pow(2,taille);
	
	//printf("veuillez entrer le rang ou commence la 2eme partie du tableau : ");
	//scanf("%d",&mil);
	
	mil=taille/2;
	
	int tab[taille];
	
	remplir_tableau_trie(tab,mil);
	
	affiche_tab(tab);
	
	printf("\n");
	
	tri_tab(tab,0,mil-1,mil,taille-1);
	
	affiche_tab(tab);
	
	printf("\n");
	
	switch(est_tab_trie(tab))
	{
		case 0:
			printf("le tableau n est pas trié\n");
			break;
		case 1:
			printf("le tableau est trié\n");
			break;
	}
	
	printf("\n");
	printf("nombre de comparaisons : %d\n",comparaisons);
	
	return 0;
}
