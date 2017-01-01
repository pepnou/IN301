#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constantes.h"


LEVEL init_lvl(LEVEL niveau)
{
	int i,j;
	
	for(j=0;j<largeur_max;j++)
	{
		for(i=0;i<hauteur_max;i++)
		{
			niveau.T[i][j] = 0;
		}
	}
	niveau.direction_joueur = 1;
	
	return niveau;
}

int lecture_nbr_lvl()
{
	FILE* fichier_lvl = fopen(fichier_a_lire,"r");
	if(fichier_lvl == NULL) exit(-1);
	
	int nbr_lvl = 0;
	char c = fgetc(fichier_lvl);
	
	while(c != EOF)
	{
		if(c == ';') nbr_lvl ++;
		c = fgetc(fichier_lvl);
	}
	
	fclose(fichier_lvl);
	return nbr_lvl;
}

LEVEL lecture_fichier(int num_lvl)
{	
	FILE* fichier_lvl = fopen(fichier_a_lire,"r");
	if(fichier_lvl == NULL) exit(-1);
		
	int i,j,w_tmp,h_tmp,continuer;
	LEVEL niveau;
	
	niveau = init_lvl(niveau);
	
	niveau.width = 0;
		
	char* tmp;
	if(!(tmp=malloc(100 * sizeof(char)))) exit(EXIT_FAILURE);
		
	int lvl_courant = 0;
	
	continuer = 1;
	char c = ' ';
	
	while(num_lvl != lvl_courant)
	{
		c = fgetc(fichier_lvl);
		if(c == ';') lvl_courant++;
	}
	
	while(c != '\n')
	{
		c = fgetc(fichier_lvl);
	}
	while((c != '#')&&(c != ' '))
	{
		c = fgetc(fichier_lvl);
	}
	ungetc(c,fichier_lvl);
	
	i = 0;
	j = 0;
		
	while((c != EOF)&&(c != ';'))
	{
		while(c != '\n')
		{
			c = fgetc(fichier_lvl);			
			switch(c)
			{
				case ' ':
					niveau.T[i][j]=VIDE;
					break;
				case '#':
					niveau.T[i][j]=MUR;
					break;
				case '$':
					niveau.T[i][j]=CAISSE;
					break;
				case '@':
					niveau.T[i][j]=JOUEUR;
					niveau.joueur.x = i;
					niveau.joueur.y = j;
					break;
				case '.':
					niveau.T[i][j]=ARRIVE;
					break;
				case '+':
					niveau.T[i][j]=JOUEUR_ARRIVE;
					break;
				case '*':
					niveau.T[i][j]=CAISSE_ARRIVE;
					break;
				default:
					i--;
					break;
			}
			i++;
			if(i>largeur_max-1) exit(EXIT_FAILURE);
		}
		
		if(i>niveau.width)
		{
			niveau.width = i;
		}
		i = 0;
		j++;
		if(j>hauteur_max-1) exit(EXIT_FAILURE);
		
		c = fgetc(fichier_lvl);
		if(c == ';') j -= 1;
		else ungetc(c,fichier_lvl);
	}
		
	niveau.height = j;
	
	fclose(fichier_lvl);
	return niveau;
}

void enregistrer_lvl(LEVEL lvl)
{
	FILE* fichier_lvl = fopen(fichier_pour_ecrire,"a");
	if(fichier_lvl == NULL) exit(-1);
	
	int nbr_lvl = lecture_nbr_lvl();
	
	fputc(13,fichier_lvl);fputc(10,fichier_lvl);fputc(';',fichier_lvl);fputc(' ',fichier_lvl);fprintf(fichier_lvl,"%d",nbr_lvl + 1);fputc(13,fichier_lvl);fputc(10,fichier_lvl);fputc(13,fichier_lvl);fputc(10,fichier_lvl);
	
	int i,j;
	
	for(j=0;j<lvl.height;j++)
	{
		for(i=0;i<lvl.width;i++)
		{
			switch(lvl.T[i][j])
			{
				case VIDE:
					fputc(' ',fichier_lvl);
					break;
				case MUR:
					fputc('#',fichier_lvl);
					break;
				case CAISSE:
					fputc('$',fichier_lvl);
					break;
				case JOUEUR:
					fputc('@',fichier_lvl);
					break;
				case ARRIVE:
					fputc('.',fichier_lvl);
					break;
				case JOUEUR_ARRIVE:
					fputc('+',fichier_lvl);
					break;
				case CAISSE_ARRIVE:
					fputc('*',fichier_lvl);
					break;
			}
		}
		fprintf(fichier_lvl,"\n");
	}
	fclose(fichier_lvl);
}

