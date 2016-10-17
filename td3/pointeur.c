#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void affiche_taille_mem()
{
	printf("sizeof(char) : %lu\n",sizeof(char));
	printf("sizeof(int) : %lu\n",sizeof(int));
	printf("sizeof(double) : %lu\n",sizeof(double));
	printf("sizeof(char*) : %lu\n",sizeof(char*));
	printf("sizeof(void*) : %lu\n",sizeof(void*));
	printf("sizeof(int*) : %lu\n",sizeof(int*));
	printf("sizeof(double*) : %lu\n",sizeof(double*));
	printf("sizeof(int**) : %lu\n",sizeof(int**));
	printf("sizeof(int[10]) : %lu\n",sizeof(int[10]));
	printf("sizeof(char[7][3]) : %lu\n",sizeof(char[7][3]));
	//printf("sizeof(int[]) : %lu\n",sizeof(int[]));
	
	printf("\n");
	
	char tab[10];
	
	printf("sizeof(tab) : %lu\n",sizeof(tab));
	printf("sizeof(tab[0]) : %lu\n",sizeof(tab[0]));
	printf("sizeof(&tab[0]) : %lu\n",sizeof(&tab[0]));
	printf("sizeof(*&tab) : %lu\n",sizeof(*&tab));
	printf("sizeof(*&tab[0]) : %lu\n",sizeof(*&tab[0]));
	
	printf("\n");
	
	char (*p)[10]=&tab;
	
	printf("sizeof(p) : %lu\n",sizeof(p));
	printf("sizeof(*p) : %lu\n",sizeof(*p));
	printf("sizeof((*p)[2]) : %lu\n",sizeof((*p)[2]));
	printf("sizeof(&(*p)[2]) : %lu\n",sizeof(&(*p)[2]));
	
}

void swap(int *a,int *b)
{
	printf("a=%d\n",*a);
	printf("b=%d\n",*b);
	
	int tmp=*a;
	*a=*b;
	*b=tmp;
	
	printf("a=%d\n",*a);
	printf("b=%d\n",*b);
}

int main()
{
	//affiche_taille_mem();
	
	int c=24;
	int d=42;
	swap(&c,&d);
	
	
	
	return 0;
}
