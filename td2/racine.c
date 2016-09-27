#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int truc_inutile;
	
	float a;
	float err;
	float deb=0;
	float fin=a;
	
	printf("veuillez entrer l'entier positif : "); 
	scanf("%f",&a);
	printf("veuillez entrer l'erreur : "); 
	scanf("%f",&err);
	
	float res=(deb+fin)/2;
//	printf("%f\n",res);
//	scanf("%d",&truc_inutile);
	
	while((res*res>a+err)||(res*res<a-err))
	{
		if((deb*deb<a+err)&&(deb*deb>a-err))
		{
			res=deb;
			break;
		}
		if((fin*fin<a+err)&&(fin*fin>a-err))
		{
			res=fin;
			break;
		}
		
		if(res*res>a+err)
		{
			fin=res;
		}
		if(res*res<a-err)
		{
			deb=res;
		}
		res=(deb+fin)/2;
		
//		printf("%f\n",res);
//		scanf("%d",&truc_inutile);
	}
	
	printf("%f\n",res);
	
	return 0;
}
