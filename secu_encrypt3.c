#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int positionDansAlphabet(char lettre) {
    if (lettre >= 'a' && lettre <= 'z') {
        return lettre - 'a' + 1;
    } else {
        printf("\nErreur la lettre doit être minuscule\n");
        return 0;
    }
}


void position_permutation_octet(char *key, int *octet) {
  int k = strlen(key);
  int octet1; 
  int octet2;

  if (k % 2 == 0) {

    octet1 = 0;
    octet2 = 0;

    for (int i = 0; i < k; i++) {
      if (i < (k / 2)) {
        octet1 += positionDansAlphabet(key[i]);
      } else {
        octet2 += positionDansAlphabet(key[i]);
      }
    }

  } else {
    octet1 = 0;
    octet2 = 0;

    for (int i = 0; i < k - 1; i++) {
      if (i < (k - 1) / 2) {
        octet1 += positionDansAlphabet(key[i]);
      } else {
        octet2 += positionDansAlphabet(key[i]);
      }
    }

  }
  
  printf("\nLes octets à permuter sont %d et %d\n", octet1, octet2);

  
  octet[0]=octet1;
  octet[1]=octet2;
  
}

int secu_encrypt(char *key, char *input_file, char *output_file, int mode) {
  // Vérification de la clé
  if (!key || strlen(key) < 4 || strlen(key) > 10) {
    fprintf(stderr, "Erreur : la clé doit être comprise entre 4 et 10 caractères.\n");
    return 1;
  }

  // Vérification du mode
  if (mode != 0 && mode != 1) {
    fprintf(stderr, "Erreur : le mode doit être 0 pour le cryptage ou 1 pour le décryptage.\n");
    return 1;
  }

  // Ouverture des fichiers
  FILE *input = fopen(input_file, "rb");
  if (!input) {
    fprintf(stderr, "Erreur : échec de l'ouverture du fichier d'entrée.\n");
    return 1;
  }

  FILE *output = fopen(output_file, mode ? "wb" : "wb");
  if (!output) {
    fprintf(stderr, "Erreur : échec de l'ouverture du fichier de sortie.\n");
    fclose(input);
    return 1;
  }

  // Calcul de la longueur de la clé
  int key_len = strlen(key);

    
  int tableau_perm[2];
    position_permutation_octet(key,tableau_perm);
  // Permutation des octets
  for (int i = 1; i <= key_len; i++) {
    
    
    // Permutation des octets aux positions données
     int pos1 = tableau_perm[0] * i;
        int pos2 = tableau_perm[1] * i;

        // Déplacer le curseur de lecture/écriture à pos1
        fseek(input, pos1, SEEK_SET);

        // Lire l'octet à pos1
        char octet1;
        fread(&octet1, sizeof(char), 1, input);

        // Déplacer le curseur de lecture/écriture à pos2
        fseek(input, pos2, SEEK_SET);

        // Lire l'octet à pos2
        char octet2;
        fread(&octet2, sizeof(char), 1, input);

        // Revenir à la position pos1
        fseek(input, pos1, SEEK_SET);

        // Écrire octet2 à la position pos1
        fwrite(&octet2, sizeof(char), 1, output);

        // Revenir à la position pos2
        fseek(input, pos2, SEEK_SET);

        // Écrire octet1 à la position pos2
        fwrite(&octet1, sizeof(char), 1, output);
    
    printf("\n Permutation numero %d : octet %d avec octet %d\n", i ,tableau_perm[0]*i,tableau_perm[1]*i );

  }

  // Fermeture des fichiers
  fclose(input);
  fclose(output);

  

  return 0;
}


int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s [mode] [clé] [fichier_source] [fichier_destination]\n", argv[0]);
    return 1;
  }

  int mode = atoi(argv[1]);
  if (mode != 0 && mode != 1) {
    fprintf(stderr, "Erreur : le mode doit être 0 pour le cryptage ou 1 pour le décryptage.\n");
    return 1;
  }

  char *key = argv[2];
  char *input_file = argv[3];
  char *output_file = argv[4];

  // Cryptage ou décryptage du fichier
  int ret = secu_encrypt(key, input_file, output_file, mode);
  if (ret) {
    fprintf(stderr, "Erreur : échec du cryptage ou du décryptage.\n");
    return 1;
  }
    

  
  return 0;
}