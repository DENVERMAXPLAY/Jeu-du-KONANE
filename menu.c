#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define RESET   "\033[0m"
#define ROUGE   "\033[31m"
#define BLANC   "\033[37m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define effacer_ligne "\033[2K"
#define remonter_ligne "\033[1A"

#define RED   "\033[31m"
#define RESET    "\033[0m"

#define CV   "\033[45m"
#define CB  "\033[44m"

#include "menu.h"


char T[7][7];
char joueur1[50];
char joueur2[50];
char piece_joueur, piece_machine;

//Permet de faire une pause afin de permettre d'afficher un message d'erreur
void pause_console()
{
    printf("\nAppuyez sur Entree pour continuer...");
    while(getchar() != '\n');
    getchar();
}

//Pour effacer le contenu du terminal et afficher le texte "KONANE"
void syst_konane_espace()
{
    system("cls");
    konane();
    printf("\n\n");
}

//Affiche le texte "KONANE"
void konane()
{
    printf("%105s", "    __ __      ____       _   __     ___         _   __     ______   \n");
    printf("%105s", "   / //_/     / __ \\     / | / /    /   |       / | / /    / ____/   \n");
    printf("%105s", "  / ,<       / / / /    /  |/ /    / /| |      /  |/ /    / __/      \n");
    printf("%105s", " / /| |     / /_/ /    / /|  /    / ___ |     / /|  /    / /___      \n");
    printf("%105s", "/_/ |_|     \\____/    /_/ |_/    /_/  |_|    /_/ |_/    /_____/      \n");
}

//Affiche le menu_principale et retourne le choix effectuer
int menu_principale()
{
    int n;
    do
    {
        syst_konane_espace();
        printf("%77s", ">>> 1- Jouez au jeu \n\n");
        printf("%82s", ">>> 2- Les regles du jeu \n\n");
        printf("%78s", ">>> 3- Sortir du jeu \n\n");
        printf("\n\n");

        printf("Votre choix : ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n');
            printf("\n\n");
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 3.%s\n", ROUGE, RESET);
            pause_console();
            continue;
        }
        if (n < 1 || n > 3)
        {
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 3.%s\n", ROUGE, RESET);
            pause_console();
        }
    } while (n < 1 || n > 3);

    return n;
}

//Affiche un menu qui permet de choisir son adversaire et retourne (l'option choisie + 10)
int choix_adversaire()
{
    int n;
    do
    {
        syst_konane_espace();

        printf("%85s","Selectionnez l'option de jeu :\n\n");
        printf("%82s",">>> 1- Joeur 1 vs Joueur 2\n\n");
        printf("%89s",">>> 2- Player vs Machine (simple)\n\n");
        printf("%90s",">>> 3- Player vs Machine (complex)\n\n");
        printf("%69s",">>> 4- Retour\n\n");
        printf("%72s",">>> 5- Quitter \n\n\n");

        printf("Votre choix : ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n');
            printf("\n\n");
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 5.%s\n", ROUGE, RESET);
            pause_console();
            continue;
        }
        if (n < 1 || n > 5)
        {
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 4.%s\n", ROUGE, RESET);
            pause_console();
        }
    } while (n < 1 || n > 5);

    return 10 + n;
}

//Afiiche les r�gles du jeu et retourne (l'option choisie + 20)
int regles_jeu()
{
    int n;
    do
    {
        syst_konane_espace();

        printf("%89s",">>>>> Bienvenue dans le jeu de KONANE <<<<<\n\n");
        printf("%78s","===>Regles du jeu<===\n\n");

        printf("%95s","1-> Le plateau est une grille remplie de pierres noires\n");
        printf("%96s", "et blanches, disposees en alternance comme un damier.\n\n");

        printf("%106s","2-> Le joueur *Noir* commence en retirant une pierre au centre ou au coin .\n");
        printf("%96s","Le joueur *Blanc* retire ensuite une pierre voisine.\n");
        printf("%95s","Ces retraits creent les premiers espaces vides.\n\n");

        printf("%98s","3-> A chaque tour, un joueur doit deplacer une de ses pierres\n");
        printf("%98s","en sautant orthogonalement (haut, bas, gauche ou droite)\n");
        printf("%93s","par-dessus une pierre adverse vers une case vide.\n");
        printf("%94s","La pierre sautee est capturee et retiree du plateau.\n");
        printf("%89s","Les diagonales ne sont pas autorisees.\n\n");

        printf("%95s","4-> Si, apres un saut, une autre capture est possible,\n");
        printf("%95s","le joueur doit continuer a sauter dans le meme tour.\n");
        printf("%96s","Toute la sequence de sauts compte comme un seul coup.\n\n");

        printf("%98s","5-> La partie se termine lorsqu'un joueur ne peut plus jouer.\n");
        printf("%97s","Ce joueur perd et l'adversaire est declare vainqueur.\n\n");

        printf("%75s",">>> Objectif :\n");
        printf("%100s","Bloquer l'adversaire en reduisant ses possibilites de mouvement.\n");
        printf("%100s","Le gagnant est celui qui reussit a immobiliser l'autre joueur.\n\n");
        printf("%78s","Bonne partie !!!!!!!!\n\n");
        printf("%82s", ">>> 1- Retour ||  >>> 2- Quitter\n\n");

        printf("Votre choix : ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n');
            printf("\n\n");
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 2.%s\n", ROUGE, RESET);
            pause_console();
            continue;
        }
        if (n < 1 || n >2)
        {
            printf("%sErreur : Veuillez entrer un chiffre entre 1 et 2.%s\n", ROUGE, RESET);
            pause_console();
        }
    }while (n <1 && n > 2);

    return 20 + n;
}

//Permet de choisir un joueur al�atoirement pour le d�but du jeu
int tirage_premier_joueur()
{
    int premier_joueur;
    premier_joueur = rand() % 2;
    syst_konane_espace();

    if (premier_joueur == 0) printf(RED "\n\n>>> C'est %s qui commence ! <<<\n" RESET, joueur1);
    else printf(RED "\n\n>>> C'est %s qui commence ! <<<\n" RESET, joueur2);

    pause_console();
    syst_konane_espace();

    return  premier_joueur;
}


//Permet de faire une pause en pleine partie
void pause_console_en_plein_jeu()
{
    char c;
    printf("\n===== PAUSE - Appuyez sur 'p' pour reprendre ===== \n");
    fflush(stdout);
    do {
        c = getchar();
        //Vider le buffer
        while (getchar() != '\n');
        printf(remonter_ligne);
        printf("\r%s", effacer_ligne);
        fflush(stdout);
    } while (c != 'p' && c != 'P'); //on va accepter meme si l'utilisatuer entre p maj ou min

    //Effacer le message de pause
    printf(remonter_ligne);
    printf("\r%s", effacer_ligne);
    fflush(stdout);
    printf(remonter_ligne);
    printf("\r%s", effacer_ligne);
    fflush(stdout);
}


//Permet de g�rer la saisie et choisir un pion contenu dans le tableau
int gestion_de_saisie()
{
    char saisie[10];
    printf("\n");

    do
    {
        scanf("%s", saisie);
        while (getchar() != '\n');

        if (strcmp(saisie, "99") == 0)
        {
            return -99;
        }
        if (strcmp(saisie, "p") == 0 || strcmp(saisie, "P") == 0)
        {
            pause_console_en_plein_jeu();
            continue;
        }

        if ((strlen(saisie) != 2) || (saisie[0] < '1' || saisie[0] > '7' || saisie[1] < '1' || saisie[1] > '7'))
        {
            printf("%sErreur : Position invalide.%s\n", ROUGE, RESET);
            continue;
        }
        int valeur = (saisie[0] - '0') * 10 + (saisie[1] - '0');
        return valeur;
    } while (1);
}
