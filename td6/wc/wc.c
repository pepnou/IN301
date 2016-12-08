#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ouverture_possible(char* nom_fic);
int nbr_caractere(char* nom_fic);

int main(int argc,char** argv)
{
	if(!((argc == 2)&&(ouverture_possible(argv[1]))))
	{
		printf("ouverture impossible du fichier ou mauvais format de la ligne de commande\n");
		exit(EXIT_FAILURE);
	}
	
	printf("nombre de caractère dans la fichier \"%s\" : %d\n",argv[1],nbr_caractere(argv[1]));
	
	exit(EXIT_SUCCESS);
} 

int ouverture_possible(char* nom_fic)
{
	int res = 1;
	if(fopen(nom_fic,"r") == NULL) res = 0;
	return res;
}

int nbr_caractere(char* nom_fic)
{
	int res = 0;
	
	FILE* fichier = fopen(nom_fic,"r");
	
	while(!(fgetc(fichier) == EOF)) res++;
	
	fclose(fichier);
	
	return res;
}







