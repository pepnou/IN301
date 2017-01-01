#include "constantes.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

int encadrement(int x,int x1,int x2)
{
	if(((x>x1)&&(x<x2))||((x>x2)&&(x<x1))) return 1;
	
	return 0;
}

int position_clic_encadre(int x1,int x2,int y1,int y2,SDL_Event event)
{
	if((encadrement(event.button.x,x1,x2))&&(encadrement(event.button.y,y1,y2))) return 1;
	
	return 0;
}

SDL_Event attendre_clic_gauche()
{
	SDL_Event event_clic;
	
	int continuer =1;
	
	while(continuer)
	{
		SDL_WaitEvent(&event_clic);
		if((event_clic.type == SDL_MOUSEBUTTONUP)&&(event_clic.button.button == SDL_BUTTON_LEFT)) continuer = 0;
	}
	
	return event_clic;
}


Play_Event attendre_evenement(LEVEL niveau,SDL_Surface *ecran)
{
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event event;
	int continuer=1;
	int position_bandeau = (ecran->w)/2 - 150;
	int x,y;
	
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						continuer = 0;
						evenement.deplacement.y=-1;
						evenement.deplacement.x=0;
						break;
					case SDLK_DOWN:
						continuer = 0;
						evenement.deplacement.y=1;
						evenement.deplacement.x=0;
						break;
					case SDLK_RIGHT:
						continuer = 0;
						evenement.deplacement.x=1;
						evenement.deplacement.y=0;
						break;
					case SDLK_LEFT:
						continuer = 0;
						evenement.deplacement.x=-1;
						evenement.deplacement.y=0;
						break;
					case SDLK_u:
						continuer = 0;
						evenement.event = E_UNDO;
						break;
					case SDLK_r:
						continuer = 0;
						evenement.event = E_REDO;
						break;
					case SDLK_i:
						continuer = 0;
						evenement.event = E_INIT;
						break;
					case SDLK_p:
						continuer = 0;
						evenement.event = E_PREVIOUS;
						break;
					case SDLK_s:
						continuer = 0;
						evenement.event = E_NEXT;
						break;
					case SDLK_q: case SDLK_ESCAPE:
						continuer = 0;
						evenement.event = E_QUIT;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(position_bandeau + 10,position_bandeau + 49,20,80,event))
				{
					continuer = 0;
					evenement.event = E_UNDO;
				}
				if(position_clic_encadre(position_bandeau + 58,position_bandeau + 97,20,80,event))
				{
					continuer = 0;
					evenement.event = E_REDO;
				}
				if(position_clic_encadre(position_bandeau + 106,position_bandeau + 145,20,80,event))
				{
					continuer = 0;
					evenement.event = E_PREVIOUS;
				}
				if(position_clic_encadre(position_bandeau + 154,position_bandeau + 193,20,80,event))
				{
					continuer = 0;
					evenement.event = E_NEXT;
				}
				if(position_clic_encadre(position_bandeau + 202,position_bandeau + 241,20,80,event))
				{
					continuer = 0;
					evenement.event = E_INIT;
				}
				if(position_clic_encadre(position_bandeau + 250,position_bandeau + 289,20,80,event))
				{
					continuer = 0;
					evenement.event = E_QUIT;
				}
				if(position_clic_encadre(20,niveau.width*32 + 20,100,niveau.height*32 + 100,event))
				{
					x = (event.button.x-20)/32;
					y = (event.button.y-100)/32;
					
					if(((x-niveau.joueur.x) + (y-niveau.joueur.y) == -1)||((x-niveau.joueur.x) + (y-niveau.joueur.y) == 1))
					{	
						evenement.deplacement.x= x - niveau.joueur.x;
						evenement.deplacement.y= y - niveau.joueur.y;
						continuer = 0;
					}
				}
				break;
		}
	}
	
	return evenement;
}

Play_Event attendre_evenement_invert(LEVEL niveau,SDL_Surface *ecran)
{
	Play_Event evenement;
	evenement.event = E_MOVE;
	
	SDL_EnableKeyRepeat(10, 10);
	
	SDL_Event event;
	int continuer=1;
	int position_bandeau = (ecran->w)/2 - 150;
	int x,y;
	
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						continuer = 0;
						evenement.deplacement.y=-1;
						evenement.deplacement.x=0;
						break;
					case SDLK_DOWN:
						continuer = 0;
						evenement.deplacement.y=1;
						evenement.deplacement.x=0;
						break;
					case SDLK_RIGHT:
						continuer = 0;
						evenement.deplacement.x=1;
						evenement.deplacement.y=0;
						break;
					case SDLK_LEFT:
						continuer = 0;
						evenement.deplacement.x=-1;
						evenement.deplacement.y=0;
						break;
					case SDLK_u:
						continuer = 0;
						evenement.event = E_UNDO;
						break;
					case SDLK_r:
						continuer = 0;
						evenement.event = E_REDO;
						break;
					case SDLK_i:
						continuer = 0;
						evenement.event = E_INIT;
						break;
					case SDLK_q: case SDLK_ESCAPE:
						continuer = 0;
						evenement.event = E_QUIT;
						break;
					case SDLK_RETURN:
						continuer = 0;
						evenement.event = E_CONFIRM;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(position_clic_encadre(position_bandeau + 10,position_bandeau + 49,20,80,event))
				{
					continuer = 0;
					evenement.event = E_UNDO;
				}
				if(position_clic_encadre(position_bandeau + 58,position_bandeau + 97,20,80,event))
				{
					continuer = 0;
					evenement.event = E_REDO;
				}
				if(position_clic_encadre(position_bandeau + 154,position_bandeau + 193,20,80,event))
				{
					continuer = 0;
					evenement.event = E_INIT;
				}
				if(position_clic_encadre(position_bandeau + 202,position_bandeau + 241,20,80,event))
				{
					continuer = 0;
					evenement.event = E_CONFIRM;
				}
				if(position_clic_encadre(position_bandeau + 250,position_bandeau + 289,20,80,event))
				{
					continuer = 0;
					evenement.event = E_QUIT;
				}
				if(position_clic_encadre(20,niveau.width*32 + 20,100,niveau.height*32 + 100,event))
				{
					x = (event.button.x-20)/32;
					y = (event.button.y-100)/32;
					
					if(((x-niveau.joueur.x) + (y-niveau.joueur.y) == -1)||((x-niveau.joueur.x) + (y-niveau.joueur.y) == 1))
					{	
						evenement.deplacement.x= x - niveau.joueur.x;
						evenement.deplacement.y= y - niveau.joueur.y;
						continuer = 0;
					}
				}
				break;
		}
	}
	
	return evenement;
}
