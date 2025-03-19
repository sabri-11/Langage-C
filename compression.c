#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

//--------------------------------------------------------------------------------------------- Structures -------------------------------------------------------------------------------------------------//



typedef struct _noeud
{
	struct _noeud *gauche;
    struct _noeud *droit;
	struct _noeud *suivant;
	char c;
	// char *code;
	uint32_t poids;   // nb de fois que le caractère apparaît dans la phrase/le texte.
}noeud;


typedef struct _arbre_binaire
{
    noeud *racine;
	uint16_t profondeur; 
}arbre;


typedef struct _pile
{
    uint32_t taille;
    noeud *tete;
}pile;



//---------------------------------------------------------------------------------------- Declaration de Fonctions ----------------------------------------------------------------------------------------//


pile *creerPile();
noeud *creerNoeud(char c, uint32_t poids);
arbre *creerArbre();
uint32_t *poids_lettres(FILE* in);
void init_pile(pile *p, uint32_t *tab_poids);
void insere_en_triant_pile(pile *p, noeud *no);
void push_noeud(pile *p, noeud *n);
noeud *recup_pop(pile *p);
bool est_vide_pile(pile *p);
void afficher_pile(pile *p);		// permet de vérifier les poids de chaque caractères
void afficher_pile_dans_fichier_aux(pile *p);
void construireArbre(arbre *arb, pile *p);
pile *recopierPile(pile* p);

uint32_t somme_poids(pile *p);		// permet de vérifier que la racine finale de notre arbre est bien égal à la somme du poids de chaque caractère

bool est_feuille(noeud *no);
void parcourir_arbre(arbre *arb, char **);
void parcours_rec(noeud *, char *, uint8_t, char *tab_code[256]);
void affiche_code_huffman(char *tab_code[256]);
void compresser(FILE *in, FILE *out, char *tab_code[256]);
uint8_t puissance(uint8_t bit, uint8_t puiss);
void creer_fichier_tete(FILE *out, char *tab_code[256]);

void liberer_arbre(noeud *racine);
void liberer_tab_code(char *tab_code[256]);


//-------------------------------------------------------------------------------------------------- Main --------------------------------------------------------------------------------------------------//


int main(int argc, char* argv[]) 
{
	if (argc < 3)
	{
		printf("Entrez le fichier à compresser en paramètre de l'exécution ainsi qu'un nom de fichier de sortie de votre choix.\n"
		"Fomrmat attendu : ./decompression 'fichier source' 'fichier decompressé'\n");
		return 1;
	} 
	
	FILE* in = fopen(argv[1], "rb");
	FILE *out = fopen(argv[2], "wb");
	
	assert(in!=NULL);
	assert(out!=NULL);

	pile *p = creerPile();
	arbre *arb = creerArbre();
	char *tab_code[256] = {NULL};
	

	uint32_t *tab_poids = poids_lettres(in);
	init_pile(p, tab_poids);
 //	afficher_pile(p);
	free(tab_poids);

	construireArbre(arb, p);
	free(p);

	parcourir_arbre(arb, tab_code);
 //	affiche_code_huffman(tab_code);


	compresser(in, out, tab_code);

	fclose(in);
	liberer_arbre(arb->racine);
	liberer_tab_code(tab_code);
	free(arb);		

	return 0;
}


//------------------------------------------------------------------------------------------------ Fonctions -----------------------------------------------------------------------------------------------//


pile *creerPile()
{
    pile *p = malloc(sizeof(pile));
    if (!p) assert(0);

    p->tete = NULL;
	p->taille = 0;
	
    return (p);
}

noeud *creerNoeud(char c, uint32_t poids)
{
    noeud *no = malloc(sizeof(noeud));
    if (!no) assert(0);

    no->gauche = NULL;
    no->droit = NULL;
	no->suivant = NULL;
    no->c = c;
    no->poids = poids;
    return(no);
}

arbre *creerArbre()
{
	arbre *arb = malloc(sizeof(arbre));
	if (!arb) assert(0);

	arb->profondeur = 0;
	arb->racine = NULL;
	return arb;
}

void init_pile(pile *p, uint32_t *tab_poids)
{
	for (uint16_t i = 0; i < 256; i++)
	{
		if (tab_poids[i] != 0) {
			noeud *no = creerNoeud(i, tab_poids[i]);
			insere_en_triant_pile(p, no);
		}
	}
}

void construireArbre(arbre *arb, pile *p)
{	

	noeud *no1;
	noeud *no2;
	noeud *parent;

	while (p->taille != 1)
	{
		no1 = recup_pop(p);
        no2 = recup_pop(p);
        parent = creerNoeud('\0', no1->poids + no2->poids);
        parent->gauche = no1;
        parent->droit = no2;
        insere_en_triant_pile(p, parent);
        arb->profondeur++;
	}
 //	printf("profdondeur : %u\n", arb->profondeur);
	arb->racine = p->tete;

}


void parcourir_arbre(arbre *arb, char **tab_code)
{
    char temp_code[256];

    parcours_rec(arb->racine, temp_code, 0, tab_code);
}


void parcours_rec(noeud *no, char *temp_code, uint8_t profondeur, char *tab_code[256])
{
    if (no == NULL) return;

    // Si c'est une feuille, copier le code du tableau temporaire dans tab_code, notre tableau de code de Hufffman
    if (no->gauche == NULL && no->droit == NULL) {
        temp_code[profondeur] = '\0';
        tab_code[(unsigned char)no->c] = strdup(temp_code);
        return;
    }

    // Descente par la gauche : on ajoute '0' dans notre tableau temporaire 
    temp_code[profondeur] = '0';
    parcours_rec(no->gauche, temp_code, profondeur + 1, tab_code);

    // Descente par la droite : on ajoute '1' dans notre tableau temporaire
    temp_code[profondeur] = '1';
    parcours_rec(no->droit, temp_code, profondeur + 1, tab_code);
}

void creer_fichier_tete(FILE *out, char *tab_code[256])
{
	uint8_t nb_lettre = 0;
 //	FILE *g = fopen("en_tete_du_fichier.txt", "wb");

	for (int i=0; i<256; i++)
	{
		if (tab_code[i] != NULL)
		{
			nb_lettre++;
		}	
	}
	
	fprintf(out, "%c\n", (char)nb_lettre);	// ptt mettre un fwrite, fwrite(&nb_lettre, 1, , out)	

	for (uint16_t i = 0; i < 256; i++)
    {
        // ascii code_huffman 
		if (tab_code[i] != NULL)
		{
			// On sépare chaque caractère de son code de Huffman par un ':' et chaque caracrère entre eux par un retour à 
			// la ligne. Si on utilisait pas ces séparateurs, on ne pourrait pas différencier les caractères '1' et '0' de 
			// leur code de Huffman. 
			fprintf(out, "%c:%s\n", (unsigned char) i, tab_code[i]);
			// lire le caractère c, lire le :, lire le code de Huffman associé à c jusqu'au retour à la ligne.
		}
    }
 //	fclose(g);
}

void compresser(FILE *in,FILE *out, char *tab_code[256])
{
	creer_fichier_tete(out, tab_code);
	int16_t c = fgetc(in);
	uint8_t compteur = 0;	// une fois qu'on a le compteur égal à 8, cela veut dire qu'on aura récupérer les 8 bits
 //							  de l'octet. On doit donc écrire le code ascii dans notre fichier compressé qui pourrait 
 //							  être un mélange de plusieurs caractères de notre fichier de base.
	uint8_t bit = 0;
	uint8_t valeur_bit=0;	// On placera dans valeur bit la valeur de 0 ou 1 en fonction de si le code de Huffman du
 //							   caracrère lu est un 0 ou un 1.

	uint8_t place = 0;		// Permettra de nous situer dans la chaîne de caractère du code de Huffman. Quand on on lu
 //							   1er bit du code de Huffman du caractère c, on incrémente place pour ensuite lire le bit
 //							   suivant du même caractère. Quand on a le compteur à 8 on écrit le caractère codé sur les 8
 //							   bits mais on ne réinitialise pas la place car on veut continuer à lire le code de Huffman de
 //							   même caractère s'il est codé sur plus de 8 bits.

	while (c != EOF)
	{
		// uint8_t taille = (uint8_t) strlen(tab[i]);
		
		while (tab_code[(unsigned char) c][place] == '0' || tab_code[(unsigned char) c][place] == '1')
		{
			valeur_bit = tab_code[(unsigned char)c][place] - '0';	// permet d'avoir 0 ou 1 au lieu de leur code Ascii 

			bit += valeur_bit * puissance(2, 7-compteur);  // permet de faire 2⁷ 2⁶... par ex
			compteur ++;
			place++;
			if (compteur == 8)
			{
				compteur = 0;
				char r = (char) bit;
				fputc(r, out);
				bit = 0;
			}
		}
		place = 0;
		c = fgetc(in);
	}

	fclose(out);
}

uint8_t puissance(uint8_t bit, uint8_t puiss)
{
	uint8_t res = 1;
	for (uint8_t i = 0; i < puiss; i++)
	{
		res *= bit;
	}
	return res;

}

uint32_t *poids_lettres(FILE* in)
{
	
	int16_t c;		// int16_t pour pouvoir comparer à EOF, car char peut être mal comparé à EOF.

	uint32_t* tab_poids = (uint32_t*) calloc(256, sizeof(uint32_t));
	if (tab_poids==NULL) assert(0);

	while ((c = fgetc(in)) != EOF)
	{
		tab_poids[(unsigned char)c]++;
	}
	rewind(in);
	// le tableau tab_poids contiendra donc le poids de chaque caractère dans le fichier avec comme 
	// indice l'ASCII du caractère en question.
	return(tab_poids);

}


// Va nous permettre d'insérer un noeud dans notre pile, ce qui est plus simple pour faire les transfert
// d'une pile vers une autre pile auxiliaire
void push_noeud(pile *p, noeud *n)
{
    n->suivant = p->tete;
    p->tete = n;
    p->taille++;
}

// Récupère le premier nœud sans le libérer pour le réutiliser par la suite.
noeud *recup_pop(pile *p)
{
    if (p->tete == NULL) return NULL;
    noeud *temp = p->tete;
    p->tete = temp->suivant;
    p->taille--;
    temp->suivant = NULL;
    return temp;
}

// Permet d'insérer un noeud dans notre pile en le plaçant au bon endroit afin que la pile reste triée
// avec le noeud de poids faible en tête
void insere_en_triant_pile(pile *p, noeud *no)
{
    if (p->tete == NULL || p->tete->poids >= no->poids)
	{
        push_noeud(p, no);
    }
	else
	{
        noeud *temp = p->tete;
        while (temp->suivant != NULL && temp->suivant->poids < no->poids)
		{
            temp = temp->suivant;
        }
        no->suivant = temp->suivant;
        temp->suivant = no;
        p->taille++;
    }
}


bool est_vide_pile(pile *p)
{
	if (p->tete == NULL) return true;
	return false;
}

bool est_feuille(noeud *no)
{
	if (no->gauche == NULL && no->droit == NULL)
	{
		return true;
	}
	return false;
}

void afficher_pile(pile *p)
{
    uint16_t i = 0;
    noeud *temp = p->tete; 

    while (temp != NULL)
    {
        printf("%ue elem de la pile : %c, %u\n", i, temp->c, temp->poids);
        temp = temp->suivant;
        i++;
    }
}

void afficher_pile_dans_fichier_aux(pile *p)
{
    uint16_t i = 0, j=0;
    noeud *temp = p->tete; 
	FILE* aux = fopen("poids_noeuds.txt", "w");

    while (temp != NULL)
    {
        fprintf(aux, "noeud[%u] : c : %c et poids : %u. (Ascii : %u)\n", j, temp->c, temp->poids, i);
        temp = temp->suivant;
        i++;
		j++;
    }
}

void affiche_code_huffman(char *tab_code[256])
{
	for (uint16_t i = 0; i < 256; i++)
    {
        if (tab_code[i] != NULL)
        {
            printf("Caractère '%c' (ASCII %d) : Code Huffman %s\n", (char)i, i, tab_code[i]);
        }
    }
}


uint32_t somme_poids(pile *p)	// // permet de vérifier que la racine finale de notre arbre est bien égal à la somme du poids de chaque caractère
{
	noeud * no = p->tete;
	uint32_t somme=0;
	while (no != NULL)
	{
		somme += no->poids;
		no = no->suivant;
	}

	return somme;
}

void liberer_arbre(noeud *racine)
{
	if (racine == NULL)
	{
		return;
	}
	liberer_arbre(racine->gauche);
	liberer_arbre(racine->droit);
	free(racine);
}

void liberer_tab_code(char *tab_code[256])
{
	for (uint16_t i = 0; i<256; i++)
	{
		if (tab_code[i] != NULL)
		{
			free(tab_code[i]);
		}
	}
}


// gcc -Wall -Wfatal-errors compression.c -o compression
// ./compression fichiers/vingtmille.txt comp

// gcc -Wall -Wfatal-errors compression.c -o compression && ./compression fichiers/vingtmille.txt comp


// gcc -Wall -Wfatal-errors -g compression.c -o compression
// valgrind --tool=memcheck ./compression fichiers/vingtmille.txt comp

// gcc -Wall -Wfatal-errors -g compression.c -o compression && valgrind --tool=memcheck ./compression fichiers/vingtmille.txt comp