#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>

char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char numbers[] = "0123456789";
char specials[] = "!@#$%^&*()_+[]{}|;:,.<>?";


typedef enum {
    FILE_UNKNOWN,
    FILE_JPG,
    FILE_PNG,
    FILE_EXE,
    FILE_PDF,
    FILE_DOC
} FileType;



int is_special_character(char c)
{
    // Vérifier si le caractère est présent dans le tableau specials
    return strchr(specials, c) != NULL;
}


int is_password_strong(const char *password)
{
    int length = 0;
    int has_uppercase = 0;
    int has_lowercase = 0;
    int has_digitcase = 0;
    int has_specialcase = 0;

    while (password[length] != '\0')
    {
        if (isupper(password[length]))
        {
            has_uppercase = 1;
        }
        else if (islower(password[length]))
        {
            has_lowercase = 1;
        }
        else if (isdigit(password[length]))
        {
            has_digitcase = 1;
        }else if (is_special_character(password[length]))
        {
            has_specialcase = 1;
        }
        length++;
    }

    // Vérification des conditions
    if (length >= 10 && has_uppercase && has_lowercase)
    {
        return 1; // Le mot de passe est fort
    }
    else
    {
        return 0; // Le mot de passe n'est pas fort
    }
}

char *generate_password(int length, int special_characters)
{

    // Caractères autorisés :

    int total_length = length; // Longueur totale du mot de passe

    // Si les caractères spéciaux sont autorisés, ajoutez leur longueur à la longueur totale
    if (special_characters)
    {
        total_length += 1; // Ajoutez un caractère spécial
    }

    char *password = (char *)malloc((total_length + 1) * sizeof(char)); // +1 pour le caractère nul
    if (password == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(1);
    }

    // Initialiser la seed
    srand(time(NULL));

    // Générer au moins une lettre majuscule, une lettre minuscule, un chiffre et un caractère spécial
    password[0] = alphabet[rand() % 26];                     // Lettre majuscule
    password[1] = alphabet[rand() % 26 + 26];                // Lettre minuscule
    password[2] = numbers[rand() % 10];                      // Chiffre
    password[3] = specials[rand() % (sizeof(specials) - 1)]; // Caractère spécial

    // Générer le reste du mot de passe
    for (int i = 4; i < total_length; i++)
    {
        // Alternez entre les lettres majuscules, les lettres minuscules, les chiffres et les caractères spéciaux
        int random_range = rand() % 4;
        switch (random_range)
        {
        case 0:
            password[i] = alphabet[rand() % 26]; // Lettre majuscule
            break;
        case 1:
            password[i] = alphabet[rand() % 26 + 26]; // Lettre minuscule
            break;
        case 2:
            password[i] = numbers[rand() % 10]; // Chiffre
            break;
        case 3:
            password[i] = specials[rand() % (sizeof(specials) - 1)]; // Caractère spécial
            break;
        }
    }

    // Terminer la chaîne de caractères avec un caractère nul
    password[total_length] = '\0';

    return password;
}

void cypher_rotate(char *string, int rotation, int translation_length) {
    int length = strlen(string);
    int i = 0;

    while (string[i] != '\0') {
        if (islower(string[i])) {
            // Si le caractère est une lettre minuscule, effectuer la rotation
            char base = 'a';
            int offset = 26;

            // Calculer le décalage en fonction de la direction (rotation) et de la longueur de la translation
            int shift = (rotation == 0) ? translation_length : -translation_length;

            // Appliquer la rotation en tenant compte du décalage
            string[i] = ((string[i] - base + shift) % offset + offset) % offset + base;
        }
        i++;
    }
}

FileType get_file_header(FILE *file) {
    uint8_t header[4];
    size_t read_size;

    // Lire les 4 premiers octets du fichier
    read_size = fread(header, 1, 4, file);

    if (read_size != 4) {
        // Le fichier est trop court pour être identifié
        return FILE_UNKNOWN;
    }

    // Vérifier le format en fonction des en-têtes
    if (header[0] == 0xFF && header[1] == 0xD8) {
        return FILE_JPG;
    } else if (header[0] == 0x89 && header[1] == 0x50 && header[2] == 0x4E && header[3] == 0x47) {
        return FILE_PNG;
    } else if (header[0] == 0x4D && header[1] == 0x5A) {
        return FILE_EXE;
    } else if (header[0] == 0x25 && header[1] == 0x50 && header[2] == 0x44 && header[3] == 0x46) {
        return FILE_PDF;
    } else if (header[0] == 0xD0 && header[1] == 0xCF && header[2] == 0x11 && header[3] == 0xE0) {
        return FILE_DOC;
    } else {
        return FILE_UNKNOWN;
    }
}


int is_file_png(FILE *file) {
    uint8_t header[8];
    const uint8_t png_signature[] = {137, 80, 78, 71, 13, 10, 26, 10}; // Signature PNG

    // Lire les 8 premiers octets du fichier
    size_t read_size = fread(header, 1, 8, file);

    if (read_size != 8) {
        // Le fichier est trop court pour être un fichier PNG
        return 0;
    }

    // Comparer les 8 premiers octets avec la signature PNG
    if (memcmp(header, png_signature, 8) == 0) {
        return 1; // Le fichier est au format PNG
    } else {
        return 0; // Le fichier n'est pas au format PNG
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Utilisation : %s <longueur> <caracteres_speciaux>\n", argv[0]);
        return 1;
    }

    int length = atoi(argv[1]);
    int special_characters = atoi(argv[2]);

    char *password = generate_password(length, special_characters);

    if (password != NULL)
    {
        printf("Mot de passe genere: %s\n", password);
        free(password); // Libérer la mémoire allouée pour le mot de passe
    }

    return 0;
}
