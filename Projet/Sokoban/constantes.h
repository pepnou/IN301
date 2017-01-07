// PEPIN Thibaut

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
#define E_CONFIRM 7
#define E_BOUTTON_1 8
#define E_BOUTTON_2 9
#define E_BOUTTON_3 10
#define E_BOUTTON_4 11
#define E_BOUTTON_5 12
#define E_BOUTTON_6 13

#define COULEUR_FOND 254,185,24

#define extension_fichier ".xsb"

extern char* fichier_a_lire;
extern char* fichier_pour_ecrire;
extern int NBR_NIVEAUX;

#define largeur_max 56
#define hauteur_max 30

struct pos
{
	int x;
	int y;
};
typedef struct pos POS;

struct level
{
	int direction_joueur;
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
	int nbr_tour;
	LEVEL base_lvl;
};
typedef struct tour TOUR;


