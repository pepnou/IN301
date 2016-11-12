#define VIDE 0
#define MUR 1
#define CAISSE 2
#define JOUEUR 3
#define ARRIVE 4
#define JOUEUR_ARRIVE 5
#define CAISSE_ARRIVE 6

#define largeur_fenetre 400
#define hauteur_fenetre 400

#define largeur_max 100
#define hauteur_max 100

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
	int T[largeur_max][hauteur_max];
	POS joueur;
};
typedef struct level LEVEL;

