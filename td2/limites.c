#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	double prec = 0.01;
	double lim = 0;
	int i = 1;
	
	//printf("precision : %f\n",prec);
	printf("veuillez entrer la precision : ");
	scanf("%lf",&prec);
	
	while(1.0/(pow(i+1.0,2.0))>prec)
	{
		lim = lim + (1.0/pow(i,2));
		i++;
	}
	
	printf("limite : %f\n",lim);
	
	return 0;
}
