#define VIDE 0
#define MUR 1
#define CAISSE 2
#define JOUEUR 3
#define ARRIVE 4
#define JOUEUR_ARRIVE 5
#define CAISSE_ARRIVE 6

#define E_MOVE 0
#define E_UNDO 1
#define E_REDO 2
#define E_INIT 3
#define E_PREVIOUS 4
#define E_NEXT 5
#define E_QUIT 6

extern int largeur_fenetre;
extern int hauteur_fenetre;

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

struct Play_Event
{
	int event;
	POS deplacement;
};
typedef struct Play_Event Play_Event;

struct elem
{
	LEVEL val;
	struct elem* suiv;
};
typedef struct elem* liste;

struct tour
{
	liste fait;
	liste deplace;
	int continuer;
	int num_level;
	LEVEL base_lvl;
};
typedef struct tour TOUR;


