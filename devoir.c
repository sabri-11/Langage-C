#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b);
int tresor_iter(int n, int m, int valeur[n][m]);
int tresor_rec(int i, int j, int n, int m, int valeur[n][m]);

int main()
{ 
    char *choix_fonction = (char*)malloc(10*sizeof(char));
    char *choix_matrice = (char*)malloc(6*sizeof(char));
    printf("\nSur quelle matrice souhaitez vous exécuter le pgm : 8x8, 11x8, 14x19 ou 21x19 (entrez simplement 8x8 par exemple ou appuyez sur q pour quitter) : ");
    scanf("%s", choix_matrice);
    while( (strcmp(choix_matrice, "8x8") !=0 ) && (strcmp(choix_matrice, "11x8") != 0) && (strcmp(choix_matrice, "14x19") != 0) && (strcmp(choix_matrice, "21x19") != 0) )
    {
    	if (strcmp(choix_matrice, "q") == 0) return 0;
        printf("Vous n'avez pas entré la matrice sous le bon format.\nEntrez simplement 8x8, 11x8, 14x19, 21x19 ou appuyez sur q pour quitter : ");
        scanf("%s", choix_matrice);
    }
    
    printf ("Quel algorithme souhaitez vous utiliser ? Entrez iteratif ou recursif ou appuyez sur q pour quitter : ");
    scanf("%s", choix_fonction);   
    while (strcmp(choix_fonction, "iteratif") != 0 && strcmp(choix_fonction, "recursif") != 0)
    {
    	if (strcmp(choix_fonction, "q") == 0) return 0;
        printf("Vous n'avez pas enter un bon nom de fonction, entrez simplement iteratif ou recursif sans accent ni majuscule.\nEntrez un nouveau nom de fonction ou appuyez sur q pour quitter : ");
        scanf("%s", choix_fonction); 
    }

    printf("\nCalculs en cours...\nPressez ctrl+c pour quitter.\n");


    if ( strcmp(choix_matrice, "8x8") == 0 )
    {
        int n=8, m=8, t;
        int valeur[8][8] =  
            {
                {0, 3, 5, 4, 2, 3, 2, 4},
                {2, 3, 6, 1, 1, 1, 1, 6},
                {4, 1, 1, 2, 4, 3, 3, 2},
                {4, 2, 5, 3, 3, 4, 3, 5},
                {2, 1, 4, 4, 2, 3, 2, 3},
                {2, 3, 4, 3, 1, 2, 1, 2},
                {5, 4, 1, 2, 3, 1, 1, 1},
                {5, 3, 2, 3, 2, 1, 2, 0}
            };   //coût max : 44 trouvé instantanément avec les 2 algorithmes
        if ( strcmp(choix_fonction, "iteratif") == 0 )
        {   
            t = tresor_iter(n, m, valeur);
        }
        else
        {
            int i=0, j=0;
            t = tresor_rec(i, j, n, m, valeur);
        }
        printf("coût maximal : %d\n", t);
    
    } 
    else if ( strcmp(choix_matrice, "11x8") == 0 )
    {
        int n=11, m=8, t;
        int valeur[11][8] =  
            {
                {0, 3, 4, 3, 6, 5, 4, 6},
                {6, 2, 3, 1, 3, 3, 4, 1},
                {2, 3, 1, 4, 2, 5, 3, 4},
                {1, 4, 2, 5, 4, 3, 4, 3},
                {3, 2, 2, 3, 2, 2, 3, 2},
                {3, 3, 4, 3, 2, 2, 1, 2},
                {2, 3, 1, 2, 3, 4, 1, 2},
                {5, 3, 2, 3, 2, 5, 2, 4},
                {5, 4, 3, 2, 3, 3, 4, 2},
                {1, 2, 3, 1, 2, 3, 4, 2},
                {3, 2, 4, 3, 4, 5, 3, 0}
            };   //coût max : 59, trouvé instantanément avec les 2 algorithmes
        if ( strcmp(choix_fonction, "iteratif") == 0)
        {
            t = tresor_iter(n, m, valeur);
        }
        else
        {
            int i=0, j=0;
            t = tresor_rec(i, j, n, m, valeur);
        }
        printf("coût maximal : %d\n", t);
    }
    
    else if ( strcmp(choix_matrice, "21x19") == 0 )
    {
        int n=21, m=19, t;
        int valeur[21][19] = 
        {
            {0, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1},
            {2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2},
            {3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3},
            {4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4},
            {5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5},
            {6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6},
            {1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1},
            {2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2},
            {3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3},
            {1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1},
            {2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2},
            {3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3},
            {4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4},
            {5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5},  
            {6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6},
            {1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1},
            {2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2},
            {3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3},
            {1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1},
            {2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2},
            {3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3}
        };   // coût max : 133, trouvé instantanément en itératif mais pas en récursif (bcp trop de temps).
        if (strcmp(choix_fonction, "iteratif") == 0)
        {
            t = tresor_iter(n, m, valeur);
        }
        else
        {
            int i=0, j=0;
            t = tresor_rec(i, j, n, m, valeur);
        }
        
        printf("coût maximal : %d\n", t);
    }

    else if ( strcmp(choix_matrice, "14x19") == 0 )
    {
        int n=14, m=19, t;
        int valeur[14][19] = 
        {
            {0, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1},
            {2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2},
            {3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3},
            {4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4},
            {5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5},
            {6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6},
            {1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1},
            {2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2},
            {3, 1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 3, 4, 5, 6, 1, 2, 3},
            {1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1},
            {2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2},
            {3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3},
            {4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4},
            {5, 1, 3, 2, 4, 6, 2, 1, 3, 5, 1, 3, 2, 4, 6, 2, 1, 3, 5}
        };   //coût max : 107, plus de temps en récursif qu'en itératif
        if (strcmp(choix_fonction, "iteratif") == 0)
        {
            t = tresor_iter(n, m, valeur);
        }
        else
        {
            int i=0, j=0;
            t = tresor_rec(i, j, n, m, valeur);
        }
        printf("coût maximal : %d\n", t);
    }
   
    return 0;
}


int max(int a, int b)
{
    if (a>=b)
    {
        return(a);
    }
    else
    {
        return(b);
    }
}



int tresor_iter(int n, int m, int valeur[n][m])
{
    int gain[n][m];
    char chemin_opt[n][m];

    gain[n-1][m-1] = valeur[n-1][m-1];

    for (int i = n-2; i >= 0; i--)
    {
        chemin_opt[i][m-1] = 'b';
        gain[i][m-1] = valeur[i][m-1] + gain[i+1][m-1];
    }

    for (int j = m-2; j >= 0; j--)
    {
        chemin_opt[n-1][j] = 'd';
        gain[n-1][j] = valeur[n-1][j] + gain[n-1][j+1];
    }
    for (int i = n-2; i >= 0; i--)
    {
        for (int j = m-2; j >= 0; j--)
        {
            if (gain[i+1][j] > gain[i][j+1])
            {
                chemin_opt[i][j] = 'b';
                gain[i][j] = valeur[i][j] + gain[i+1][j];
            }
            else
            {
                chemin_opt[i][j] = 'd';
                gain[i][j] = valeur[i][j] + gain[i][j+1];
            }
        }
    }
    

    int i = 0, j = 0;

    printf("point de départ : (%d, %d)\nchemin à suivre : \n", i, j);
    while (i != n-1 || j != m-1)
    {
        if (chemin_opt[i][j] == 'b')    
        {
            printf("b, le chasseur descend et est maintenant en (%d, %d)\n", i+1, j+1);
            i++;
        }
        else
        {
           printf("d, le chasseur va à droite et est maintenant en (%d, %d) \n", i+1, j+1);
            j++;
        }
    }

    return gain[0][0];
}


int tresor_rec(int i, int j, int n, int m, int valeur[n][m])
{
    int a, b;
    if (i==n-1 && j==m-1)
    {
        return(valeur[i][j]);
    }
    else if (j==m-1)
    { 
        return (valeur[i][j] + tresor_rec(i+1, j, n, m, valeur));
    }
    else if (i==n-1)
    {
        return (valeur[i][j] + tresor_rec(i, j+1, n, m, valeur));
    }
    else
    {
        a = tresor_rec(i+1, j, n, m, valeur);
		b = tresor_rec(i, j+1, n ,m, valeur);
        return (valeur[i][j] + max(a, b));  
    }
}
//gcc -Wall -Wfatal-errors devoir.c -o devoir && ./devoir
