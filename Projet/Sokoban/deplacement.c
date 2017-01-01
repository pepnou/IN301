#include "constantes.h"

LEVEL deplacement_vers_VIDE(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_vers_CAISSE_1(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_vers_CAISSE_2(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE_ARRIVE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_vers_CAISSE(LEVEL niveau,POS deplacement)
{	
	switch(niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y])
	{
		case VIDE:
			niveau = deplacement_vers_CAISSE_1(niveau,deplacement);
			break;
		case ARRIVE:
			niveau = deplacement_vers_CAISSE_2(niveau,deplacement);
			break;
	}
		
	return niveau;
}

LEVEL deplacement_vers_CAISSE_ARRIVE_1(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_vers_CAISSE_ARRIVE_2(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y] = CAISSE_ARRIVE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_vers_CAISSE_ARRIVE(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	switch(niveau.T[niveau.joueur.x + 2*deplacement.x][niveau.joueur.y + 2*deplacement.y])
	{
		case VIDE:
			niveau = deplacement_vers_CAISSE_ARRIVE_1(niveau,deplacement);
			break;
		case ARRIVE:
			niveau = deplacement_vers_CAISSE_ARRIVE_2(niveau,deplacement);
			break;
	}
	
	return niveau;
}

LEVEL deplacement_vers_ARRIVE(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacer_joueur(LEVEL niveau,POS deplacement)
{	
	switch(niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y])
	{
		case VIDE:
			niveau = deplacement_vers_VIDE(niveau,deplacement);
			
			break;
		case CAISSE:
			niveau = deplacement_vers_CAISSE(niveau,deplacement);
			break;
		case CAISSE_ARRIVE:
			niveau = deplacement_vers_CAISSE_ARRIVE(niveau,deplacement);
			break;
		case ARRIVE:
			niveau = deplacement_vers_ARRIVE(niveau,deplacement);
			break;
	}
	niveau.direction_joueur = 2*deplacement.x + deplacement.y;
	
	return niveau;
}



LEVEL deplacement_invert_vers_VIDE_1(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = VIDE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
	
	return niveau;
}

LEVEL deplacement_invert_vers_VIDE_2(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
	
	return niveau;
}

LEVEL deplacement_invert_vers_VIDE(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	
	switch(niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y])
	{
		case CAISSE:
			niveau = deplacement_invert_vers_VIDE_1(niveau,deplacement);
			break;
		case CAISSE_ARRIVE:
			niveau = deplacement_invert_vers_VIDE_2(niveau,deplacement);
			break;
	}
	
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacement_invert_vers_ARRIVE_1(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = VIDE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
	
	return niveau;
}

LEVEL deplacement_invert_vers_ARRIVE_2(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y] = ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = CAISSE + ANCIENNE_CASE;
	
	return niveau;
}

LEVEL deplacement_invert_vers_ARRIVE(LEVEL niveau,POS deplacement)
{
	int ANCIENNE_CASE = VIDE;
	if(niveau.T[niveau.joueur.x][niveau.joueur.y] == JOUEUR_ARRIVE) ANCIENNE_CASE = ARRIVE;
	
	niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y] = JOUEUR_ARRIVE;
	niveau.T[niveau.joueur.x][niveau.joueur.y] = ANCIENNE_CASE;
	
	switch(niveau.T[niveau.joueur.x - deplacement.x][niveau.joueur.y - deplacement.y])
	{
		case CAISSE:
			niveau = deplacement_invert_vers_ARRIVE_1(niveau,deplacement);
			break;
		case CAISSE_ARRIVE:
			niveau = deplacement_invert_vers_ARRIVE_2(niveau,deplacement);
			break;
	}
	
	niveau.joueur.x=niveau.joueur.x + deplacement.x;
	niveau.joueur.y=niveau.joueur.y + deplacement.y;
	
	return niveau;
}

LEVEL deplacer_joueur_invert(LEVEL niveau,POS deplacement)
{	
	switch(niveau.T[niveau.joueur.x + deplacement.x][niveau.joueur.y + deplacement.y])
	{
		case VIDE:
			niveau = deplacement_invert_vers_VIDE(niveau,deplacement);
			break;
		case ARRIVE:
			niveau = deplacement_invert_vers_ARRIVE(niveau,deplacement);
			break;
	}
	niveau.direction_joueur = (-2)*deplacement.x - deplacement.y;
	
	return niveau;
}

