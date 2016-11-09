#include "graphics.h"
#include <math.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

//a revoir : les define sont a coté de la plaque

#define VIDE 0
#define MUR 1
#define CAISSE 2
#define JOUEUR 3
#define ARRIVE 4
#define CAISSE_ARRIVE 5
#define JOUEUR_ARRIVE 6

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
LEVEL deplacer_joueur(LEVEL niveau,POS deplacement);
POS attendre_evenement();
int victoire(LEVEL niveau);

int main()
{
	SDL_Surface *ecran = NULL;

	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("Test",NULL);

    ecran = SDL_SetVideoMode(largeur,hauteur,32,SDL_HWSURFACE);
    
    
    int i,j;
    LEVEL lvl;
    lvl.width = 10;
    lvl.height = 10;
    for(i=0;i<lvl.width;i++)
    {
		for(j=0;j<lvl.height;j++)
		{
			if((i==0)||(i==lvl.width-1)||(j==0)||(j==lvl.height-1))
			{
				lvl.T[i][j]=3;
			}
			else
			{
				lvl.T[i][j]=alea_int(2);
			}
		}
	}
	lvl.joueur.x=alea_int(lvl.width-2)+1;
	lvl.joueur.y=alea_int(lvl.height-2)+1;
    lvl.T[lvl.joueur.x][lvl.joueur.y]=2;
    lvl.T[alea_int(lvl.width-2)+1][alea_int(lvl.height-2)+1] = 4;
    
	affichelvl(ecran,lvl);
	//POS postest;
	
	while(!victoire(lvl))
	{
		lvl = deplacer_joueur(lvl,attendre_evenement());
		
		affichelvl(ecran,lvl);
		
		
		
		/*
		postest = attendre_evenement();
		printf("x:%d y:%d\n",postest.x,postest.y);
		*/
	}
	
	printf("you win\n");
	
	
	TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

int victoire(LEVEL niveau)
{
	int i,j;
	
	for(i=1;i<niveau.width-1;i++)
    {
		for(j=1;j<niveau.height-1;j++)
		{
			if(niveau.T[i][j]==4)return 0;
		}
	}
	return 1;
}

void affichelvl(SDL_Surface *ecran,LEVEL niveau)
{
	SDL_Surface *vide = NULL;
	SDL_Surface *mur = NULL;
	SDL_Surface *caisse = NULL;
	SDL_Surface *joueur = NULL;
	SDL_Surface *arrive = NULL;
	SDL_Surface *caisse_arrive = NULL;
	vide = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	mur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	caisse = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	joueur = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	caisse_arrive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur/niveau.width, hauteur/niveau.height, 32, 0, 0, 0, 0);
	SDL_FillRect(vide, NULL, SDL_MapRGB(ecran->format, 100, 247, 255));
	SDL_FillRect(mur, NULL, SDL_MapRGB(ecran->format, 142, 142, 142));
	SDL_FillRect(caisse, NULL, SDL_MapRGB(ecran->format, 237, 161, 55));
	SDL_FillRect(joueur, NULL, SDL_MapRGB(ecran->format, 58, 255, 77));
	SDL_FillRect(arrive, NULL, SDL_MapRGB(ecran->format, 228, 0, 8));
	SDL_FillRect(caisse_arrive, NULL, SDL_MapRGB(ecran->format, 0, 53, 1));
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
				case 0:
					SDL_BlitSurface(vide,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case 1:
					SDL_BlitSurface(caisse,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case 2:
					SDL_BlitSurface(joueur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case 3:
					SDL_BlitSurface(mur,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case 4:
					SDL_BlitSurface(arrive,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
				case 5:
					SDL_BlitSurface(caisse_arrive,NULL,ecran,&positionCase);
					SDL_Flip(ecran);
					break;
					/*
				default :
					printf("you forgot to blit a surface");
					break;
					*/
			}
		}
	}
	
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(joueur);
}


LEVEL deplacer_joueur(LEVEL niveau,POS deplacement)
{
	//printf("x:%d\n",niveau.joueur.x + deplacement.x);
	//printf("y:%d\n",niveau.joueur.y + deplacement.y);
	//printf("T[x][y]:%d\n",niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y]);
	
	if(niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] == 0)
	{
		niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = 2;
		niveau.T[niveau.joueur.x][niveau.joueur.y] = 0;
		niveau.joueur.x=niveau.joueur.x + deplacement.x;
		niveau.joueur.y=niveau.joueur.y + deplacement.y;
	}
	
	//printf("T[x][y]':%d\n",niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y]);
	else
	{
		switch(niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y])
		{
			case 0:
				niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = 2;
				niveau.T[niveau.joueur.x][niveau.joueur.y] = 0;
				niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = 1;
				niveau.joueur.x=niveau.joueur.x + deplacement.x;
				niveau.joueur.y=niveau.joueur.y + deplacement.y;
				break;
			case 4:
				niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = 2;
				niveau.T[niveau.joueur.x][niveau.joueur.y] = 0;
				niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = 5;
				niveau.joueur.x=niveau.joueur.x + deplacement.x;
				niveau.joueur.y=niveau.joueur.y + deplacement.y;
				break;
		}
	}
	return niveau;
}

POS attendre_evenement()
{
	POS deplacement_joueur;
	deplacement_joueur.x=0;
	deplacement_joueur.y=0;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event action;
	int continuer=1;
	
	while(continuer)
	{
		SDL_WaitEvent(&action);
		if(action.type==SDL_KEYDOWN)
        {
			switch(action.key.keysym.sym)
            {
				case SDLK_UP:
					continuer = 0;
					deplacement_joueur.y=-1;
					break;
				case SDLK_DOWN:
                    continuer = 0;
                    deplacement_joueur.y=1;
                    break;
				case SDLK_RIGHT:
                    continuer = 0;
                    deplacement_joueur.x=1;
                    break;
                case SDLK_LEFT:
                    continuer = 0;
                    deplacement_joueur.x=-1;
                    break;
                default:
					break;
            }
		}
	}
	
	
	return deplacement_joueur;
}










/*
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *quit = NULL;
    SDL_Surface *boutton = NULL;

    quit = SDL_LoadBMP("quit-2.bmp");
    boutton = SDL_LoadBMP("bouton.bmp");

    SDL_Rect positionQuit;
    positionQuit.x = X-30;
    positionQuit.y = 5;

    SDL_SetColorKey(quit, SDL_SRCCOLORKEY, SDL_MapRGB(quit->format, 0, 255, 0));
    SDL_BlitSurface(quit,NULL,ecran,&positionQuit);


    SDL_SetColorKey(boutton, SDL_SRCCOLORKEY, SDL_MapRGB(boutton->format, 255, 0, 0));
    SDL_Rect positionBoutton;

    positionBoutton.x = (X/2)-(200/2);
    positionBoutton.y = 150;

    SDL_BlitSurface(boutton,NULL,ecran,&positionBoutton);
*/

/*
int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *rectangle = NULL;
    SDL_Rect position;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    // Allocation de la surface
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    position.x = 0; // Les coordonnées de la surface seront (0, 0)
    position.y = 0;
    // Remplissage de la surface avec du blanc
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(rectangle, NULL, ecran, &position); // Collage de la surface sur l'écran

    SDL_Flip(ecran); // Mise à jour de l'écran

    pause();

    SDL_FreeSurface(rectangle); // Libération de la surface
    SDL_Quit();

    return EXIT_SUCCESS;
}
*/

/*

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define X 300
#define Y 500

double argentdispo;


void ecran_principal(SDL_Surface *ecran);
void ecran_ajout(SDL_Surface *ecran);
void ecran_depense(SDL_Surface *ecran);
void ecran_historique(SDL_Surface *ecran);
void ecran_date(SDL_Surface *ecran);
void pause();
void dessinne_ecran_ajout(SDL_Surface *ecran);
void dessinne_ecran_commentaire(SDL_Surface *ecran);
void ecran_commentaire(SDL_Surface *ecran);
void dessinne_ecran_historique(SDL_Surface *ecran);

int main ( int argc, char *argv[] )
{

    if(TTF_Init() == -1)
{
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
}


    SDL_Surface *ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(SDL_LoadBMP("MoneyCountIco_2.bmp"),NULL);
    SDL_WM_SetCaption("Money Count",NULL);

    ecran = SDL_SetVideoMode(X,Y,32,SDL_HWSURFACE);

    if(ecran==NULL)
    {
        fprintf(stderr,"Impossible de charger le mode video : %s \n",SDL_GetError());
        exit(EXIT_FAILURE);
    }



    FILE* fichier_a = NULL;

    fichier_a = fopen("argent.txt","r");

    if(fichier_a != NULL)
    {
        fscanf(fichier_a,"%lf",&argentdispo);
        fclose(fichier_a);
    }




    ecran_principal(ecran);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void ecran_principal(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *quit = NULL;
    SDL_Surface *boutton = NULL;

    quit = SDL_LoadBMP("quit-2.bmp");
    boutton = SDL_LoadBMP("bouton.bmp");

    SDL_Rect positionQuit;
    positionQuit.x = X-30;
    positionQuit.y = 5;

    SDL_SetColorKey(quit, SDL_SRCCOLORKEY, SDL_MapRGB(quit->format, 0, 255, 0));
    SDL_BlitSurface(quit,NULL,ecran,&positionQuit);


    SDL_SetColorKey(boutton, SDL_SRCCOLORKEY, SDL_MapRGB(boutton->format, 255, 0, 0));
    SDL_Rect positionBoutton;

    positionBoutton.x = (X/2)-(200/2);
    positionBoutton.y = 150;

    SDL_BlitSurface(boutton,NULL,ecran,&positionBoutton);

    positionBoutton.x = (X/2)-(200/2);
    positionBoutton.y = positionBoutton.y+98+10;

    SDL_BlitSurface(boutton,NULL,ecran,&positionBoutton);

    positionBoutton.x = (X/2)-(200/2);
    positionBoutton.y = positionBoutton.y+98+10;

    SDL_BlitSurface(boutton,NULL,ecran,&positionBoutton);

    positionBoutton.x = (X/2)-(200/2);
    positionBoutton.y = 20;

    SDL_BlitSurface(boutton,NULL,ecran,&positionBoutton);



    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",30);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;


    texte = TTF_RenderText_Blended(police,"Ajout",couleurnoire);

    positionTexte.x = ((X/2)-(200/2))+55;
    positionTexte.y = 150+30;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


    texte = TTF_RenderText_Blended(police,"Depense",couleurnoire);

    positionTexte.x = ((X/2)-(200/2))+35;
    positionTexte.y = (positionTexte.y+98+10);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


    texte = TTF_RenderText_Blended(police,"Historique",couleurnoire);

    positionTexte.x = ((X/2)-(200/2))+10;
    positionTexte.y = (positionTexte.y+98+10);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);



    FILE* fichier_a = NULL;

    fichier_a = fopen("argent.txt","w+");

    fprintf(fichier_a,"%f",argentdispo);

    fclose(fichier_a);



    char affichage[30];

    sprintf(affichage,"%f",argentdispo);

    int j;
    int position_virgule_affichage;


    for(j=0;j<30;j++)
    {
        if(affichage[j]=='.')position_virgule_affichage=j;
        if(j>position_virgule_affichage+2)affichage[j]=' ';
    }


    texte = TTF_RenderText_Blended(police,affichage,couleurnoire);

    positionTexte.x = ((X/2)-(200/2))+30;
    positionTexte.y = 20+30;

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


    SDL_Flip(ecran);








    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        if((event.type == SDL_MOUSEBUTTONUP)&&(event.button.button == SDL_BUTTON_LEFT))
        {
            if((event.button.x>(X/2)-(200/2))&&(event.button.x<(X/2)+(200/2)))
            {
                if((event.button.y>150)&&(event.button.y<150+98))
                {
                    SDL_FreeSurface(quit);
                    SDL_FreeSurface(boutton);
                    SDL_FreeSurface(texte);

                    ecran_ajout(ecran);

                    continuer=0;
                }
                if((event.button.y>(150+(108*1)))&&(event.button.y<(150+(108*1)+98)))
                {
                    SDL_FreeSurface(quit);
                    SDL_FreeSurface(boutton);
                    SDL_FreeSurface(texte);

                    ecran_depense(ecran);

                    continuer=0;
                }
                if((event.button.y>(150+(108*2)))&&(event.button.y<(150+(108*2)+98)))
                {
                    SDL_FreeSurface(quit);
                    SDL_FreeSurface(boutton);
                    SDL_FreeSurface(texte);

                    ecran_historique(ecran);

                    continuer=0;
                }
            }
            if((event.button.x>(X-30))&&(event.button.x<(X-30)+25)&&(event.button.y>5)&&(event.button.y<30))
            {
                continuer=0;
            }
        }
    }
}

void ecran_ajout(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(200/2);
    position_petit_ecran.y = (Y/2)-(98/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);



    char tab[8] = "";
    int continuer = 1;
    SDL_Event event;
    int positioncurseur = 0;
    int positionvirgule = 7;


    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;



    positionTexte.x = (X/2)-100;
    positionTexte.y = 20;

    texte = TTF_RenderText_Blended(police,"somme ajoutée",couleurnoire);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    SDL_Flip(ecran);


    positionTexte.x = 100;
    positionTexte.y = Y/2-15;



    while(continuer)
    {

        SDL_WaitEvent(&event);
        if((event.type == SDL_KEYDOWN)&&(positioncurseur<7)&&(positioncurseur < positionvirgule+3))
        {
            switch(event.key.keysym.sym)
            {
//                case SDLK_RETURN:
//                    if(positionvirgule==7)
//                    {
//                        positionvirgule=positioncurseur;
//                    }
//                    continuer = 0;

//                    break;

                case SDLK_BACKSPACE:
                    if(positioncurseur!=0)
                    {
                        positioncurseur--;

                        if(tab[positioncurseur]=='.')positionvirgule=7;

                        tab[positioncurseur] = ' ';

                        dessinne_ecran_ajout(ecran);

                        positionTexte.x = (X/2)-100;
                        positionTexte.y = 20;

                        texte = TTF_RenderText_Blended(police,"somme ajoutée",couleurnoire);

                        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                        SDL_Flip(ecran);


                        positionTexte.x = 100;
                        positionTexte.y = Y/2-15;

                    }

                    break;



                case SDLK_KP_PERIOD:
                    if((positionvirgule == 7)&&(positioncurseur != 0))
                    {
                        positionvirgule=positioncurseur;
                        tab[positioncurseur]= '.';
                        positioncurseur++;
                    }
                    break;
                case SDLK_KP0:
                    tab[positioncurseur]= '0';
                    positioncurseur++;
                    break;
                case SDLK_KP1:
                    tab[positioncurseur]= '1';
                    positioncurseur++;
                    break;
                case SDLK_KP2:
                    tab[positioncurseur]= '2';
                    positioncurseur++;
                    break;
                case SDLK_KP3:
                    tab[positioncurseur]= '3';
                    positioncurseur++;
                    break;
                case SDLK_KP4:
                    tab[positioncurseur]= '4';
                    positioncurseur++;
                    break;
                case SDLK_KP5:
                    tab[positioncurseur]= '5';
                    positioncurseur++;
                    break;
                case SDLK_KP6:
                    tab[positioncurseur]= '6';
                    positioncurseur++;
                    break;
                case SDLK_KP7:
                    tab[positioncurseur]= '7';
                    positioncurseur++;
                    break;
                case SDLK_KP8:
                    tab[positioncurseur]= '8';
                    positioncurseur++;
                    break;
                case SDLK_KP9:
                    tab[positioncurseur]= '9';
                    positioncurseur++;
                    break;
            }

        }

        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_RETURN))
        {
            if(positionvirgule==7)
            {
                positionvirgule=positioncurseur;
            }
            continuer = 0;
        }

        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_BACKSPACE))
        {
            if(positioncurseur!=0)
            {
                positioncurseur--;

                if(tab[positioncurseur]=='.')positionvirgule=7;

                tab[positioncurseur] = ' ';

                dessinne_ecran_ajout(ecran);

                positionTexte.x = (X/2)-100;
                positionTexte.y = 20;

                texte = TTF_RenderText_Blended(police,"somme ajoutée",couleurnoire);

                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                SDL_Flip(ecran);

                positionTexte.x = 100;
                positionTexte.y = Y/2-15;

            }
        }





//        if(positioncurseur==7)continuer = 0;
//        if(positioncurseur==positionvirgule+3)continuer = 0;


        texte = TTF_RenderText_Blended(police,tab,couleurnoire);

        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        SDL_Flip(ecran);

    }

    int i = 0;
    double ajout = 0;

//    printf(" %d \n",positionvirgule);

    for(i=0;i<7;i++)
    {
        if(i<positionvirgule)
        {
            ajout = ajout + (tab[i]-48)*pow(10,positionvirgule-(i+1)) ;
        }

        if(i>positionvirgule)
        {
            if((i == positionvirgule + 1) && (tab[i] >= 48))
            {
                ajout = ajout + (tab[i]-48)*0.1;
            }
            if((i == positionvirgule + 2) && (tab[i] >= 48))
            {
                ajout = ajout + (tab[i]-48)*0.01;
            }
        }
    }




    FILE* fichier_h = NULL;
    fichier_h = fopen("historique.txt","a+");
//    fseek(fichier_h,0,SEEK_END);
    fprintf(fichier_h,"%lf \n",ajout);
    fclose(fichier_h);



//    printf(" %f \n",ajout);
    argentdispo = argentdispo + ajout;


    SDL_FreeSurface(texte);


    ecran_date(ecran);
}

void ecran_depense(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(200/2);
    position_petit_ecran.y = (Y/2)-(98/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);



    char tab[8] = "";
    int continuer = 1;
    SDL_Event event;
    int positioncurseur = 0;
    int positionvirgule = 7;


    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;



    positionTexte.x = (X/2)-100;
    positionTexte.y = 20;

    texte = TTF_RenderText_Blended(police,"somme depensée",couleurnoire);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    SDL_Flip(ecran);



    positionTexte.x = 100;
    positionTexte.y = Y/2-15;



    while(continuer)
    {

        SDL_WaitEvent(&event);
        if((event.type == SDL_KEYDOWN)&&(positioncurseur<7)&&(positioncurseur < positionvirgule+3))
        {
            switch(event.key.keysym.sym)
            {

                case SDLK_RETURN:
                    if(positionvirgule==7)
                    {
                        positionvirgule=positioncurseur;
                    }
                    continuer = 0;

                    break;

                case SDLK_BACKSPACE:
                    if(positioncurseur!=0)
                    {
                        positioncurseur--;

                        if(tab[positioncurseur]=='.')positionvirgule=7;

                        tab[positioncurseur] = ' ';

                        dessinne_ecran_ajout(ecran);


                        positionTexte.x = (X/2)-100;
                        positionTexte.y = 20;

                        texte = TTF_RenderText_Blended(police,"somme depensée",couleurnoire);

                        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                        SDL_Flip(ecran);



                        positionTexte.x = 100;
                        positionTexte.y = Y/2-15;

                    }

                    break;

                case SDLK_KP_PERIOD:
                    if((positionvirgule == 7)&&(positioncurseur != 0))
                    {
                        positionvirgule=positioncurseur;
                        tab[positioncurseur]= '.';
                        positioncurseur++;
                    }
                    break;
                case SDLK_KP0:
                    tab[positioncurseur]= '0';
                    positioncurseur++;
                    break;
                case SDLK_KP1:
                    tab[positioncurseur]= '1';
                    positioncurseur++;
                    break;
                case SDLK_KP2:
                    tab[positioncurseur]= '2';
                    positioncurseur++;
                    break;
                case SDLK_KP3:
                    tab[positioncurseur]= '3';
                    positioncurseur++;
                    break;
                case SDLK_KP4:
                    tab[positioncurseur]= '4';
                    positioncurseur++;
                    break;
                case SDLK_KP5:
                    tab[positioncurseur]= '5';
                    positioncurseur++;
                    break;
                case SDLK_KP6:
                    tab[positioncurseur]= '6';
                    positioncurseur++;
                    break;
                case SDLK_KP7:
                    tab[positioncurseur]= '7';
                    positioncurseur++;
                    break;
                case SDLK_KP8:
                    tab[positioncurseur]= '8';
                    positioncurseur++;
                    break;
                case SDLK_KP9:
                    tab[positioncurseur]= '9';
                    positioncurseur++;
                    break;
            }
        }


        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_RETURN))
        {
            if(positionvirgule==7)
            {
                positionvirgule=positioncurseur;
            }
            continuer = 0;
        }

        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_BACKSPACE))
        {
            if(positioncurseur!=0)
            {
                positioncurseur--;

                if(tab[positioncurseur]=='.')positionvirgule=7;

                tab[positioncurseur] = ' ';

                dessinne_ecran_ajout(ecran);

                positionTexte.x = (X/2)-100;
                positionTexte.y = 20;

                texte = TTF_RenderText_Blended(police,"somme depensée",couleurnoire);

                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                SDL_Flip(ecran);

                positionTexte.x = 100;
                positionTexte.y = Y/2-15;

            }
        }








//        if(positioncurseur==7)continuer = 0;
//        if(positioncurseur==positionvirgule+3)continuer = 0;


        texte = TTF_RenderText_Blended(police,tab,couleurnoire);

        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        SDL_Flip(ecran);

    }

    int i = 0;
    double ajout = 0;

//    printf(" %d \n",positionvirgule);

    for(i=0;i<7;i++)
    {
        if(i<positionvirgule)
        {
            ajout = ajout + (tab[i]-48)*pow(10,positionvirgule-(i+1)) ;
        }

        if(i>positionvirgule)
        {
            if((i == positionvirgule + 1) && (tab[i] >= 48))
            {
                ajout = ajout + (tab[i]-48)*0.1;
            }
            if((i == positionvirgule + 2) && (tab[i] >= 48))
            {
                ajout = ajout + (tab[i]-48)*0.01;
            }
        }
    }





    FILE* fichier_h = NULL;
    fichier_h = fopen("historique.txt","a+");
//    fseek(fichier_h,0,SEEK_END);
    fprintf(fichier_h,"-%lf \n",ajout);
    fclose(fichier_h);




//    printf(" %f \n",ajout);
    argentdispo = argentdispo - ajout;

    ecran_date(ecran);


    SDL_FreeSurface(texte);


}

void ecran_date(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(200/2);
    position_petit_ecran.y = (Y/2)-(98/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);







    char tab[11] = "";
    int continuer = 1;
    SDL_Event event;
    int positioncurseur = 0;

    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;

    positionTexte.x = (X/2)-25;
    positionTexte.y = 20;

    texte = TTF_RenderText_Blended(police,"date",couleurnoire);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    SDL_Flip(ecran);



    positionTexte.x = 75;
    positionTexte.y = (Y/2)-15;



    while(continuer)
    {

        SDL_WaitEvent(&event);
        if((event.type == SDL_KEYDOWN)&&(positioncurseur < 10))
        {
            switch(event.key.keysym.sym)
            {

                case SDLK_RETURN:
                    continuer = 0;
                    break;

                case SDLK_BACKSPACE:
                    if(positioncurseur!=0)
                    {
                        positioncurseur--;
                        tab[positioncurseur] = ' ';
                        dessinne_ecran_ajout(ecran);

                        positionTexte.x = (X/2)-25;
                        positionTexte.y = 20;

                        texte = TTF_RenderText_Blended(police,"date",couleurnoire);

                        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                        SDL_Flip(ecran);

                        positionTexte.x = 75;
                        positionTexte.y = (Y/2)-15;

                    }
                    break;

                case SDLK_SPACE:
                    tab[positioncurseur] = ' ';
                    positioncurseur++;
                    break;

                case SDLK_KP_DIVIDE:
                    tab[positioncurseur] = '/';
                    positioncurseur++;
                    break;


                case SDLK_KP0:
                    tab[positioncurseur]= '0';
                    positioncurseur++;
                    break;
                case SDLK_KP1:
                    tab[positioncurseur]= '1';
                    positioncurseur++;
                    break;
                case SDLK_KP2:
                    tab[positioncurseur]= '2';
                    positioncurseur++;
                    break;
                case SDLK_KP3:
                    tab[positioncurseur]= '3';
                    positioncurseur++;
                    break;
                case SDLK_KP4:
                    tab[positioncurseur]= '4';
                    positioncurseur++;
                    break;
                case SDLK_KP5:
                    tab[positioncurseur]= '5';
                    positioncurseur++;
                    break;
                case SDLK_KP6:
                    tab[positioncurseur]= '6';
                    positioncurseur++;
                    break;
                case SDLK_KP7:
                    tab[positioncurseur]= '7';
                    positioncurseur++;
                    break;
                case SDLK_KP8:
                    tab[positioncurseur]= '8';
                    positioncurseur++;
                    break;
                case SDLK_KP9:
                    tab[positioncurseur]= '9';
                    positioncurseur++;
                    break;


            }
        }



        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_RETURN))
        {
            continuer = 0;
        }

        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_BACKSPACE))
        {
            if(positioncurseur!=0)
            {
                positioncurseur--;
                tab[positioncurseur] = ' ';
                dessinne_ecran_ajout(ecran);

                positionTexte.x = (X/2)-25;
                positionTexte.y = 20;

                texte = TTF_RenderText_Blended(police,"date",couleurnoire);

                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                SDL_Flip(ecran);

                positionTexte.x = 75;
                positionTexte.y = (Y/2)-15;

            }
        }
















//        if(positioncurseur==10)continuer = 0;

        texte = TTF_RenderText_Blended(police,tab,couleurnoire);

        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        SDL_Flip(ecran);

    }


    FILE* fichier_h = NULL;
    fichier_h = fopen("historique.txt","a+");
//    fseek(fichier_h,0,SEEK_END);
    fprintf(fichier_h,tab);
    fprintf(fichier_h,"\n");
    fclose(fichier_h);





    ecran_commentaire(ecran);

}

void ecran_commentaire(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton_grand.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(300/2)+10;
    position_petit_ecran.y = (Y/2)-(100/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);







    char tab[18] = "";
    int continuer = 1;
    SDL_Event event;
    int positioncurseur = 0;

    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;


    positionTexte.x = (X/2)-75;
    positionTexte.y = 20;

    texte = TTF_RenderText_Blended(police,"commentaire",couleurnoire);

    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    SDL_Flip(ecran);




    positionTexte.x = 20;
    positionTexte.y = (Y/2)-15;








    while(continuer)
    {





        SDL_WaitEvent(&event);
        if((event.type == SDL_KEYDOWN)&&(positioncurseur < 17))
        {
            switch(event.key.keysym.sym)
            {

                case SDLK_RETURN:
                    continuer = 0;
                    break;

                case SDLK_BACKSPACE:
                    if(positioncurseur!=0)
                    {
                        positioncurseur--;
                        tab[positioncurseur] = ' ';
                        dessinne_ecran_commentaire(ecran);

                        positionTexte.x = (X/2)-75;
                        positionTexte.y = 20;

                        texte = TTF_RenderText_Blended(police,"commentaire",couleurnoire);

                        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                        SDL_Flip(ecran);

                        positionTexte.x = 20;
                        positionTexte.y = (Y/2)-15;
                    }
                    break;

                case SDLK_SPACE:
                    tab[positioncurseur] = ' ';
                    positioncurseur++;
                    break;

                case SDLK_KP_DIVIDE:
                    tab[positioncurseur] = '/';
                    positioncurseur++;
                    break;



                case SDLK_q:
                    tab[positioncurseur] = 'a';
                    positioncurseur++;
                    break;

                case SDLK_w:
                    tab[positioncurseur]= 'z';
                    positioncurseur++;
                    break;

                case SDLK_e:
                    tab[positioncurseur]= 'e';
                    positioncurseur++;
                    break;

                case SDLK_r:
                    tab[positioncurseur]= 'r';
                    positioncurseur++;
                    break;

                case SDLK_t:
                    tab[positioncurseur]= 't';
                    positioncurseur++;
                    break;

                case SDLK_y:
                    tab[positioncurseur]= 'y';
                    positioncurseur++;
                    break;

                case SDLK_u:
                    tab[positioncurseur]= 'u';
                    positioncurseur++;
                    break;

                case SDLK_i:
                    tab[positioncurseur]= 'i';
                    positioncurseur++;
                    break;

                case SDLK_o:
                    tab[positioncurseur]= 'o';
                    positioncurseur++;
                    break;

                case SDLK_p:
                    tab[positioncurseur]= 'p';
                    positioncurseur++;
                    break;

                case SDLK_a:
                    tab[positioncurseur]= 'q';
                    positioncurseur++;
                    break;

                case SDLK_s:
                    tab[positioncurseur]= 's';
                    positioncurseur++;
                    break;

                case SDLK_d:
                    tab[positioncurseur]= 'd';
                    positioncurseur++;
                    break;

                case SDLK_f:
                    tab[positioncurseur]= 'f';
                    positioncurseur++;
                    break;

                case SDLK_g:
                    tab[positioncurseur]= 'g';
                    positioncurseur++;
                    break;

                case SDLK_h:
                    tab[positioncurseur]= 'h';
                    positioncurseur++;
                    break;

                case SDLK_j:
                    tab[positioncurseur]= 'j';
                    positioncurseur++;
                    break;

                case SDLK_k:
                    tab[positioncurseur]= 'k';
                    positioncurseur++;
                    break;

                case SDLK_l:
                    tab[positioncurseur]= 'l';
                    positioncurseur++;
                    break;

                case SDLK_SEMICOLON:
                    tab[positioncurseur]= 'm';
                    positioncurseur++;
                    break;

                case SDLK_z:
                    tab[positioncurseur]= 'w';
                    positioncurseur++;
                    break;

                case SDLK_x:
                    tab[positioncurseur]= 'x';
                    positioncurseur++;
                    break;

                case SDLK_c:
                    tab[positioncurseur]= 'c';
                    positioncurseur++;
                    break;

                case SDLK_v:
                    tab[positioncurseur]= 'v';
                    positioncurseur++;
                    break;

                case SDLK_b:
                    tab[positioncurseur]= 'b';
                    positioncurseur++;
                    break;

                case SDLK_n:
                    tab[positioncurseur]= 'n';
                    positioncurseur++;
                    break;


                case SDLK_KP0:
                    tab[positioncurseur]= '0';
                    positioncurseur++;
                    break;
                case SDLK_KP1:
                    tab[positioncurseur]= '1';
                    positioncurseur++;
                    break;
                case SDLK_KP2:
                    tab[positioncurseur]= '2';
                    positioncurseur++;
                    break;
                case SDLK_KP3:
                    tab[positioncurseur]= '3';
                    positioncurseur++;
                    break;
                case SDLK_KP4:
                    tab[positioncurseur]= '4';
                    positioncurseur++;
                    break;
                case SDLK_KP5:
                    tab[positioncurseur]= '5';
                    positioncurseur++;
                    break;
                case SDLK_KP6:
                    tab[positioncurseur]= '6';
                    positioncurseur++;
                    break;
                case SDLK_KP7:
                    tab[positioncurseur]= '7';
                    positioncurseur++;
                    break;
                case SDLK_KP8:
                    tab[positioncurseur]= '8';
                    positioncurseur++;
                    break;
                case SDLK_KP9:
                    tab[positioncurseur]= '9';
                    positioncurseur++;
                    break;


            }
        }



        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_RETURN))
        {
            continuer = 0;
        }

        if((event.type == SDL_KEYDOWN)&&(event.key.keysym.sym == SDLK_BACKSPACE))
        {
            if(positioncurseur!=0)
            {
                positioncurseur--;
                tab[positioncurseur] = ' ';
                dessinne_ecran_commentaire(ecran);

                positionTexte.x = (X/2)-75;
                positionTexte.y = 20;

                texte = TTF_RenderText_Blended(police,"commentaire",couleurnoire);

                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                SDL_Flip(ecran);

                positionTexte.x = 20;
                positionTexte.y = (Y/2)-15;
            }
        }













//        if(positioncurseur==17)continuer = 0;

        texte = TTF_RenderText_Blended(police,tab,couleurnoire);

        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        SDL_Flip(ecran);

    }


    FILE* fichier_h = NULL;
    fichier_h = fopen("historique.txt","a+");
//    fseek(fichier_h,0,SEEK_END);
    fprintf(fichier_h,tab);
    fprintf(fichier_h,"\n");
    fprintf(fichier_h,"\n");
    fclose(fichier_h);



    ecran_principal(ecran);
}


void dessinne_ecran_ajout(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(200/2);
    position_petit_ecran.y = (Y/2)-(98/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);
}

void dessinne_ecran_commentaire(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *petit_ecran = NULL;
    petit_ecran = SDL_LoadBMP("bouton_grand.bmp");
    SDL_SetColorKey(petit_ecran, SDL_SRCCOLORKEY, SDL_MapRGB(petit_ecran->format, 255, 0, 0));

    SDL_Rect position_petit_ecran;

    position_petit_ecran.x = (X/2)-(300/2)+10;
    position_petit_ecran.y = (Y/2)-(100/2);

    SDL_BlitSurface(petit_ecran,NULL,ecran,&position_petit_ecran);

    SDL_Flip(ecran);
}


void ecran_historique(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Flip(ecran);

    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;

    dessinne_ecran_historique(ecran);






    FILE* fichier_h = NULL;
    fichier_h = fopen("historique.txt","r");
    rewind(fichier_h);

    char tab1[20] = "";
    char tab2[20] = "";
    char tab3[20] = "";
    char tab4[20] = "";
    char tab5[20] = "";
    char tab6[20] = "";
    char tab7[20] = "";
    char tab8[20] = "";

    int i=1;
    char page[1000]= "";
    int bcl = 0;

    if(fichier_h != NULL)
    {
        fgets(tab1,19,fichier_h);
        fgets(tab2,19,fichier_h);
        fgets(tab3,19,fichier_h);
        fgets(tab4,19,fichier_h);


        positionTexte.x = 20;
        positionTexte.y = 150;
        texte = TTF_RenderText_Blended(police,tab1,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab2,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab3,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab4,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


        positionTexte.x = X-30;
        positionTexte.y = Y-30;
        sprintf(page,"%d",i);
        texte = TTF_RenderText_Blended(police,page,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
    }



     if(fichier_h != NULL)
    {
        fgets(tab5,19,fichier_h);
        fgets(tab6,19,fichier_h);
        fgets(tab7,19,fichier_h);
        fgets(tab8,19,fichier_h);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab5,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab6,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab7,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

        positionTexte.x = 20;
        positionTexte.y = positionTexte.y + (25+10);
        texte = TTF_RenderText_Blended(police,tab8,couleurnoire);
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    }




    SDL_Flip(ecran);




    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        if((event.type == SDL_MOUSEBUTTONUP)&&(event.button.button == SDL_BUTTON_LEFT))
        {
            if((event.button.x> X-(30+10))&&(event.button.x< X-10)&&(event.button.y>130)&&(event.button.y<160))
            {
                if((fichier_h != NULL)&&(fgets(tab1,19,fichier_h) != NULL))
                {
                    i++;

                    dessinne_ecran_historique(ecran);

//                    fgets(tab1,19,fichier_h);
                    fgets(tab2,19,fichier_h);
                    fgets(tab3,19,fichier_h);
                    fgets(tab4,19,fichier_h);


                    positionTexte.x = 20;
                    positionTexte.y = 150;
                    texte = TTF_RenderText_Blended(police,tab1,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab2,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab3,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab4,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


                    positionTexte.x = X-30;
                    positionTexte.y = Y-30;
                    sprintf(page,"%d",i);
                    texte = TTF_RenderText_Blended(police,page,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                }
                if(fichier_h != NULL)
                {
                    fgets(tab5,19,fichier_h);
                    fgets(tab6,19,fichier_h);
                    fgets(tab7,19,fichier_h);
                    fgets(tab8,19,fichier_h);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab5,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab6,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab7,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab8,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                }

                SDL_Flip(ecran);
            }
            if((event.button.x> X-(30+10))&&(event.button.x< X-10)&&(event.button.y>90)&&(event.button.y<120))
            {
                if(i>1)
                {
                    dessinne_ecran_historique(ecran);

                    rewind(fichier_h);
                    i--;

                    for(bcl = 0;bcl<i;bcl++)
                    {
                        fgets(tab1,19,fichier_h);
                        fgets(tab2,19,fichier_h);
                        fgets(tab3,19,fichier_h);
                        fgets(tab4,19,fichier_h);
                    }
                    positionTexte.x = 20;
                    positionTexte.y = 150;
                    texte = TTF_RenderText_Blended(police,tab1,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab2,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab3,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab4,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


                    positionTexte.x = X-30;
                    positionTexte.y = Y-30;
                    sprintf(page,"%d",i);
                    texte = TTF_RenderText_Blended(police,page,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    SDL_Flip(ecran);
                }
            }
            if((event.button.x> X-(30+10))&&(event.button.x< X-10)&&(event.button.y>10)&&(event.button.y<40))
            {
                continuer=0;
            }
            if((event.button.x> X-(30+10))&&(event.button.x< X-10)&&(event.button.y>50)&&(event.button.y<80))
            {
                dessinne_ecran_historique(ecran);

                    rewind(fichier_h);

                    i = 1;

                    fgets(tab1,19,fichier_h);
                    fgets(tab2,19,fichier_h);
                    fgets(tab3,19,fichier_h);
                    fgets(tab4,19,fichier_h);

                    positionTexte.x = 20;
                    positionTexte.y = 150;
                    texte = TTF_RenderText_Blended(police,tab1,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab2,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab3,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    positionTexte.x = 20;
                    positionTexte.y = positionTexte.y + (25+10);
                    texte = TTF_RenderText_Blended(police,tab4,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


                    positionTexte.x = X-30;
                    positionTexte.y = Y-30;
                    sprintf(page,"%d",i);
                    texte = TTF_RenderText_Blended(police,page,couleurnoire);
                    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                    SDL_Flip(ecran);
            }
            if((event.button.x> X-(30+10))&&(event.button.x< X-10)&&(event.button.y>170)&&(event.button.y<200))
            {
                while(fgets(tab1,19,fichier_h) != NULL)
                {
                    i++;

                    dessinne_ecran_historique(ecran);

//                    fgets(tab1,19,fichier_h);
                    fgets(tab2,19,fichier_h);
                    fgets(tab3,19,fichier_h);
                    fgets(tab4,19,fichier_h);

                }

                positionTexte.x = 20;
                positionTexte.y = 150;
                texte = TTF_RenderText_Blended(police,tab1,couleurnoire);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                positionTexte.x = 20;
                positionTexte.y = positionTexte.y + (25+10);
                texte = TTF_RenderText_Blended(police,tab2,couleurnoire);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                positionTexte.x = 20;
                positionTexte.y = positionTexte.y + (25+10);
                texte = TTF_RenderText_Blended(police,tab3,couleurnoire);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                positionTexte.x = 20;
                positionTexte.y = positionTexte.y + (25+10);
                texte = TTF_RenderText_Blended(police,tab4,couleurnoire);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);


                positionTexte.x = X-30;
                positionTexte.y = Y-30;
                sprintf(page,"%d",i);
                texte = TTF_RenderText_Blended(police,page,couleurnoire);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

                SDL_Flip(ecran);
            }
        }
    }


    ecran_principal(ecran);
}

void dessinne_ecran_historique(SDL_Surface *ecran)
{
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,240,240,215));

    SDL_Surface *boutton_up = NULL;
    SDL_Surface *boutton_down = NULL;
    SDL_Surface *boutton_back = NULL;
    SDL_Surface *boutton_d_up = NULL;
    SDL_Surface *boutton_d_down = NULL;

    boutton_up = SDL_LoadBMP("fleche_up.bmp");
    boutton_down = SDL_LoadBMP("fleche_down.bmp");
    boutton_back = SDL_LoadBMP("fleche_back.bmp");
    boutton_d_up = SDL_LoadBMP("fleche_d_up.bmp");
    boutton_d_down = SDL_LoadBMP("fleche_d_down.bmp");

    SDL_SetColorKey(boutton_up, SDL_SRCCOLORKEY, SDL_MapRGB(boutton_up->format, 255, 0, 0));
    SDL_SetColorKey(boutton_down, SDL_SRCCOLORKEY, SDL_MapRGB(boutton_down->format, 255, 0, 0));
    SDL_SetColorKey(boutton_back, SDL_SRCCOLORKEY, SDL_MapRGB(boutton_back->format, 255, 0, 0));
    SDL_SetColorKey(boutton_d_up, SDL_SRCCOLORKEY, SDL_MapRGB(boutton_d_up->format, 255, 0, 0));
    SDL_SetColorKey(boutton_d_down, SDL_SRCCOLORKEY, SDL_MapRGB(boutton_d_down->format, 255, 0, 0));

    SDL_Rect position_boutton_up;
    SDL_Rect position_boutton_down;
    SDL_Rect position_boutton_back;
    SDL_Rect position_boutton_d_up;
    SDL_Rect position_boutton_d_down;

    position_boutton_back.x = X - (30+10);
    position_boutton_back.y = 10;

    position_boutton_d_up.x = X - (30+10);
    position_boutton_d_up.y = position_boutton_back.y + (10+30);

    position_boutton_up.x = X - (30+10);
    position_boutton_up.y = position_boutton_d_up.y + (10+30);

    position_boutton_down.x = X - (30+10);
    position_boutton_down.y = position_boutton_up.y + (10+30);

    position_boutton_d_down.x = X - (30+10);
    position_boutton_d_down.y = position_boutton_down.y + (10+30);

    SDL_BlitSurface(boutton_up,NULL,ecran,&position_boutton_up);
    SDL_BlitSurface(boutton_down,NULL,ecran,&position_boutton_down);
    SDL_BlitSurface(boutton_back,NULL,ecran,&position_boutton_back);
    SDL_BlitSurface(boutton_d_up,NULL,ecran,&position_boutton_d_up);
    SDL_BlitSurface(boutton_d_down,NULL,ecran,&position_boutton_d_down);



    SDL_Surface *texte = NULL;

    TTF_Font *police = NULL;

    police = TTF_OpenFont("unispace_rg.ttf",25);

    SDL_Color couleurnoire = {0,0,0};

    SDL_Rect positionTexte;

    positionTexte.x = 50;
    positionTexte.y = 30;
    texte = TTF_RenderText_Blended(police,"historique",couleurnoire);
    SDL_BlitSurface(texte,NULL,ecran,&positionTexte);

    SDL_Flip(ecran);
}

























void pause()
{
    int continuer=1;
    SDL_Event event;

    while (continuer)
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            continuer = 0;
            break;
    }
}
}

*/

