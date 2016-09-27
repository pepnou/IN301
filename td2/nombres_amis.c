#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int somme_des_diviseurs(int a)
{
	int res=0;
	int i;
	for(i=1;i<a;i++)
	{
		if(a%i == 0) res=res+i;
	}
	return res;
}

int main()
{
	int test = 0;
	
	printf("voulez vous : \n"); 
	printf(" -tester si deux entiers sont des nombres amis ou non (1)\n"); 
	printf(" -afficher tous les couples de nombres amis (n,m) tels que n<=m<=nmax (2)\n"); 
	printf("veuillez entrer votre choix : "); 
	scanf("%d",&test);
	
	
	if(test == 1)
	{
	
	int entier1;
	int entier2;
	
	printf("veuillez entrer le premier entier positif : "); 
	scanf("%d",&entier1);
	printf("veuillez entrer le deuxieme entier positif : "); 
	scanf("%d",&entier2);
	
	if((somme_des_diviseurs(entier1)==entier2)&&(somme_des_diviseurs(entier2)==entier1))
		printf("%d et %d sont des nombres amis\n",entier1,entier2);
	else
		printf("%d et %d ne sont pas des nombres amis\n",entier1,entier2);
	
	}
	
	if(test == 2)
	{
		int nmax;
		printf("veuillez entrer nmax : "); 
		scanf("%d",&nmax);
		
		int i,j;
		
		for(i=0;i<=nmax;i++)
		{
			for(j=0;j<=i;j++)
			{
				if((somme_des_diviseurs(j)==i)&&(somme_des_diviseurs(i)==j))
				printf("(%d,%d)\n",j,i);
			}
		}
		
	}
	
	printf("fait\n");
	return 0;
}
