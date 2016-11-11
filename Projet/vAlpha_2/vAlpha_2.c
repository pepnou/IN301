#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

#define VIDE 0
#define MUR 1
#define CAISSE 2
#define JOUEUR 3
#define ARRIVE 4

#define largeur 400
#define hauteur 400

struct pos
{
	int x;
	int y;
};
typedef struct pos POS;

struct level
{
	int width;
	int height;
	int T[100][100];
	POS joueur;
};

typedef struct level LEVEL;

void affichelvl(SDL_Surface *ecran,LEVEL niveau);
LEVEL lecture_fichier();
void pause();


void affichelvl(SDL_Surface *ecran,LEVEL niveau);
main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("Test",NULL);

    ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
	
	LEVEL lvl;
	
	lvl=lecture_fichier();
	
	affichelvl(ecran,lvl);
	
	pause();
	
	exit(EXIT_SUCCESS);
}




void affichelvl(SDL_Surface *ecran,LEVEL niveau)
{
	SDL_Surface *vide = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *caisse = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *arrive = NULL;

	vide = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	mur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	
	SDL_FillRect(vide, NULL, SDL_MapRGB(ecran->format, 100, 247, 255));
	SDL_FillRect(mur, NULL, SDL_MapRGB(ecran->format, 142, 142, 142));
	SDL_FillRect(caisse, NULL, SDL_MapRGB(ecran->format, 237, 161, 55));
	SDL_FillRect(joueur, NULL, SDL_MapRGB(ecran->format, 58, 255, 77));
	SDL_FillRect(arrive, NULL, SDL_MapRGB(ecran->format, 228, 0, 8));
	
	SDL_Rect positionCase;
	
	int i,j;
	
	for(i=0;i<niveau.width;i++)
    {
		for(j=0;j<niveau.height;j++)
		{
			positionCase.x=i*(largeur/niveau.width);
			positionCase.y=j*(hauteur/niveau.height);
			
			switch(niveau.T[i][j])
			{
				case VIDE:
					SDL_BlitSurface(vide,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case MUR:
					SDL_BlitSurface(mur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case CAISSE:
					SDL_BlitSurface(caisse,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case JOUEUR:
					SDL_BlitSurface(joueur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case ARRIVE:
					SDL_BlitSurface(arrive,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				default :
					printf("you forgot to blit a surface");
					break;
			}
		}
	}
	
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(joueur);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(arrive);
}


LEVEL lecture_fichier()
{
	FILE* fichier_lvl = fopen("fichier_niveaux.txt","r");
	if(fichier_lvl == NULL) exit(-1);
	
	LEVEL niveau;
	int i,j;
	
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


void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


































