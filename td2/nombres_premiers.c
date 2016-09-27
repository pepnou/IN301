#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int a;
	int b=0;
	int i;
	
	printf("entrer un entier positif : ");
	scanf("%d",&a);
	for(i=2;i*i<=a;i++)
	{
		if(a%i == 0) b=1;
	}
	if(b==1) printf("%d n'est pas premier\n",a);
	else printf("%d est premier\n",a);
	
	return 0;
}
