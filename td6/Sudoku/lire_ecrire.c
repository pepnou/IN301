#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"
#include "constantes.h"

SUDOKU lecture_fichier(char* nom_fichier)
{
	FILE* fichier_lvl = fopen(nom_fichier,"r");
	if(fichier_lvl == NULL)
	{
		fprintf(stderr,"echec ouverture fichier : %s\n",nom_fichier);
		exit(EXIT_FAILURE);
	} 
	
	SUDOKU S;
	S.mode = JOUER;
	
	int i,j;
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			S.la_case[i][8-j].val = fgetc(fichier_lvl) - '0';
		}
		fgetc(fichier_lvl);
	}
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			S.la_case[i][8-j].modifiable = fgetc(fichier_lvl) - '0';
		}
		fgetc(fichier_lvl);
	}
	
	fclose(fichier_lvl);
	return S;
}

void enregistrer_lvl(SUDOKU S)
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","w+");
	if(fichier_lvl == NULL) exit(-1);
	
	int i,j;
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			fputc(S.la_case[i][j].val,fichier_lvl);
		}
		fputc('\n',fichier_lvl);
	}
	
	for(j=0;j<9;j++)
	{
		for(i=0;i<9;i++)
		{
			fputc(S.la_case[i][j].modifiable,fichier_lvl);
		}
		fputc('\n',fichier_lvl);
	}
	
	fclose(fichier_lvl);
} 


 
