// PEPIN Thibaut

void affichelvl(SDL_Surface **ecran,LEVEL niveau,int invert);
void affiche_play_menu(SDL_Surface **ecran,int lvl_num);
void affiche_main_menu(SDL_Surface **ecran);
void affiche_menu_taille_lvl(SDL_Surface **ecran, int width, int height);
void affiche_entier(int entier,int x,int y,SDL_Surface *ecran);
void affiche_texte(char* texte,int x,int y,SDL_Surface *ecran);
void affiche_image(char* nom_image,int x,int y,SDL_Surface *ecran);
void affiche_image_2(char* nom_image,int x,int y,int rouge,int vert,int bleu,SDL_Surface *ecran);
void affiche_fond(int rouge,int vert,int bleu,SDL_Surface *ecran);
void affiche_interface(int invert,int x,int y,SDL_Surface *ecran);
void affiche_interface_bas(int x,int y,int num_lvl,int nbr_coup,SDL_Surface *ecran);
void affiche_grille_niveau(SDL_Surface *ecran,LEVEL niveau);
char* selection_image_joueur(int direction_joueur);
