#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

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
	
	fscanf(fichier_lvl, "%d %d\n", &niveau.width, &niveau.height);
	fscanf(fichier_lvl, "%d %d\n", &niveau.joueur.x, &niveau.joueur.y);

	for(j=0;j<niveau.height;j++)
	{
		for(i=0;i<niveau.width+1;i++)
		{
			switch(fgetc(fichier_lvl))
			{
				case '-':
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

void ecriture_nbr_lvl(int nbr_LVL)
{
	FILE* fichier_nbr_lvl = fopen("fichier_nbr_niveaux.txt","w+");
	if(fichier_nbr_lvl == NULL) exit(-1);
	
	fprintf(fichier_nbr_lvl,"%d",nbr_LVL);
	
	fclose(fichier_nbr_lvl);
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
					fputc('-',fichier_lvl);
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
