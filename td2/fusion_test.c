#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void tri_tab(int *tab,int c2)
{	
	int c1=0;
	int temp;
	int i;
	
	comparaisons=comparaisons+2;
	
	while((c1<=c2)&&(c2<=taille))
	{
		comparaisons++;
		
		if(tab[c1]>tab[c2])
		{
			temp = tab[c2];
			for(i=c2;i>c1;i--)
			{
				tab[i]=tab[i-1];
				
				comparaisons++;
			}
			tab[c1]=temp;
			c2++;
		}
		c1++;
		
		comparaisons=comparaisons+2;
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
	
	printf("veuillez entrer la taille du tableau : ");
	scanf("%d",&taille);
	
	printf("veuillez entrer le rang ou commence la 2eme partie du tableau : ");
	scanf("%d",&mil);
	
	int tab[taille];
	
	remplir_tableau_trie(tab,mil);
	
	affiche_tab(tab);
	
	printf("\n");
	
	tri_tab(tab,mil);
	
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
