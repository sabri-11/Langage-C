#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void fichier_et_mdp(char *);
void entrez_mdp(char*);
int est_minuscule(char);
int est_majuscule(char);

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Erreur, trop peu d'arguments.\n");
        return 1;
    }
    if (argc>4)
    {
        printf("Erreur, trop d'arguments.\n");
        return 1;
    }
    char c[16], r;
    FILE* in;
    FILE* out;
    
    int position_mdp=0;

    in = fopen(argv[1], "r");
    int taille_mdp = strlen(argv[2]);
    out = fopen(argv[3], "w");
    if (in == NULL || out == NULL)
    {
        printf("Erreur, un des fichiers entrée eest nul.\n");
        return 1;
    }

    for (int i=0; i<taille_mdp; i++)
    {
        if (est_minuscule(argv[2][i]))
        {
            c[i] = argv[2][i] - 'a' +1;
        }
        else if (est_majuscule(argv[2][i]))
        {
            c[i] = argv[2][i] - 'A' +1;
        }
    }
    
    r = fgetc(in);
    while (r !=EOF)
    {

        if (est_minuscule(r))
        
        {
            r = ((r-'a'+c[position_mdp])%26 + 'a');
            position_mdp = (position_mdp+1)%taille_mdp;
            fputc(r, out);
        }
        else if (est_majuscule(r))
        {
            r = ((r-'A'+c[position_mdp])%26 + 'A');
            position_mdp = (position_mdp+1)%taille_mdp;
            fputc(r, out);
        }
        else
        {
            fputc(r, out);
            
            
        }
        r = fgetc(in);
    }

    return 0;
}

int est_minuscule(char c)
{
  if (c >= 'a' && c<='z')
    {
      return 1;
    }
  else
    {
      return 0;
    }
    
}

int est_majuscule(char c)
{
  if (c >= 'A' && c<='Z')
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

//gcc -Wall -Wfatal-errors vigenere_codage.c -o vigenere_codage && ./vigenere_codage text.txt mdp text_crypte.txt
