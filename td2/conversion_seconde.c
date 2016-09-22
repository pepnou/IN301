#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int temps,heures,minutes,secondes;
	temps = 52442;
	secondes = temps%60;
	heures = temps /3600;
	minutes = temps/60 - heures*60;
	
	printf("%d correspond a : ",temps);
	if(heures>1) printf("%d heures, ",heures);
	else ("%d heure, \n",heures);
	if(minutes>1) printf("%d minutes, ",minutes);
	else ("%d minutes, \n",minutes);
	if(secondes>1) printf("et %d secondes\n",secondes);
	else ("et %d seconde\n",secondes);
	
	
	return 0;
}
