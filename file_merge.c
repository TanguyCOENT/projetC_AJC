#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 10

int main(int argc, char *argv[])
{
    // Vérifier le nombre d'arguments
    if (argc < 2)
    {
        printf("Erreur : le programme necessite au moins un argument.\n");
        exit(1);
    }

    // Initialisation des variables
    int i;
    FILE *f_out = NULL;
    FILE *f_in[argc - 1];
    char *file_names[MAX_FILES];
    int opt;

    // Détection des paramètres hors options
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        { // stockage du nom des fichiers pour l'exploitation dans le files.merge
            file_names[i - 1] = argv[i];
        }
    }

    // Gestion des options dans la commande
    while ((opt = getopt(argc, argv, "u")) != -1)
    {
        switch (opt)
        {
        case 'u':
            printf("option -u fonctionne\n");
            // Ouvrir le fichier de merge en mode lecture binaire
            FILE *f_in = fopen(argv[2], "rb");
            if (f_in == NULL)
            {
                printf("Erreur : le fichier de merge ne peut pas etre ouvert.\n");
                exit(1);
            }

            // Lire les informations de début de fichier
            int n_files;
            fread(&n_files, sizeof(int), 1, f_in);

            // Lire les noms des fichiers
            char *file_names[MAX_FILES];
            for (int i = 0; i < n_files - 1; i++)
            {
                fread(file_names[i], sizeof(char), strlen(file_names[i]), f_in);
            }

            // Lire les balises de séparation
            char buf[256];
            while (fread(buf, sizeof(char), strlen(buf), f_in) > 0)
            {
                // Détecter la balise
                char *delim = strchr(buf, '/');
                if (delim != NULL)
                {
                    // Extraire le nom du fichier
                    char *file_name = buf;
                    file_name[delim - buf] = '\0';

                    // Extraire le poids du fichier
                    int weight = atoi(delim + 1);

                    // Créer le nouveau fichier
                    char new_file_name[256];
                    snprintf(new_file_name, sizeof(new_file_name), "%s_unmerged.%s", file_name, file_names[i + 1]);
                    FILE *f_out = fopen(new_file_name, "wb");

                    // Écrire les données dans le nouveau fichier
                    fseek(f_in, weight, SEEK_CUR);
                    int c;
                    while ((c = fgetc(f_in)) != EOF)
                    {
                        fputc(c, f_out);
                    }

                    // Fermer le nouveau fichier
                    fclose(f_out);
                }
            }

            // Fermer le fichier de merge
            fclose(f_in);

            // Sortie
            printf("Démergement effectué !\n");
            break;

        default:
            fprintf(stderr, "Usage: %s [-u] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Fusion des fichiers
    for (int i = 1; i < argc; i++)
    {
        f_in[i - 1] = fopen(argv[i], "r");
        if (f_in[i - 1] == NULL)
        {
            printf("Erreur : le fichier %s n'existe pas.\n", argv[i]);

            exit(1);
        }
    }

    // Ouvrir le fichier de sortie en mode écriture binaire
    f_out = fopen("files.merge", "wb");
    if (f_out == NULL)
    {
        printf("Erreur : le fichier de sortie ne peut pas etre ouvert.\n");
        exit(1);
    }

    /*
    // Écrire les informations de début de fichier
    fwrite(&argc, sizeof(int), 1, f_out);
    for (int i = 0; i < argc - 1; i++)
    {
        fwrite(file_names, sizeof(char), strlen(*file_names), f_out);
    }
    */

    // Écrire les balises de séparation
    for (int i = 0; i < argc - 1; i++)
    {
        // Ouvrir le fichier en mode lecture
        FILE *f_in = fopen(file_names[i], "r");
        if (f_in == NULL)
        {
            printf("Erreur : le fichier %s n'existe pas.\n", file_names[i]);
            exit(1);
        }

        // Déplacer le curseur de lecture à la fin du fichier
        fseek(f_in, 0, SEEK_END);

        // Récupérer la taille du fichier
        int size = ftell(f_in);

        // Fermer le fichier
        fclose(f_in);

        // Écrire la balise
        char buf[256];
        snprintf(buf, sizeof(buf), "<%s/%d>", file_names[i], size);
        fwrite(buf, sizeof(char), strlen(buf), f_out);
    }
    
    // Lire les données des fichiers en entrée et les écrire dans le fichier de sortie
    int c;
    
    while ((c = fgetc(f_in[0])) != EOF)
    {
        fputc(c, f_out);
    }
    
    for (int i = 1; i < argc - 1; i++)
    {
        while ((c = fgetc(f_in[i])) != EOF)
        {
            fputc(c, f_out);
        }
    }

    // Fermer les fichiers
    for (int i = 0; i < argc - 1; i++)
    {
        fclose(f_in[i]);
    }
    fclose(f_out);

    // Sortie
    printf("Fusion des fichiers effectuee !\n");

    return 0;
}