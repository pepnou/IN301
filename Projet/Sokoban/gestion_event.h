// PEPIN Thibaut

SDL_Event attendre_clic_gauche();

int encadrement(int x,int x1,int x2);
int position_clic_encadre(int x1,int x2,int y1,int y2,SDL_Event event);

int victoire(LEVEL niveau);

Play_Event attendre_evenement(LEVEL niveau,SDL_Surface *ecran);
Play_Event attendre_evenement_invert(LEVEL niveau,SDL_Surface *ecran);

Play_Event attendre_event_menu_taille_lvl();
Play_Event attendre_event_modif_niveau(int position_bandeau,int lvl_width,int lvl_height);
Play_Event attendre_event_main_menu();
Play_Event attendre_event_play_menu();
