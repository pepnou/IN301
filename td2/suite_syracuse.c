#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int a;
	int iteration = 0;
	int arret;
	
	printf("veuillez entrer l'entier positif : "); 
	scanf("%d",&a);
	printf("veuillez entrer le nombre d'iterations avant arret : "); 
	scanf("%d",&arret);
	
	printf("%d\n",a);
	printf("nombre d'iterations : %d\n",iteration);
	
	while(/*(a>1)&&*/(iteration<arret))
	{
		if(a%2==0)
		{
			a=a/2;
			printf("%d\n",a);
		}
		else
		{
			a=3*a+1;
			printf("%d\n",a);
		}
		iteration++;
		printf("nombre d'iterations : %d\n",iteration);
		
	}
	
	
	printf("fait\n");
	return 0;
}
