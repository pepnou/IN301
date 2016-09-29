#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille = 5;

void init_tab(int *tab,int a)
{
	int j;
	
	for(j=0;j<taille;j++)
	{
		tab[j]=a;
	}
	
}

int prod_elem_tab(int *tab)
{
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
	int taille2=taille-1;
	
	while(taille2>i)
	{
		tab[taille2]=tab[taille2-1];
		taille2--;
	}
	tab[i]=0;
}

int insert_tab(int *tab,int i)
{
	int j;
	
	for(j=0;j<taille;j++)
	{
		if(tab[j]>i)
		{
			decal_tab(tab,j);
			tab[j]=i;
			return 0;
		}
	}
	return 0;
}

void invert_tab(int *tab)
{
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

float moy_section_tab(int *tab)
{
	int pos = 0;
	int a;
	int j=0;
	float res = 0;
	
	while(j<taille)
	{
		a = prod_elem_tab_modif(tab,j,pos);
		j = j + prod_elem_tab_modif(tab,j,pos);
		if(a>1) pos++;
	}
	
	j=0;
	while(tab[j]!=0)
	{
		res = res+tab[j];
		j++;
	}
	res=res/(j);
	
	return res;
}

void affiche_tab(int *tab)
{
	int i;
	
	for(i=0;i<taille;i++)
	{
		printf("%d : %d\n",i,tab[i]);
	}
}

int main(void)
{	
	int tab[taille];
	
	//init_tab(tab,0);
	tab[0]=3;
	tab[1]=4;
	tab[2]=0;
	tab[3]=0;
	tab[4]=10;
	
	affiche_tab(tab);
	
	//printf("%d\n",prod_elem_tab(tab));
	//printf("%d\n",min_tab(tab));
	
	//decal_tab(tab,2);
	
	//insert_tab(tab,3);
	
	//elim_double_tab(tab);
	
	//invert_tab(tab);
	
	printf("%f\n",moy_section_tab(tab));
	
	affiche_tab(tab);
	
	
	
	return 0;
}
