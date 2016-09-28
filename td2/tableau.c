#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_tab(int *tab,int a)
{
	int taille;
	taille=sizeof(tab);
	int j;
	
	for(j=0;j<taille;j++)
	{
		tab[j]=a;
	}
	
}

int prod_elem_tab(int *tab)
{
	int taille;
	taille=sizeof(tab);
	int j;
	int res = 1;
	
	for(j=0;j<taille;j++)
	{
		res = res*tab[j];
	}
	return res;
}

int prod_elem_tab_modif(int *tab,int i,int pos)
{
	int taille;
	taille=sizeof(tab);
	int j;
	int res = 1;
	int k = 1;
	
	if(tab[i] == 0) return 1;
	
	for(j=i;j<taille;j++)
	{
		if(tab[j]==0)
		{
			break;
		}
		else
		{
			res = res*tab[j];
			k++;
		}
	}
	tab[pos]=res;
	tab[pos+1]= 0;
	return k;
}

int min_tab(int *tab)
{
	int taille;
	taille=sizeof(tab);
	int j;
	int min = tab[0];
	
	for(j=1;j<taille;j++)
	{
		if(tab[j]<min)min=tab[j];
	}
	return min;
}

void decal_tab(int *tab,int i)
{
	int taille;
	taille=sizeof(tab)-1;
	
	while(taille>i)
	{
		tab[taille]=tab[taille-1];
	}
	tab[i]=0;
}

void insert_tab(int *tab,int i)
{
	int taille;
	taille=sizeof(tab);
	int j;
	
	for(j=0;j<taille;j++)
	{
		if(tab[j]>i)
		{
			decal_tab(tab,j);
			tab[j]=i;
		}
	}
}

void invert_tab(int *tab)
{
	int taille;
	taille=sizeof(tab);
	int j;
	int temp;
	
	for(j=0;j<=taille/2;j++)
	{
		temp=tab[j];
		tab[j]=tab[taille-1-j];
		tab[taille-1-j]=temp;
	}
}

void elim_double_tab(int *tab)
{
	int taille;
	taille=sizeof(tab);
	int j;
	int i;
	
	for(j=0;j<taille;j++)
	{
		if(tab[j]>0)
		{
			for(i=j+1;i<taille;i++)
			{
				if(tab[i] == tab[j]) tab[i]=tab[i]*(-1);
			}
		}
	}
}

int moy_section_tab(int *tab)
{
	int pos = 0;
	int taille;
	taille=sizeof(tab);
	int j=0;
	int res = 0;
	
	
	while(j<taille)
	{
		j = j + prod_elem_tab_modif(tab,j,pos);
	}
	
	j=0;
	while(tab[j]!=0)
	{
		res = res+tab[j];
		j++;
	}
	res=res/(j-1);
}



int main(void)
{	
	int tab[50];
	
	init_tab(tab,0);
	
	return 0;
}
