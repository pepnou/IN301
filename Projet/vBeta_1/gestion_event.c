#include "constantes.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

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

int encadrement(int x,int x1,int x2)
{
	if(((x>x1)&&(x<x2))||((x>x2)&&(x<x1))) return 1;
	
	return 0;
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
