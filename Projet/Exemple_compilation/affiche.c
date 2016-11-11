#include <uvsqgraphics.h>
#define TAILLE_POLICE 30

void initialiser_affichage() {
    init_graphics(600,400);
}

void ecrire_texte_dans_cercle(char *texte) {
    int rayon = 2 + largeur_texte(texte,TAILLE_POLICE)/2;
    POINT centre; centre.x = LARGEUR_FENETRE/2; centre.y = HAUTEUR_FENETRE/2;
    POINT bg; bg.x = centre.x - 30; bg.y = centre.y - 30;
    fill_screen(blanc);
    int i;
    for (i=0 ; i<=10 ; i++) {
        draw_fill_circle(centre,rayon,gold);
        if (i%2) aff_pol_centre(texte, TAILLE_POLICE, centre, red);
        aff_int(10-i,TAILLE_POLICE,bg,red);
        attendre(250);
    }
}

