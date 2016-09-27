#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	float prec = 0.01;
	float lim = 0;
	int i = 1;
	
	
	
	//printf("precision : %f\n",prec);
	printf("veuillez entrer la precision : ");
	scanf("%f",&prec);
	
	float test = ((i+1)*(i+1))*prec;
	
	while(1>test)
	{
		lim = lim + (1/((i+1)*(i+1)));
		i++;
	}
	
	printf("limite : %f\n",lim);
	
	return 0;
}
