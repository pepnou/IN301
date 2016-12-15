#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct elemArith{
	struct elemArith* fg;
	struct elemArith* fd;
	
	int type;
	float val;
};
typedef struct elemArith* arithExpr;

int parenthese_pos(char *s){//retourne la position de la parenthèse qui ferme la parenthèse en position 0
	
	int i = 0;int nbr_p = 0;
	
	while(s[i] != '\0')
	{
		if(s[i] == '(') nbr_p ++;
		if(s[i] == ')') nbr_p --;
		
		if(nbr_p == 0) return i;
		i++;
	}
	
	return strlen(s);
}

arithExpr lire_chaine(char *s){
	
	if(s == NULL) return NULL;
	
	arithExpr arbre = NULL;
	if(!(arbre = malloc(sizeof(arithExpr)))) exit(EXIT_FAILURE);
	
	if((isdigit(s[0]))||(s[0] == '-'))
	{
		arbre->type = 0;
		sscanf(s,"%f",&(arbre->val)); 
		arbre->fg = NULL;
		arbre->fd = NULL;
		
		return arbre;
	}
	
	int par = parenthese_pos(s);
	/*
	int i,j;
	int lenght = strlen(s);
	
	char* ag;
	if(!(ag = malloc(lenght*sizeof(char)))) exit(EXIT_FAILURE);
	char* ad;
	if(!(ad = malloc(lenght*sizeof(char)))) exit(EXIT_FAILURE);
	
	for(i=1;i<par;i++)
	{
		ag[i] = s[i];
	}
	for(i=par+3;j=0;i<lenght-2;i++;j++)
	{
		ad[j] = s[i];
	}
	
	arbre->fg = lire_chaine(ag);
	arbre->fd = lire_chaine(ad);
	*/
	
	switch(s[par+1])
	{
		case '+':
			arbre->type = 1;
			break;
		case '*':
			arbre->type = 2;
			break;
	}
	
	arbre->fg = lire_chaine(&s[1]);
	arbre->fd = lire_chaine(&s[par+3]);
	
	return arbre;
}

void affiche(arithExpr a)
{
	FILE* fichier = fopen("expr.txt","a");
	if(a->fg == NULL)
	{
		fprintf(fichier,"%f",a->val);
		printf("%f",a->val);
	}
	else
	{
		fputc('(',fichier);
		printf("(");
		affiche(a->fg);
		fputc(')',fichier);
		printf(")");
		
		switch(a->type)
		{
			case 1:
				fputc('+',fichier);
				printf("+");
				break;
			case 2:
				fputc('*',fichier);
				printf("*");
				break;
		}
		
		fputc('(',fichier);
		printf("(");
		affiche(a->fd);
		fputc(')',fichier);
		printf(")");
	}
	fclose(fichier);
}

double eval_arith(arithExpr a){
	
 return 0;
}

arithExpr rand_arith(int n, int m){
	return NULL;
	
}

void free_arith(arithExpr a){
	
}

arithExpr simplifie(arithExpr a){
	return NULL;
}

int main(int argc, char **argv){

	srand(time(NULL));

	if(argc != 2){
		printf("Il doit y a voir comme unique argument le chemin du fichier à ouvrir \n");	
		exit(1);
	}
	
	FILE* f = fopen(argv[1],"w+");
	char buffer[300];
	fscanf(f,"%s",buffer);
	printf("Taille du fichier : %d\n",(int)strlen(buffer));
	printf("Contenu du fichier %s\n",buffer);
	
	////////////////// Test des fonctions ///////////////////////
	
	printf("1\n");
	
	arithExpr a = lire_chaine(buffer);
	affiche(a);
	/*
	printf("\nValeur de l'expression : %f\n",eval_arith(a));
	free_arith(a);
	a = rand_arith(5,100);
	affiche(a);
	free_arith(a);
	*/
	fclose(f);
	exit(0);

}
