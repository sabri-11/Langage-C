#include <stdio.h>
#include <stdlib.h>

FILE *f;
FILE *g;
char r;
void decalage(FILE*, FILE*, int);

int main(int argc, char *argv[])
{
  f = fopen(argv[1], "r");
  g = fopen(argv[3], "w");
  
  if (f==NULL)
    {
      printf("erreur");
      return 1;
    }
  decalage(f, g, atoi(argv[2]));
 
  fclose(f);
  fclose(g);
  
  return 0;
} 

void decalage(FILE *f, FILE *g, int d)
{
  if (d < 0) 
  {
   d = ((-d/26)+1)*26 +d;
  }
  while ((r=fgetc(f)) != EOF)
    {
      
  if (r>='a' && r<='z')
  {
    fputc((r - 'a' + d)%26 + 'a', g);
  }
  else if (r>='A' && r<='Z')
  {
    fputc((r - 'A' + d)%26 + 'A', g);
  }
  else
    {
      fputc(r,g);
    }
    }
    
}


// fputc(g, (c - 'a' + dec) %26 + 'a')

//gcc -Wall -Wfatal-errors cesar_codage.c -o cesar_codage && ./cesar_codage mon_fichier.txt 1 sortie.txt
