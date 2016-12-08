#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int est_flottant(char* arg);
void somme_flottant(int argc,char** argv);
void expression_correcte(char* arg);
int caractere_ok(char* arg);
int parenthese_ok(char* arg);
int entier_ok(char* arg);

int main(int argc,char** argv)
{
	system("clear");
	
	if(argc < 2) exit(EXIT_FAILURE);
	
	if(!strcmp(argv[1],"-somme"))
	{
		somme_flottant(argc,argv);
	}
	
	if(!strcmp(argv[1],"-expr"))
	{
		expression_correcte(argv[2]);
	}
	
	
	exit(EXIT_SUCCESS);
}

void somme_flottant(int argc,char** argv)
{
	int i;
	double res = 0;
	double tmp;
	for(i=2;i<argc;i++)
	{
		if(est_flottant(argv[i]))
		{
			sscanf(argv[i],"%lf",&tmp);
			res = res + tmp;
		}
		else
		{
			printf("le %d-eme argument n est pas un flottant\n",i);
			exit(EXIT_FAILURE);
		}
	}
	
	printf("%f\n",res);
}

int est_flottant(char* arg)
{
	int lenght = strlen(arg);
	int virgule = 0;
	int i = 0;
	
	if(!((isdigit(arg[i]))||(arg[i] == '-'))) return 0;
	
	for(i=1;i<lenght;i++)
	{
		if(!(isdigit(arg[i])))
		{
			if(arg[i] == '.')
			{
				virgule ++;
				if(virgule>1) return 0;
			}
			else
			{
				return 0;
			}
		}
	}
	
	return 1;
}

void expression_correcte(char* arg)
{	
	if((caractere_ok(arg)) && (parenthese_ok(arg)) && (entier_ok(arg))) printf("l'expression est correcte\n");
}

int caractere_ok(char* arg)
{
	int lenght = strlen(arg);
	int i;
	
	for(i=0;i<lenght;i++)
	{
		if(!((isdigit(arg[i])) || (arg[i] == '(') || (arg[i] == ')') || (arg[i] == '+') || (arg[i] == '-') || (arg[i] == '*') || (arg[i] == '/') || (arg[i] == '.')))
		{
			printf("un caractere non autorisé est present dans l'expression\n");
			return 0;
		}
	}
	return 1;
}

int parenthese_ok(char* arg)
{
	int lenght = strlen(arg);
	int par = 0;
	int i;
	
	for(i=0;i<lenght;i++)
	{
		if(arg[i] == '(') par++;
		if(arg[i] == ')') par--;
		if(par < 0)
		{
			printf("le nombre de parenthèses ouvrantes n est pas égale au nombre de parenthèses fermantes\n");
			return 0;
		}
	}
	if(par != 0)
	{
		printf("le nombre de parenthèses ouvrantes n est pas égale au nombre de parenthèses fermantes\n");
		return 0;
	}
	return 1;
}

int entier_ok(char* arg)
{
	int lenght = strlen(arg);
	int virgule = 0; 
	int i;
	
	for(i=0;i<lenght;i++)
	{
		if(arg[i] == '.') virgule ++;
		else if(! isdigit(arg[i])) virgule = 0;
		
		if(virgule > 1)
		{
			printf("un nombre possède plusieurs virgules\n");
			return 0;
		}
	}
	
	return 1;
}


