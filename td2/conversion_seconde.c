#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int temps,heures,minutes,secondes;
	
	srand(time(NULL));
	temps = rand();
	
	secondes = temps%60;
	heures = temps /3600;
	minutes = temps/60 - heures*60;
	
	printf("%d secondes correspond a : ",temps);
	if(heures>1) printf("%d heures, ",heures);
	else printf("%d heure, \n",heures);
	if(minutes>1) printf("%d minutes, ",minutes);
	else printf("%d minutes, \n",minutes);
	if(secondes>1) printf("et %d secondes\n",secondes);
	else printf("et %d seconde\n",secondes);
	
	
	return 0;
}
