#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "lecture_ecriture.h"

void lancement_option_1(int argc, char** argv,SDL_Surface *ecran)
{
	int lvl_a_lire = 1;
	
	fichier_a_lire = argv[1];
	NBR_NIVEAUX = lecture_nbr_lvl(argv[1]);
	
	if(NBR_NIVEAUX>=1)play_mode(ecran,lvl_a_lire);
	else
	{
		affiche_play_menu(&ecran,0);
		SDL_Delay(2000);
	}
}

void lancement_option_2(int argc, char** argv,SDL_Surface *ecran)
{
	int lvl_a_lire = 1;
	
	if(!(strcmp(&(argv[3][strlen(argv[3]) - strlen(extension_fichier)]),extension_fichier)))
	{
		fichier_a_lire = argv[3];
		NBR_NIVEAUX = lecture_nbr_lvl(argv[3]);
		sscanf(argv[2],"%d",&lvl_a_lire);
		
		if(NBR_NIVEAUX>=lvl_a_lire)play_mode(ecran,lvl_a_lire);
		else
		{
			affiche_play_menu(&ecran,0);
			SDL_Delay(2000);
		}
	}
	else printf("le fichier passé en option ne posséde pas la bonne extension (.xsb)\n");
}

void lancement_option_3(int argc, char** argv,SDL_Surface *ecran)
{
	if(!(strcmp(&(argv[2][strlen(argv[2]) - strlen(extension_fichier)]),extension_fichier)))
	{
		fichier_pour_ecrire = argv[2];
		
		menu_taille_lvl(ecran);
	}
	else printf("le fichier passé en option ne posséde pas la bonne extension (.xsb)\n");
}

void lancement_base(int argc,SDL_Surface *ecran)
{
	if(argc>1)
	{
		printf("Les options passées sur la ligne de commande ne sont pas valide\n");
		printf("Pour information , l'extension des fichier doit necessairement etre \'xsb\' , et le format des option doit etre fichier.xsb ou -n num fichier.xsb ou -c fichier.xsb\n");
		printf("Le programme utilisera default.xsb pour la lecture et l'enregistrement des niveaux\n");
	}
	main_menu(ecran);
}

void gestion_ligne_commande(int argc, char** argv,SDL_Surface *ecran)
{
	if((argc>=2)&&(!(strcmp(&(argv[1][strlen(argv[1]) - strlen(extension_fichier)]),extension_fichier))))
	{
		lancement_option_1(argc,argv,ecran);
	}
	else if((argc>=4)&&(!(strcmp(argv[1],"-n"))))
	{
		lancement_option_2(argc,argv,ecran);
	}
	else if((argc>=3)&&(!(strcmp(argv[1],"-c"))))
	{
		lancement_option_3(argc,argv,ecran);
	}
	else
	{
		lancement_base(argc,ecran);
	}
}
