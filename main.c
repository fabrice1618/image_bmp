#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGUEUR 20
#define TAILLE_BLOC_ENTETE 14
#define TAILLE_BLOC_IMAGE 40

void analyser_image(char *nom_fichier);

int main(int argc, char **argv)
{
    char nom_fichier[LONGUEUR];

    if (2 == argc) {
        strcpy( nom_fichier, argv[1]);
        
        analyser_image(nom_fichier);
    } else {
        printf("Usage: %s nom_fichier.bmp\n", argv[0]);
    }

    return EXIT_SUCCESS;
}

void analyser_image(char *nom_fichier)
{
    FILE *fp;
    char buffer_entete[TAILLE_BLOC_ENTETE];
    char buffer_entete_image[TAILLE_BLOC_IMAGE];

    printf("Fichier: %s\n", nom_fichier);
    
    fp = fopen(nom_fichier, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Erreur ouverture fichier\n");
        exit(2);
    }
    printf("Fichier ouvert\n");

    // lecture entete fichier
    int bloc_lus = fread(buffer_entete, TAILLE_BLOC_ENTETE, 1, fp);
    if (bloc_lus != 1) {
        fprintf(stderr, "Erreur lecture\n");
        exit(2);
    }

    for(int i = 0; i < TAILLE_BLOC_ENTETE; i++) {
        printf("%3d ", buffer_entete[i]);
    }

    int *p;
    p = (int*) &buffer_entete[2];
    int taille_fichier = *p;

    p = (int*) &buffer_entete[10];
    int offset_fichier = *p;

    printf("taille fichier: %d  offset: %d\n", taille_fichier, offset_fichier);

    // Entete image
    bloc_lus = fread(buffer_entete_image, TAILLE_BLOC_IMAGE, 1, fp);
    if (bloc_lus != 1) {
        fprintf(stderr, "Erreur lecture\n");
        exit(2);
    }

    for(int i = 0; i < TAILLE_BLOC_IMAGE; i++) {
        printf("%3d ", buffer_entete_image[i]);
    }


    fclose(fp);
}

/*
void analyser_image(char *nom_fichier)
{
    FILE *fp;
    char buffer_entete[TAILLE_BLOC_ENTETE];
    char buffer_entete_image[TAILLE_BLOC_IMAGE];

    printf("Fichier: %s\n", nom_fichier);
    
    fp = fopen(nom_fichier, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Erreur ouverture fichier\n");
        exit(2);
    }
    printf("Fichier ouvert\n");

    // lecture entete fichier
    int bloc_lus = fread(buffer_entete, TAILLE_BLOC_ENTETE, 1, fp);
    if (bloc_lus != 1) {
        fprintf(stderr, "Erreur lecture\n");
        exit(2);
    }

    printf("Entête fichier:\n");
    for(int i = 0; i < TAILLE_BLOC_ENTETE; i++) {
        printf("%3d ", buffer_entete[i]);
    }
    printf("\n");

    char *p_char = &buffer_entete[0];
    char signature[3] = {0, 0, 0};
    signature[0] = *p_char++;
    signature[1] = *p_char;

    int *p_int;
    p_int = (int*) &buffer_entete[2];
    int taille_fichier = *p_int;

    p_int = (int*) &buffer_entete[10];
    int offset_fichier = *p_int;

    printf("signature: %s taille fichier: %d  offset: %d\n\n", signature, taille_fichier, offset_fichier);

    // Entete image
    bloc_lus = fread(buffer_entete_image, TAILLE_BLOC_IMAGE, 1, fp);
    if (bloc_lus != 1) {
        fprintf(stderr, "Erreur lecture\n");
        exit(2);
    }

    printf("Entête image:\n");
    for(int i = 0; i < TAILLE_BLOC_IMAGE; i++) {
        if (i % 10 == 0 && i != 0) {
            printf("\n");
        }
        printf("%4d:%2X ", buffer_entete_image[i], buffer_entete_image[i]);
    }
    printf("\n");

    p_int = (int*) &buffer_entete_image[0];
    int signature_entete = *p_int++;
    int image_size_x = *p_int++;
    int image_size_y = *p_int++;

    short *p_short;
    p_short = (short*) &buffer_entete_image[14];
    short codage_couleur = *p_short;
    
    p_int = (int*) &buffer_entete_image[16];
    int compression = *p_int++;
    int taille_image = *p_int++;
    int resolution_x = *p_int++;
    int resolution_y = *p_int++;
    int couleurs_palette = *p_int++;
    int couleurs_importantes = *p_int;

    printf("signature entete: %X image_size_x: %d image_size_y: %d \n", signature_entete, image_size_x, image_size_y);
    printf("codage_couleur: %d compression: %d taille_image: %d \n", codage_couleur, compression, taille_image);
    printf("resolution_x: %d resolution_y: %d\n", resolution_x, resolution_y);
    printf("couleurs_palette: %d couleurs_importantes: %d\n\n", couleurs_palette, couleurs_importantes);


    printf("\n");
    fclose(fp);
}
*/