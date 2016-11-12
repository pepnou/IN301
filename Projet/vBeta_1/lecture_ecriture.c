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
		for(j=0;j<height_tmp;j++)
		{
			fgets(tmp,101,fichier_lvl);
		}
	}
	
	fscanf(fichier_lvl, "%d %d\n", &niveau.width, &niveau.height);
	
	for(j=0;j<niveau.height+1;j++)
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
			}
		}
	}
	
	fclose(fichier_lvl);
	return niveau;
}
