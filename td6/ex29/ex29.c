#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct image
{
	char type[10];
	int width;
	int height;
	int val_max_pix;
	int*** tab;
};
typedef struct image IMAGE;

int ouverture_possible(char* nom_fic);
IMAGE lect_image(IMAGE pic,char* nom_fic);
int est_ppm(char* nom_fic);
void passer_ligne(FILE* fichier);
char* changement_nom(char* nom_fic,char* ajout);
void enregistrer_image(IMAGE pic,char* nom_fic);

int main(int argc,char** argv)
{
	if(!((argc == 2)&&(est_ppm(argv[1]))&&(ouverture_possible(argv[1]))))
	{
		printf("ouverture impossible du fichier , mauvais format de fichier ou mauvais format de la ligne de commande\n");
		exit(EXIT_FAILURE);
	}
	
	IMAGE pic = lect_image(pic,argv[1]);
	
	enregistrer_image(pic,argv[1]);
	
	exit(EXIT_SUCCESS);
}

IMAGE lect_image(IMAGE pic,char* nom_fic)
{	
	FILE* fichier = fopen(nom_fic,"r");
	
	fgets(pic.type,10,fichier);
		
	fscanf(fichier,"%d %d %d\n",&pic.width,&pic.height,&pic.val_max_pix);
		
	int i,j;
	pic.tab = malloc(pic.width * sizeof(int**));
	for(i=0;i<pic.width;i++) 
	{
		pic.tab[i] = malloc(pic.height * sizeof(int*));
		for(j=0;j<pic.height;j++) 
		{
			pic.tab[i][j] = malloc(3 * sizeof(int));
		}
	}
		
	char tmp;
	
	for(i=0;i<pic.width;i++) 
	{
		for(j=0;j<pic.height;j++) 
		{
			tmp= fgetc(fichier);
			if(tmp == '#') passer_ligne(fichier);
			else ungetc(tmp,fichier);
			
			fscanf(fichier,"%d %d %d",&pic.tab[i][j][0],&pic.tab[i][j][1],&pic.tab[i][j][2]);
			printf("%d %d %d\n",pic.tab[i][j][0],pic.tab[i][j][1],pic.tab[i][j][2]);
		}
	}
		
	return pic;
}

void passer_ligne(FILE* fichier)
{
	while(fgetc(fichier) != '\n');
}

int est_ppm(char* nom_fic)
{
	if(strlen(nom_fic) < 4) return 0;
	if(strcmp(".ppm",&(nom_fic[strlen(nom_fic) - 4])) != 0) return 0;
	
	return 1;
}

int ouverture_possible(char* nom_fic)
{
	int res = 1;
	if(fopen(nom_fic,"r") == NULL) res = 0;
	return res;
}

void enregistrer_image(IMAGE pic,char* nom_fic)
{
	nom_fic = changement_nom(nom_fic,"_copie.ppm");
	
	FILE* fichier = fopen(nom_fic,"w+");
	
	fprintf(fichier,"%s%d %d\n%d\n",pic.type,pic.width,pic.height,pic.val_max_pix);
	
	int i,j;
	for(i=0;i<pic.width;i++) 
	{
		for(j=0;j<pic.height;j++) 
		{
			fprintf(fichier,"%d %d %d\n",pic.tab[i][j][0],pic.tab[i][j][1],pic.tab[i][j][2]);
		}
	}
	
	fclose(fichier);
}

char* changement_nom(char* nom_fic,char* ajout)
{
	char* nv = malloc((strlen(nom_fic) + 6) * sizeof(char));
	char* tmp = malloc((strlen(nom_fic) - 4) * sizeof(char));

	int i;
	
	for(i = 0;i < strlen(nom_fic) - 4;i++)
	{
		tmp[i] = nom_fic[i];
	}
	
	for(i=0;i<strlen(nom_fic);i++)
	{
		if(nom_fic[i] == '.') nom_fic[i] = '\n';
	}
	nv = strcat(tmp,ajout);
	
	return nv;
}








