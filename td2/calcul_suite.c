#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float racine(int x)
{	
	float err=0.01;
	float deb=0.0;
	float fin=a;
	float res=(deb+fin)/2.0;
		
	while((res*res>x+err)||(res*res<x-err))
	{
		if(res*res>x+err)
		{
			fin=res;
		}
		if(res*res<x-err)
		{
			deb=res;
		}
		res=(deb+fin)/2.0;
	}
	
	return res;
}

void calcul_suite(int nmax,int n)
{	
	if(n==nmax)
	{
		return racine(n);
	}
	else
	{
		return racine(n+calcul_suite(nmax,n+1));
	}	
}

int main()
{
	int a;
	
	printf("veuillez entrer le rang max de la suite : "); 
	scanf("%d",&a);
	
	calcul_suite(a);
	
	printf("fait\n");
	return 0;
}
