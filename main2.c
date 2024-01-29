// Analyse d'un fichier BMP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGUEUR 20
#define TAILLE_BLOC_ENTETE 54

// Structure entete image
struct entete_image {
    int largeur;
    int hauteur;
    int offset_data;
};

void analyser_entete(char *nom_fichier);

// Programme principal
int main(int argc, char **argv)
{
    char nom_fichier[LONGUEUR];

    if (2 == argc) {
        strcpy( nom_fichier, argv[1]);
        
        analyser_entete(nom_fichier);
    } else {
        printf("Usage: %s nom_fichier.bmp\n", argv[0]);
    }

    return EXIT_SUCCESS;
}

// Analyser l'entete de l'image
void analyser_entete(char *nom_fichier)
{
    FILE *fp;
    char buffer_entete[TAILLE_BLOC_ENTETE];
    char *p_char;
    short *p_short;
    int *p_int;

    // Ouverture fichier
    fp = fopen(nom_fichier, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Erreur ouverture fichier\n");
        exit(2);
    }

    // lecture entete fichier
    int bloc_lus = fread(buffer_entete, TAILLE_BLOC_ENTETE, 1, fp);
    if (bloc_lus != 1) {
        fprintf(stderr, "Erreur lecture\n");
        exit(2);
    }

    // Verification de la signature de l'image
    p_char = &buffer_entete[0];
    char signature[3] = {0, 0, 0};
    signature[0] = *p_char++;
    signature[1] = *p_char;
    if (strcmp(signature, "BM") != 0) {
        fprintf(stderr, "Type de fichier incorrect\n");
        exit(3);
    }

    // recuperation de la taille de l'image annoncée dans l'entete
    p_int = (int*) &buffer_entete[2];
    int taille_fichier = *p_int;

    // Recuperation
    p_int = (int*) &buffer_entete[10];
    int offset_data = *p_int;

    // Recuperation de la hauteur et la largeur de l'image
    p_int = (int*) &buffer_entete[18];
    int image_size_x = *p_int++;
    int image_size_y = *p_int++;

    // Recuperation du codage des couleurs
    p_short = (short*) &buffer_entete[28];
    short codage_couleur = *p_short;
    if (codage_couleur != 24) {
        fprintf(stderr, "Type de fichier incorrect\n");
        exit(3);
    }

    // Ne traiter que les images non compressées
    p_int = (int*) &buffer_entete[30];
    int compression = *p_int++;
    if (compression != 0) {
        fprintf(stderr, "Type de fichier incorrect\n");
        exit(3);
    }
 
    // Taille des données de l'image
    int taille_image = *p_int++;
    if (taille_image + offset_data != taille_fichier) {
        fprintf(stderr, "Taille fichier incorrecte\n");
        exit(3);
    }

    // Verification que la taille de l'image corresponds à la hauteur et largeur
    if ((image_size_x * image_size_y) * 3 != taille_image) {
        fprintf(stderr, "Taille fichier incorrecte\n");
        exit(3);
    }

    // Recherche de la taille réelle du fichier sur le disque
    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "Positionnement fichier incorrect\n");
        exit(2);
    }
    long taille_reelle_disque = ftell( fp );
    if (taille_reelle_disque != taille_fichier) {
        fprintf(stderr, "Taille fichier incorrecte %ld\n", taille_reelle_disque);
        exit(3);
    }

    // Fermeture fichier
    fclose(fp);
}
