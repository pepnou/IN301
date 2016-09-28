#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(void)
{
	/*
  int i, j, k = 0;
 
  puts("\n ___ TABLEAU DECIMAL ___");
  puts("\n     0 1 2 3 4 5 6 7 8 9");
  for(i = 0; i < 26; i++) {
    printf("\n %2d  ", i);
    for(j = 0; j < 10; j++, k++)
      printf("%c ", k != 7 && k != 8 && k != 9 && k != 10 && k != 13 && k < 256 ? k : ' ');
  }
 
  puts("\n _______________________");
  return 0;
  */
	
	int i;
	
	for(i=0;i<=127;i++)
	{
		printf("Code ASCII n°%d -> %c\n",i,i);
	}

	return 0;
}
