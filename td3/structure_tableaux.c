#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tableau
	{
		int taille;
		int T[100];
	};
typedef struct tableau tableau;

struct acces
	{
		int ecriture;
		int lecture;
	};

typedef struct acces acces;

int alea(int n)
{
	return rand()%n;
}

void ini_struct_tab(tableau *a)
{
	int i;
	(*a).taille=10;
	for(i=0;i<(*a).taille;i++) (*a).T[i]=alea(100);
}

void affiche_tableau_struct_tab(tableau b)
{
	printf("\n");
	int i;
	for(i=0;i<b.taille;i++) printf("%d\n",b.T[i]);
}

int prod_tableau_struct_tab(tableau c)
{
	int res=1;
	int i;
	for(i=0;i<c.taille;i++)
	{
		res*=c.T[i];
	}
	
	printf("\nsomme element tableau : %d\n",res);
	return res;
}

int min_tableau_struct_tab(tableau d)
{
	int min=d.T[0];
	int i;
	for(i=1;i<d.taille;i++)
	{
		if(d.T[i]<min) min=d.T[i];
	}
	
	printf("\nminimum tableau : %d\n",min);
	return min;
}

void decale_droite_tableau_struct_tab(tableau *e)
{
	int j;
	for(j=(*e).taille;j>0;j--)
	{
		(*e).T[j]=(*e).T[j-1];
	}
	(*e).T[0]=0;
	(*e).taille++;
}

int decale_droite_tableau_struct_tab_modif(tableau *e,int rang)
{
	if(rang>(*e).taille)return -1;
	
	int i;
	for(i=(*e).taille;i>rang;i--)
	{
		(*e).T[i]=(*e).T[i-1];
	}
	(*e).T[rang]=0;
	(*e).taille++;
	
	return 1;
}

int decale_gauche_tableau_struct_tab_modif(tableau *e,int rang)
{
	if(rang>(*e).taille)return -1;
	
	int i;
	for(i=rang;i<(*e).taille-1;i++)
	{
		(*e).T[i]=(*e).T[i+1];
	}
	(*e).taille--;
	
	return 1;
}

void trie_tableau_struct_tab(tableau *f)
{
	int tmp;
	int i=0;
	while(i<(*f).taille)
	{
		if((*f).T[i]>(*f).T[i+1])
		{
			tmp=(*f).T[i];
			(*f).T[i]=(*f).T[i+1];
			(*f).T[i+1]=tmp;
			i=0;
		}
		else
		{
			i++;
		}
	}
}

int inser_tableau_struct_tab(tableau *g,int x)
{
	int i;
	for(i=0;i<(*g).taille;i++)
	{
		if((*g).T[i]>x)
		{
			decale_droite_tableau_struct_tab_modif(g,i);
			(*g).T[i]=x;
			//(*g).taille++;
			return 1;
		}
	}
	(*g).T[(*g).taille]=x;
	(*g).taille++;
	return 1;
}

void invert_tableau_struct_tab(tableau *h)
{
	int tmp;
	int i;
	int mil=(*h).taille/2;
	for(i=0;i<mil;i++)
	{
		tmp=(*h).T[i];
		(*h).T[i]=(*h).T[(*h).taille-i-1];
		(*h).T[(*h).taille-1-i]=tmp;
	}
}

void elim_alea_struct_tab(tableau *i)
{
	decale_gauche_tableau_struct_tab_modif(i,alea(((*i).taille)-1));
}

void elim_doublon_tableau_struct_tab(tableau *j)
{
	int i;
	for(i=0;i<((*j).taille)-1;i++)
	{
		if((*j).T[i]==(*j).T[i+1])
		{
			decale_gauche_tableau_struct_tab_modif(j,i);
			i--;
		}
	}
}

acces min_tableau_struct_tab_modif(tableau *d,int debut,int fin)
{
	acces b;
	b.lecture=0;
	b.ecriture=0;
	
	int min=debut;
	int i;
	int tmp;
	b.lecture++;
	for(i=debut+1;i<(*d).taille;i++)
	{
		b.lecture+=3;
		if((*d).T[i]<(*d).T[min]) min=i;
	}
	b.lecture+=2;
	b.ecriture+=2;
	
	tmp=(*d).T[debut];
	(*d).T[debut]=(*d).T[min];
	(*d).T[min]=tmp;
	
	return b;
}

acces add(acces a,acces b)
{
	acces c;
	c.lecture = a.lecture + b.lecture;
	c.ecriture = a.ecriture + b.ecriture;
	return c;
}

acces tri_selection_tableau_struct_tab(tableau *k,int debut,int fin)
{
	acces a;
	a.lecture=0;
	a.ecriture=0;
	
	if(debut == fin);
	else
	{
		a=add(min_tableau_struct_tab_modif(k,debut,fin),a);
		a=add(tri_selection_tableau_struct_tab(k,debut+1,fin),a);
		
		//affiche_tableau_struct_tab(*k);
	}
	return a;
}

acces inser_tableau_struct_tab_modif(tableau *g,int x)
{
	acces w;
	w.lecture=0;
	w.ecriture=0;
	
	int a = (*g).T[x];
	w.lecture++;
	int i,j;
	for(i=0;i<x;i++)
	{
		w.lecture +=2;
		if((*g).T[i]>(*g).T[x])
		{
			for(j=x;j>i;j--)
			{
				w.lecture++;
				w.ecriture++;
				(*g).T[j] = (*g).T[j-1];
			}
			w.ecriture++;
			(*g).T[i]=a;
			return w;
		}
	}
	return w;
}

acces tri_insertion_tableau_struct_tab(tableau *l,int n)
{
	acces z;
	z.lecture=0;
	z.ecriture=0;
	z.lecture++;
	if(!(n>((*l).taille-1)))
	{
		z = add(inser_tableau_struct_tab_modif(l,n),z);
		
		z = add(tri_insertion_tableau_struct_tab(l,n+1),z);
	}
	return z;
}

acces tri_bulle_tableau_struct_tab(tableau *m)
{
	acces z;
	z.lecture=0;
	z.ecriture=0;
	
	int tmp;
	int i,j;
	
	z.lecture++;
	for(i=0;i<(*m).taille;i++)
	{
		z.lecture +=2;
		for(j=0;j<(*m).taille-1;j++)
		{
			z.lecture++;
			z.lecture+=2;
			if((*m).T[j]>(*m).T[j+1])
			{
				z.lecture++;
				tmp=(*m).T[j];
				z.lecture++;
				z.ecriture++;
				(*m).T[j]=(*m).T[j+1];
				z.ecriture++;
				(*m).T[j+1]=tmp;
			}
		}
	}
	
	return z;
}

void afficher_acces(acces a)
{
	printf("acces lecture : %d\n",a.lecture);
	printf("acces ecriture : %d\n",a.ecriture);
}

void tri_lineaire_tableau_struct_tab(tableau *o)
{
	int i;
	int j=0;
	int tab[100];

	for(i=0;i<100;i++)
	{
		tab[i]=0;
	}

	for(i=0;i<(*o).taille;i++)
	{
		tab[(*o).T[i]]++;
	}

	i=0;
	while(i<100)
	{
		if(tab[i]!=0)
		{
			(*o).T[j]=i;
			tab[i]--;
			j++;
		}
		else
		{
			i++;
		}
	}
}

void swap(tableau *q,int a,int b)
{
	int tmp=(*q).T[a];
	(*q).T[a]=(*q).T[b];
	(*q).T[b]=tmp;
}

void suppr(tableau *q,int n)
{
	int k;
	for(k=n;k<(*q).taille-1;k++)
	{
		(*q).T[k]=(*q).T[k+1];
	}
	(*q).taille--;
}

void tri_rapide_tableau_struct_tab(tableau *p,int deb,int fin)
{
	int i;
	
	if((!(deb==fin))&&(deb<fin))
	{
		int x=deb;
		int y=fin;
		
		for(i=x+1;i<=y;i++)
		{
			if((*p).T[x]>(*p).T[i])
			{
				decale_droite_tableau_struct_tab(p);
				x++;
				(*p).T[0]=(*p).T[i+1];
				suppr(p,i+1);
			}
		}
		tri_rapide_tableau_struct_tab(p,deb,x);
		tri_rapide_tableau_struct_tab(p,x+1,fin);
	}
}

int main()
{
	srand(time(NULL));
	
	tableau tab;
	
	
	//printf("sizeof(tableau) : %lu\n\n",sizeof(tableau));
	
	//printf("%d\n",alea(100));
	
	ini_struct_tab(&tab);
	affiche_tableau_struct_tab(tab);
	printf("\n");
	
	//prod_tableau_struct_tab(tab);
	//min_tableau_struct_tab(tab);
	
	//decale_droite_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//decale_droite_tableau_struct_tab_modif(&tab,5);
	//affiche_tableau_struct_tab(tab);
	
	//trie_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//inser_tableau_struct_tab(&tab,alea(20));
	//affiche_tableau_struct_tab(tab);
	
	//invert_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//elim_alea_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//elim_doublon_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	//afficher_acces(tri_selection_tableau_struct_tab(&tab,0,tab.taille-1));
	//affiche_tableau_struct_tab(tab);
	
	//afficher_acces(tri_insertion_tableau_struct_tab(&tab,1));
	//affiche_tableau_struct_tab(tab);
	
	//afficher_acces(tri_bulle_tableau_struct_tab(&tab));
	//affiche_tableau_struct_tab(tab);
	
	//tri_lineaire_tableau_struct_tab(&tab);
	//affiche_tableau_struct_tab(tab);
	
	tri_rapide_tableau_struct_tab(&tab,0,tab.taille-1);
	affiche_tableau_struct_tab(tab);
	
	printf("\n");
	return 0;
}
