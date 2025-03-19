#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "fonctions.h"

//--------------------------------------------------------------------------------------------- Structures -------------------------------------------------------------------------------------------------//


typedef struct _noeud2
{
    struct _noeud2 *gauche;
    struct _noeud2 *droit;
	struct _noeud2 *suivant;
    char c;
    char *code;
}noeud2;

typedef struct _arbre_binaire2
{
    noeud2 *racine;
	uint16_t profondeur;
}arbre2;


typedef struct _pile2
{
    uint32_t taille;
    noeud2 *tete;
}pile2;



//---------------------------------------------------------------------------------------- Declaration de Fonctions ----------------------------------------------------------------------------------------//


void lire_tete(FILE *in, char *tab_code[256]);
void construireArbre2(arbre2 *arb, pile2 *p);
void liberer_arbre2(noeud2 *racine);
void decompresser(FILE *in, FILE *out, arbre2 *arb, char *tab_code[256], pile2 *p);

noeud2 *creerNoeud2(char c, char *code);
void push_noeud2(pile2 *p, noeud2 *no);
noeud2 *recup_pop2(pile2 *p);
void init_pile2(pile2 *p, char *tab_code[256]);
void insere_en_triant_pile2(pile2 *p, noeud2 *no);
pile2 *creerPile2();
arbre2 *creerArbre2();
bool est_vide_pile2(pile2 *p);
bool est_feuille2(noeud2 *no);

//-------------------------------------------------------------------------------------------------- Main --------------------------------------------------------------------------------------------------//


int main(int argc, char* argv[]) 
{
    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");
	if (argc < 3)
	{
		printf("Entrez le fichier à décompresser en paramètre de l'exécution ainsi qu'un nom de fichier de sortie de votre choix.\n"
        "Fomrmat attendu : ./decompression 'fichier compressé' 'fichier decompressé'\n");
		return 1;
	} 
    if (!in) assert(0);
    if (!out) assert(0);

    char *tab_code[256] = {NULL};
 //    lire_tete(in, tab_code);
    
    pile2 *p = creerPile2();
 //   init_pile2(p, tab_code);

    arbre2 *arb = creerArbre2();
  //  construireArbre2(arb, p);

    decompresser(in, out, arb, tab_code, p);


    liberer_tab_code(tab_code);     // définit dans fonctions.c
    liberer_arbre2(arb->racine);
    free(p);
    free(arb);
    fclose(in);
    fclose(out);
    return 0;
}


//------------------------------------------------------------------------------------------------ Fonctions -----------------------------------------------------------------------------------------------//



void lire_tete(FILE *in, char *tab_code[256])
{   
    char c = fgetc(in);
    char stock;        // stock va permettre de stocker la caracère qu'on a lu et de remplir son code de Huffman.
    uint8_t nb_lettre = (uint8_t) c, j=0;     // j va permettre d'écrire à notre indice stock qui représente le code ascii du caracère
    //                                         le code de Huffman complet associé à ce caractère.

    fgetc(in);  // Sauter le retour à la ligne après le nombre de lettres
    
    for (uint16_t i=0; i<nb_lettre; i++)
    {
        c = fgetc(in);
        stock = c;
        c = fgetc(in);      // permet de sauter le ':' qui sépare le caractère de son code de Huffman.
        c = fgetc(in);      // premier caractère du code de Huffman
        
        tab_code[(unsigned char)stock] = malloc(256 * sizeof(char));
        if (tab_code[(unsigned char)stock] == NULL) assert(0);
        
        j = 0;
        while (c != '\n' && c != EOF)  
        {
            if (c != '\r')
            {
                tab_code[(unsigned char)stock][j] = c;
                j++;
            }
            c = fgetc(in);
        }
        tab_code[(unsigned char)stock][j] = '\0';
        j = 0;
    }
        // printf("c à la fin : %c", c);    A la fin on a c = '\n'
    // Lorsque l'on effectuera : c = fgetc(in), on sera donc au 1er caractère de notre fichier compressé.
}


void construireArbre2(arbre2 *arb, pile2 *p)
{
    noeud2 *no;
    arb->racine = creerNoeud2('\0', "");
    noeud2 *temp = arb->racine;

    while (! est_vide_pile2(p))
    {
        no = recup_pop2(p);
        
        for(uint8_t i = 0; i<strlen(no->code); i++)
        {
            if (no->code[i] == '1')
            {
                if (temp->droit != NULL) temp = temp->droit;
                else
                {
                    temp->droit = creerNoeud2('\0', "");
                    temp = temp->droit;
                }
            }
            else
            {
                if (temp->gauche != NULL) temp = temp->gauche;
                else
                {
                    temp->gauche = creerNoeud2('\0', "");
                    temp = temp->gauche;
                }
            }
        }
        
        temp->c = no->c;
        temp = arb->racine;

        free(no->code);
        free(no);
    }
    // Vérification pour savoir si notre arbre est bien modifié.
 
    // char e = arb->racine->gauche->droit->gauche->c;      // (code de 'e' : 010)
    // char space = arb->racine->droit->droit->gauche->c;   // (code de ' ' : 110)
    // printf("On devrait normalement avoir 'e' ici : %c et ' ' ici : %c.\n", e, space);

    // if (est_feuille2(arb->racine->gauche->droit->gauche))
    // {
    //     if (est_feuille2(arb->racine->droit->droit->gauche))
    //     {
    //         printf("Tout est bueno !\n");
    //     }
    //     else printf("Arhhh\n");
    // }


} 

void decompresser(FILE *in, FILE *out, arbre2 *arb, char *tab_code[256], pile2 *p)
{
    lire_tete(in, tab_code);
    init_pile2(p, tab_code);
    construireArbre2(arb, p);


    char *temp = (char*) malloc(9*sizeof(char));     // on stockera dans temp les codes ascii sur 8 bits du caractère lu
 //                                                       on accorde 9 caractères pour inclure le caractère de fin '\0'
    if (! temp) assert(0);

    int16_t c = fgetc(in);     // On est au 1er caractère de notre fichier décompressé.
    noeud2 *aux = arb->racine;
    while (c != EOF)
    {
        for (int8_t i = 7; i >= 0; i--)     // boucle infini lorsque on utilise uint8_t
        {
            int16_t div = puissance(2, i);  // renvoie 2^i, définit dans fonctions.c
            int16_t bit = (c / div) % 2;     // extrait le bit à la position i
            if (bit == 0) temp[7 - i] = '0';    // si le bit est 0, on mets '0' dans temp à sa position
            else temp[7 - i] = '1';             // sinon on mets '1'.

        }
        temp[8] = '\0';    


        // temp contient le code binaire du caractère lu, reste à le lire en se déplaçant sur notre arbre binaire.

        
        for (uint8_t i=0; i<8; i++)
        {
             if (temp[i] == '0')
            { 
                if (aux->gauche != NULL)
                    aux = aux->gauche;
                else
                {
                    aux = arb->racine;
                    continue;
                }
            }
            else if (temp[i] == '1')
            {
                if (aux->droit != NULL)
                    aux = aux->droit;
                else
                {
                    aux = arb->racine;
                    continue;
                }
            }

            // Si on atteint une feuille, on écrit le caractère et on réinitialise le parcours
            if (est_feuille2(aux))
            {
                fputc(aux->c, out);
                aux = arb->racine;
            }
        }
        c = fgetc(in);
    }

    free(temp);
}



void init_pile2(pile2 *p, char *tab_code[256])
{
    for (uint16_t i = 0; i<256; i++)
    {
        if (tab_code[i] != NULL)
        {
            noeud2 *no = creerNoeud2(i, tab_code[i]);
			insere_en_triant_pile2(p, no);
        }
    }
    //   printf("tete pile :\nc : %c et code : %c\n", p->tete->c, p->tete->code[0]); 

    //   on a le caractère 'e' avec son code de Huffman 010, le caractère avec le poids le plus fort est ' ' mais son
    //   code de Huffman '110' a aussi 3 bits. On peut donc les interchanger dans l'ordre de la pile sans conséquences
}

void insere_en_triant_pile2(pile2 *p, noeud2 *no)
{
    uint8_t taille = (uint8_t) strlen(no->code);
    if (p->tete == NULL)
    {
        no->suivant = NULL;
        p->tete = no;
        p->taille++;
        return;
    }
    uint8_t taille_tete = (uint8_t) strlen(p->tete->code);

    if (taille_tete >= taille)
    {
        push_noeud2(p, no);
    }
    else
    {
        noeud2 *temp = p->tete;
        // Ici, on parcourt la pile pour trouver la bonne position
        while (temp->suivant != NULL && strlen(temp->suivant->code) < taille)
        {
            temp = temp->suivant;
        }
        no->suivant = temp->suivant;
        temp->suivant = no;
        p->taille++;
    }
}



noeud2 *creerNoeud2(char c, char *code)
{
    noeud2 *no = malloc(sizeof(noeud2));
    if (!no) assert(0);
    no->code = malloc( (strlen(code)+1) * sizeof(char) );
    no->gauche = NULL;
    no->droit = NULL;
	no->suivant = NULL;
    no->c = c;
    strcpy(no->code, code);
    return(no);
}

void push_noeud2(pile2 *p, noeud2 *no)
{
    no->suivant = p->tete;
    p->tete = no;
    p->taille++;
}

noeud2 *recup_pop2(pile2 *p)
{
    if (p->tete == NULL) return NULL;
    noeud2 *temp = p->tete;
    p->tete = temp->suivant;
    p->taille--;
    temp->suivant = NULL;
    return temp;
}

pile2 *creerPile2()
{
    pile2 *p = malloc(sizeof(pile2));
    if (!p) assert(0);

    p->tete = NULL;
	p->taille = 0;

    return (p);
}

arbre2 *creerArbre2()
{
	arbre2 *arb = malloc(sizeof(arbre2));
	if (!arb) assert(0);

	arb->profondeur = 0;
	arb->racine = NULL;
	return arb;
}

bool est_vide_pile2(pile2 *p)
{
	if (p->tete == NULL) return true;
	return false;
}

bool est_feuille2(noeud2 *no)
{
	if (no->gauche == NULL && no->droit == NULL)
	{
		return true;
	}
	return false;
}


void liberer_arbre2(noeud2 *racine)
{
	if (racine == NULL)
	{
		return;
	}
	liberer_arbre2(racine->gauche);
	liberer_arbre2(racine->droit);
    free(racine->code);
	free(racine);
}


// gcc -Wall -Wfatal-errors decompression.c fonctions.c -o decompression
// ./decompression comp decomp

// gcc -Wall -Wfatal-errors decompression.c fonctions.c -o decompression && ./decompression comp decomp

// Avec valgrind :
// gcc -Wall -Wfatal-errors -g decompression.c fonctions.c -o decompression && valgrind --tool=memcheck ./decompression comp decomp