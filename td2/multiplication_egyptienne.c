#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int X,Y,reste;
	reste = 0;
	
	srand(time(NULL));
	X = rand()%100;
	Y = rand()%100;
	//X=23;
	//Y=87;
	
	printf("%d x %d\n",X,Y);
	
	while(X>1)
	{
		if(X%2 == 0)
		{
			X = X/2;
			Y = Y*2;
		}
		else
		{
			X--;
			reste = reste+Y;
		}
		printf("= %d x %d + %d\n",X,Y,reste);
	}
	printf("= %d\n",Y+reste);
	
	return 0;
}

