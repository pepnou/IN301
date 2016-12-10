#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constantes.h"


/*
LEVEL lecture_fichier(int num_lvl)
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","r");
	if(fichier_lvl == NULL) exit(-1);
	
	LEVEL niveau;
	int i,j,height_tmp;
	
	char tmp[101];
	
	for(i=1;i<num_lvl;i++)
	{
		fscanf(fichier_lvl, "%d %d\n", &j, &height_tmp);
		fgets(tmp,101,fichier_lvl);
		for(j=0;j<height_tmp;j++)
		{
			fgets(tmp,101,fichier_lvl);
		}
	}
	
	//fscanf(fichier_lvl, "%d %d\n", &niveau.width, &niveau.height);
	//fscanf(fichier_lvl, "%d %d\n", &niveau.joueur.x, &niveau.joueur.y);
	
	fscanf(fichier_lvl, "%d %d", &niveau.width, &niveau.height);fgetc(fichier_lvl);
	fscanf(fichier_lvl, "%d %d", &niveau.joueur.x, &niveau.joueur.y);fgetc(fichier_lvl);

	for(j=0;j<niveau.height;j++)
	{
		for(i=0;i<niveau.width+1;i++)
		{
			switch(fgetc(fichier_lvl))
			{
				case ' ':
					niveau.T[i][j]=VIDE;
					break;
				case '#':
					niveau.T[i][j]=MUR;
					break;
				case '&':
					niveau.T[i][j]=CAISSE;
					break;
				case '@':
					niveau.T[i][j]=JOUEUR;
					break;
				case '.':
					niveau.T[i][j]=ARRIVE;
					break;
				case '*':
					niveau.T[i][j]=JOUEUR_ARRIVE;
					break;
				case '+':
					niveau.T[i][j]=CAISSE_ARRIVE;
					break;
			}
		}
	}
	
	fclose(fichier_lvl);
	return niveau;
}
*/

LEVEL lecture_fichier(int num_lvl)
{
	//FILE* fichier_lvl = fopen("fichier_niveaux.txt","r");
	
	FILE* fichier_lvl = fopen("sasquatch1.xsb","r");
	if(fichier_lvl == NULL) exit(-1);
	
	int i,j,w_tmp,h_tmp,continuer;
	LEVEL niveau;

	niveau.width = 0;
	
	char* tmp;
	if(!(tmp=malloc(100 * sizeof(char)))) exit(EXIT_FAILURE);
	
	int lvl_courant = 0;
	
	continuer = 1;
	char c = ' ';
	
	while(num_lvl != lvl_courant)
	{
		while(c != ';')
		{
			c = fgetc(fichier_lvl);
		}
		c = 'y';
		fscanf(fichier_lvl,"%d",&lvl_courant);
	}
	
	while((c != ' ')&&(c != '#')) c = fgetc(fichier_lvl);
	ungetc(c,fichier_lvl);
	
	i = 0;
	j = 0;
	
	while(c != ';')
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
		}
		if(i>niveau.width)
		{
			niveau.width = i;
		}
		i = 0;
		j++;
		
		c = fgetc(fichier_lvl);
		if(c == ';') j -= 1;
		else ungetc(c,fichier_lvl);
	}
	niveau.height = j;
	
	fclose(fichier_lvl);
	return niveau;
}

int lecture_nbr_lvl()
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","r");
	if(fichier_lvl == NULL) exit(-1);
	
	int nbr_lvl = 0;
	int tmp1,tmp2;
	int j;
	char tmp[101];
	
	while(!(fscanf(fichier_lvl,"%d %d\n",&tmp1,&tmp2) == EOF))
	{
		for(j=0;j<tmp2+1;j++) 
		{
			fgets(tmp,101,fichier_lvl);
		}
		nbr_lvl++;
	}
	fclose(fichier_lvl);

	return nbr_lvl;
}

void enregistrer_lvl(LEVEL lvl)
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","a");
	if(fichier_lvl == NULL) exit(-1);
	
	fprintf(fichier_lvl,"%d %d\n",lvl.width,lvl.height);
	fprintf(fichier_lvl,"%d %d\n",lvl.joueur.x,lvl.joueur.y);
	
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
					fputc('&',fichier_lvl);
					break;
				case JOUEUR:
					fputc('@',fichier_lvl);
					break;
				case ARRIVE:
					fputc('.',fichier_lvl);
					break;
				case JOUEUR_ARRIVE:
					fputc('*',fichier_lvl);
					break;
				case CAISSE_ARRIVE:
					fputc('+',fichier_lvl);
					break;
			}
		}
		fprintf(fichier_lvl,"\n");
	}
	
	
	fclose(fichier_lvl);
}

void efface_lvl()
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","w+");
	fclose(fichier_lvl);
}
