#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float racine(int x)
{	
	float err=0.000001;
	float deb=0.0;
	float fin=x;
	float res=(deb+fin)/2.0;
	
	if((deb*deb<x+err)&&(deb*deb>x-err)) return deb;
	if((fin*fin<x+err)&&(fin*fin>x-err)) return fin;
	
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

float calcul_suite(int nmax,int n)
{	
	if(n==nmax)
	{
		return sqrt(n);
	}
	else
	{
		return sqrt(n+calcul_suite(nmax,(n+1)));
	}	
}

int main()
{
	int a;
	int i;
	
	printf("veuillez entrer le rang max de la suite : "); 
	scanf("%d",&a);
	
	for(i=1;i<=a;i++)
	{
		printf("rang %d : %f\n",i,calcul_suite(i,1));
	}
	
	printf("fait\n");
	return 0;
}
