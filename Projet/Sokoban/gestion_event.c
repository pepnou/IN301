#include "constantes.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_ttf.h>

int victoire(LEVEL niveau)
{
	int i, j;

	for (i = 1; i < niveau.width - 1; i++) {
		for (j = 1; j < niveau.height - 1; j++) {
			if ((niveau.T[i][j] == ARRIVE)
			    || (niveau.T[i][j] == JOUEUR_ARRIVE))
				return 0;
		}
	}
	return 1;
}

int encadrement(int x, int x1, int x2)
{
	if (((x >= x1) && (x <= x2)) || ((x >= x2) && (x <= x1)))
		return 1;

	return 0;
}

int position_clic_encadre(int x1, int x2, int y1, int y2, SDL_Event event)
{
	if ((encadrement(event.button.x, x1, x2))
	    && (encadrement(event.button.y, y1, y2)))
		return 1;

	return 0;
}

SDL_Event attendre_clic_gauche()
{
	SDL_Event event_clic;

	int continuer = 1;

	while (continuer) {
		SDL_WaitEvent(&event_clic);
		if ((event_clic.type == SDL_MOUSEBUTTONUP)
		    && (event_clic.button.button == SDL_BUTTON_LEFT))
			continuer = 0;
	}

	return event_clic;
}

Play_Event attendre_evenement(LEVEL niveau, SDL_Surface * ecran)
{
	Play_Event evenement;
	evenement.event = E_MOVE;

	SDL_EnableKeyRepeat(10, 10);

	SDL_Event event;
	int continuer = 1;
	int position_bandeau = (ecran->w) / 2 - 150;
	int x, y;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				continuer = 0;
				evenement.deplacement.y = -1;
				evenement.deplacement.x = 0;
				break;
			case SDLK_DOWN:
				continuer = 0;
				evenement.deplacement.y = 1;
				evenement.deplacement.x = 0;
				break;
			case SDLK_RIGHT:
				continuer = 0;
				evenement.deplacement.x = 1;
				evenement.deplacement.y = 0;
				break;
			case SDLK_LEFT:
				continuer = 0;
				evenement.deplacement.x = -1;
				evenement.deplacement.y = 0;
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
			case SDLK_q:
			case SDLK_ESCAPE:
				continuer = 0;
				evenement.event = E_QUIT;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (position_clic_encadre(position_bandeau + 10, position_bandeau + 49, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_UNDO;
			}
			if (position_clic_encadre(position_bandeau + 58, position_bandeau + 97, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_REDO;
			}
			if (position_clic_encadre(position_bandeau + 106, position_bandeau + 145, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_PREVIOUS;
			}
			if (position_clic_encadre(position_bandeau + 154, position_bandeau + 193, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_NEXT;
			}
			if (position_clic_encadre(position_bandeau + 202, position_bandeau + 241, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_INIT;
			}
			if (position_clic_encadre(position_bandeau + 250, position_bandeau + 289, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_QUIT;
			}
			if (position_clic_encadre(20, niveau.width * 32 + 20, 100, niveau.height * 32 + 100, event)) {
				x = (event.button.x - 20) / 32;
				y = (event.button.y - 100) / 32;

				if (((y - niveau.joueur.y == 0)
				     || (x - niveau.joueur.x == 0))
				    && (encadrement(x - niveau.joueur.x, -1, 1))
				    && (encadrement(y - niveau.joueur.y, -1, 1))) {
					evenement.deplacement.x = x - niveau.joueur.x;
					evenement.deplacement.y = y - niveau.joueur.y;
					continuer = 0;
				}
			}
			break;
		}
	}

	return evenement;
}

Play_Event attendre_evenement_invert(LEVEL niveau, SDL_Surface * ecran)
{
	Play_Event evenement;
	evenement.event = E_MOVE;

	SDL_EnableKeyRepeat(10, 10);

	SDL_Event event;
	int continuer = 1;
	int position_bandeau = (ecran->w) / 2 - 150;
	int x, y;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				continuer = 0;
				evenement.deplacement.y = -1;
				evenement.deplacement.x = 0;
				break;
			case SDLK_DOWN:
				continuer = 0;
				evenement.deplacement.y = 1;
				evenement.deplacement.x = 0;
				break;
			case SDLK_RIGHT:
				continuer = 0;
				evenement.deplacement.x = 1;
				evenement.deplacement.y = 0;
				break;
			case SDLK_LEFT:
				continuer = 0;
				evenement.deplacement.x = -1;
				evenement.deplacement.y = 0;
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
			case SDLK_q:
			case SDLK_ESCAPE:
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
			if (position_clic_encadre(position_bandeau + 10, position_bandeau + 49, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_UNDO;
			}
			if (position_clic_encadre(position_bandeau + 58, position_bandeau + 97, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_REDO;
			}
			if (position_clic_encadre(position_bandeau + 154, position_bandeau + 193, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_INIT;
			}
			if (position_clic_encadre(position_bandeau + 202, position_bandeau + 241, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_CONFIRM;
			}
			if (position_clic_encadre(position_bandeau + 250, position_bandeau + 289, 20, 80, event)) {
				continuer = 0;
				evenement.event = E_QUIT;
			}
			if (position_clic_encadre(20, niveau.width * 32 + 20, 100, niveau.height * 32 + 100, event)) {
				x = (event.button.x - 20) / 32;
				y = (event.button.y - 100) / 32;

				if (((y - niveau.joueur.y == 0)
				     || (x - niveau.joueur.x == 0))
				    && (encadrement(x - niveau.joueur.x, -1, 1))
				    && (encadrement(y - niveau.joueur.y, -1, 1))) {
					evenement.deplacement.x = x - niveau.joueur.x;
					evenement.deplacement.y = y - niveau.joueur.y;
					continuer = 0;
				}
			}
			break;
		}
	}

	return evenement;
}

Play_Event attendre_event_menu_taille_lvl()
{
	Play_Event PE;
	SDL_Event event;
	int continuer = 1;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_RETURN:
				PE.event = E_CONFIRM;
				continuer = 0;
				break;
			case SDLK_ESCAPE:
				PE.event = E_QUIT;
				continuer = 0;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (position_clic_encadre(65, 104, 197, 236, event)) {
				PE.event = E_BOUTTON_1;
				continuer = 0;
			}
			if (position_clic_encadre(335, 374, 198, 237, event)) {
				PE.event = E_BOUTTON_2;
				continuer = 0;
			}
			if (position_clic_encadre(65, 104, 267, 306, event)) {
				PE.event = E_BOUTTON_3;
				continuer = 0;
			}
			if (position_clic_encadre(335, 374, 268, 307, event)) {
				PE.event = E_BOUTTON_4;
				continuer = 0;
			}
			if (position_clic_encadre(150, 189, 351, 390, event)) {
				PE.event = E_QUIT;
				continuer = 0;
			}
			if (position_clic_encadre(250, 289, 351, 390, event)) {
				PE.event = E_CONFIRM;
				continuer = 0;
			}
			break;
		}
	}
	return PE;
}

Play_Event attendre_event_modif_niveau(int position_bandeau, int lvl_width, int lvl_height)
{
	Play_Event PE;
	SDL_Event event;
	int continuer = 1;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				PE.event = E_QUIT;
				continuer = 0;
				break;
			case SDLK_RETURN:
				PE.event = E_CONFIRM;
				continuer = 0;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (position_clic_encadre(position_bandeau + 8, position_bandeau + 119, 20 + 9, 20 + 50, event)) {
				PE.event = E_BOUTTON_1;
				continuer = 0;
			}
			if (position_clic_encadre
			    (position_bandeau + 121, position_bandeau + 208, 20 + 9, 20 + 50, event)) {
				PE.event = E_BOUTTON_2;
				continuer = 0;
			}
			if (position_clic_encadre
			    (position_bandeau + 210, position_bandeau + 250, 20 + 10, 20 + 49, event)) {
				PE.event = E_CONFIRM;
				continuer = 0;
			}
			if (position_clic_encadre
			    (position_bandeau + 252, position_bandeau + 291, 20 + 10, 20 + 49, event)) {
				PE.event = E_QUIT;
				continuer = 0;
			}
			if (position_clic_encadre(20, 20 + 32 * lvl_width, 100, 100 + 32 * lvl_height, event)) {
				PE.event = E_BOUTTON_3;
				PE.deplacement.x = event.button.x;
				PE.deplacement.y = event.button.y;
				continuer = 0;
			}
			break;
		}
	}
	return PE;
}

Play_Event attendre_event_main_menu()
{
	Play_Event PE;
	SDL_Event event;
	int continuer = 1;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				PE.event = E_QUIT;
				continuer = 0;
				break;
			}
			break;
		case SDL_QUIT:
			PE.event = E_QUIT;
			continuer = 0;
			break;
		case SDL_MOUSEBUTTONUP:
			if (position_clic_encadre(110, 429, 160, 279, event)) {
				PE.event = E_BOUTTON_1;
				continuer = 0;
			}
			if (position_clic_encadre(110, 429, 300, 419, event)) {
				PE.event = E_BOUTTON_2;
				continuer = 0;
			}
			break;
		}
	}
	return PE;
}

Play_Event attendre_event_play_menu()
{
	Play_Event PE;
	SDL_Event event;
	int continuer = 1;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				PE.event = E_QUIT;
				continuer = 0;
				break;
			case SDLK_RETURN:
				PE.event = E_CONFIRM;
				continuer = 0;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (position_clic_encadre(35, 104, 197, 236, event)) {
				PE.event = E_BOUTTON_1;
				continuer = 0;
			}
			if (position_clic_encadre(335, 375, 198, 237, event)) {
				PE.event = E_BOUTTON_2;
				continuer = 0;
			}
			if (position_clic_encadre(250, 289, 281, 320, event)) {
				PE.event = E_CONFIRM;
				continuer = 0;
			}
			if (position_clic_encadre(150, 189, 281, 320, event)) {
				PE.event = E_QUIT;
				continuer = 0;
			}
			break;
		}
	}
	return PE;
}
