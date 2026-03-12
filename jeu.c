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
#define CV   "\033[45m"
#define CB  "\033[44m"

#define effacer_ligne "\033[2K"
#define remonter_ligne "\033[1A"


//Pour gerer les couleurs de la fonction affichage
#define BG_BLACK "\033[40m"
#define BG_WHITE "\033[47m"
#define RED   "\033[31m"
#define RESET    "\033[0m"
#define FG_BLACK "\033[30m"
#define FG_WHITE "\033[37m"

#include "jeu.h"
#include "menu.h"

//Compte le nombre d'espace vide dans le tableau
int espace_vide()
{
    int n=0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (T[i][j]=='0') n++;
        }
    }
    return n;
}


//Efface le contenu du terminal et affiche le texte "KONANE"
void syst_konane_espace2()
{
    system("cls");
    konane();
    printf("\n\n");
}

//Permet de faire une pause et permet au joueur de voir un message donnée
void pause_console2()
{
    printf("\nAppuyez sur Entree pour continuer...");
    while(getchar() != '\n');
    getchar();
}

//Créer la grille pour la première fois
void grille_initiale()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) T[i][j] = 'W';
            else T[i][j] = 'B';
        }
    }
}

//Permet d'afficher la grille
void affiche_grille()
{
    printf("\n%53s", "");
    for (int j = 0; j < 7; j++) printf(RED " %d   " RESET, j + 1);
    printf("\n\n");

    for (int i = 0; i < 7; i++)
    {
        printf("%48s", "");
        printf(RED " %d  " RESET, i + 1);

        for (int j = 0; j < 7; j++)
        {
            char c = T[i][j];
            if (c=='0')
            {
                c= ' ';
                if ((i + j) % 2 == 0) printf("%s%s  %c  %s", BG_WHITE, FG_BLACK, c, RESET);
                else printf("%s%s  %c  %s", BG_BLACK, FG_WHITE, c, RESET);
                continue;
            }
            if ((i + j) % 2 == 0)
                printf("%s%s  %c  %s", BG_WHITE, FG_BLACK, c, RESET);
            else
                printf("%s%s  %c  %s", BG_BLACK, FG_WHITE, c, RESET);
        }
        printf("\n\n");
    }
    if (espace_vide()>=2) {
        printf("%s %80s %s\n\n", JAUNE, "=== Abandon (tapez 99) ===", RESET);
        printf("%s %79s %s\n\n", JAUNE, "=== Pause (tapez p) ===", RESET);
    }


}

//Permet de recuperer le nom des joueurs
void init_joueurs(int avec_machine)
{
    printf("\n\n%s", "Ecrivez votre nom (mettez des tirets_bas pour les espaces) :\n\n");
    printf("%s", ">>> Joueur 1 : ");
    scanf("%49s", joueur1);
    if (avec_machine==0)
    {
        printf("\n%s", ">>> Joueur 2 : ");
        scanf("%49s", joueur2);
    }

    else if(avec_machine==1) strcpy(joueur2, "Machine");
    else if(avec_machine==2) strcpy(joueur2, "Machine2");
    syst_konane_espace2();
}

//Gère le retrait du tout premier pion noir
int choix_retrait_initial(int est_machine)
{
    int positions[5][2] = {{3, 3}, {0, 0}, {0, 6}, {6, 0}, {6, 6}};
    int l, c;
    if (est_machine)
    {
        int choix = rand()%5;
        l = positions[choix][0];
        c = positions[choix][1];
        return l*10 + c;
    }
    int pos;
    while (1)
    {
        printf("Position (centre ou coin) : ");
        pos=gestion_de_saisie();

        l = pos/10 -1;
        c = pos%10 -1;
        if (!((l == 3 && c == 3) || ((l == 0 || l == 6) && (c == 0 || c == 6))))
        {
            printf("%sPosition invalide : centre ou coin uniquement.%s\n", ROUGE, RESET);
            continue;
        }
        return l * 10 + c;
    }
}

//Verifie si des coordonnées sont adjacentes
int est_adjacente(int l1, int c1, int l2, int c2)
{
    return (l1 == l2 && abs(c1 - c2) == 1) || (c1 == c2 && abs(l1 - l2) == 1);
}

//Permet le retrait des premiers pions (en prenant en considération les cas ou les IA joue également)
void initiation(int tour)
{
    int l1, c1, l2, c2;
    int pos;

    grille_initiale();
    printf("%s %79s %s\n\n",  JAUNE,"=== INITIALISATION ===", RESET);
    affiche_grille();

    char* nom1 = (tour == 0) ? joueur1 : joueur2;
    char* nom2 = (tour == 0) ? joueur2 : joueur1;

    if (strcmp(nom1, "Machine") == 0 ||strcmp(nom1, "Machine2") == 0)
    {
        printf("\n\n%sretrait d'une piece par la machine%s\n", JAUNE, RESET);
        pause_console2();
        pos = choix_retrait_initial(strcmp(nom1, "Machine") == 0 ||strcmp(nom1, "Machine2") == 0);

        l1=pos / 10 ;
        c1=pos % 10;
        T[l1][c1] = '0';
        piece_joueur = 'W';
        piece_machine = 'B';
    }
    else
    {
        if(tour==0){
                piece_joueur = 'B';
        piece_machine = 'W';

        }
        else
        {
                piece_joueur = 'W';
        piece_machine = 'B';

        }

        printf("\n\n%s, retire une piece %sNOIRE (B)%s (ex: 33)\n", nom1, ROUGE, RESET);
        pos = choix_retrait_initial(strcmp(nom1, "Machine") == 0 ||strcmp(nom1, "Machine2") == 0);
        l1=pos / 10 ;
        c1=pos % 10;
        T[l1][c1] = '0';
        printf("%sOK%s\n", VERT, RESET);
    }

    syst_konane_espace2();
    printf("%s %79s %s\n\n",  JAUNE,"=== INITIALISATION ===", RESET);
    affiche_grille();

    if (strcmp(nom2, "Machine") == 0 ||strcmp(nom2, "Machine2") == 0)
    {
        int adjacente[4][2] = {{l1-1, c1}, {l1+1, c1}, {l1, c1-1}, {l1, c1+1}};
        printf("\n\n%sRetrait d'une piece adjacente par la machine%s\n", JAUNE, RESET);
        pause_console2();
        while (1)
        {
            int choix = rand() % 4;
            l2 = adjacente[choix][0];
            c2 = adjacente[choix][1];
            if (T[l2][c2] == piece_machine)
            {
                T[l2][c2] = '0';
                break;
            }
        }
    }
    else
    {
        printf("\n\n%s, retire une piece %sBLANCHE adjacente%s\n", nom2, BLANC, RESET);

        do
        {
            printf("Position : ");
            pos=gestion_de_saisie();

            l2 = pos/10 - 1;
            c2 = pos%10 - 1;
            if (T[l2][c2] == 'W')
            {
                if (est_adjacente(l1,c1,l2,c2))
                {
                    T[l2][c2] = '0';
                    printf("%sOK!%s\n", VERT, RESET);
                    break;
                }
                printf("%sDoit etre adjacente!%s\n", ROUGE, RESET);
            }
            else printf("%sMauvaise position!%s\n", ROUGE, RESET);
        } while (1);
    }

    syst_konane_espace2();

}

//Vérifie si une capture respecte toutes les règles
int est_coup_legal(char T[7][7], int l1, int c1, int l2, int c2, char piece)
{
    if (c2<0 || c2>=7 || l2<0 || l2>=7) return 0;
    if (T[l1][c1] != piece || T[l2][c2] != '0') return 0;

    int dl = l2 - l1;
    int dc = c2 - c1;

    if (dl == 0 && dc != 0 && abs(dc) == 2)
    {
        int dir = (dc > 0) ? 1 : -1;
        if (T[l1][c1 + dir] != '0' && T[l1][c1 + dir] != piece) return 1;
    }

    if (dc == 0 && dl != 0 && abs(dl) == 2)
    {
        int dir = (dl > 0) ? 1 : -1;
        if (T[l1 + dir][c1] != '0' && T[l1 + dir][c1] != piece) return 1;
    }

    return 0;
}

//Permet de faire une capture
void deplacer_piece(char T[7][7], int l1, int c1, int l2, int c2)
{
    char piece = T[l1][c1];
    T[l2][c2] = piece;
    T[l1][c1] = '0';
    T[(l1 + l2)/2][(c1 + c2)/2] = '0';
}

//Permet de savoir si un joueur a encore des captures disponibles(si non il perd la partie)
int peut_jouer(char T[7][7], char piece)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (T[i][j] == piece)
            {
                int moves[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
                for (int m = 0; m < 4; m++)
                {
                    int ni = i + moves[m][0];
                    int nj = j + moves[m][1];
                    if (ni >= 0 && ni < 7 && nj >= 0 && nj < 7)
                    {
                        if (est_coup_legal(T, i, j, ni, nj, piece)) return 1;
                    }
                }
            }
        }
    }
    return 0;
}

//Enumère tous les coups possibles pour l'ia simple
int liste_coup_legal_Machine(char T[7][7], char piece)
{
    int Machine_Moves[100];
    int moves=0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
          if (T[i][j] == piece)
          {
              if (est_coup_legal(T,i,j,i+2,j,piece))
              {
                  Machine_Moves[moves] = i*1000 + j*100 + (i+2)*10 + (j);
                   moves++;
              }
              if (est_coup_legal(T,i,j,i-2,j,piece))
              {
                  Machine_Moves[moves] = i*1000 + j*100 + (i-2)*10 + (j);
                  moves++;
              }
              if (est_coup_legal(T,i,j,i,j-2,piece))
              {
                  Machine_Moves[moves] = i*1000 + j*100 + i*10 + j-2;
                  moves++;
              }
              if (est_coup_legal(T,i,j,i,j+2,piece))
              {
                  Machine_Moves[moves] = i*1000 + j*100 + i*10 + j+2;
                  moves++;
              }
          }
        }
    }

    if (moves == 0) return -1;
    return Machine_Moves[rand()%moves];
}

//Permet de faire une capture multiple (identifie les captures possibles et oblige la progression jusqqu'à la fin)
void capture_multiple(int ligne, int colonne, char piece, int est_machine)
{

    int directions[4][2] = {{ 0,  2},
                            { 0, -2},
                            { 2,  0},
                            {-2,  0}};

    int captures_possibles[4];
    int nbr = 0;

    for (int i = 0; i < 4; i++)
    {
        int l2 = ligne + directions[i][0];
        int c2 = colonne + directions[i][1];
        if (est_coup_legal(T, ligne, colonne, l2, c2, piece))
        {
            captures_possibles[nbr] = i;
            nbr++;
        }
    }

    if (nbr == 0) return;
    int choix, l2, c2, pos;

    if (est_machine)
    {
        pos=rand() % nbr;
        choix = captures_possibles[pos];

    }
    else
    {
        do
        {
            int arr;
            printf("Arrivee (capture obligatoire) : ");
            arr = gestion_de_saisie(2);
            l2 = arr / 10 - 1;
            c2 = arr % 10 - 1;
            for (int i = 0; i < nbr; i++)
            {
                int d = captures_possibles[i];
                if (ligne + directions[d][0] == l2 && colonne + directions[d][1] == c2)
                {
                    choix = d;
                    goto capture_valide;
                }
            }
            printf("Capture invalide.\n");
        } while (1);
    }

    capture_valide:
    l2 = ligne + directions[choix][0];
    c2 = colonne + directions[choix][1];
    deplacer_piece(T, ligne, colonne, l2, c2);
    capture_multiple(l2, c2, piece, est_machine);
}

//Gère les tours de jeu, et permet de savoir quand un joueur n'a plus de coup à jouer et affiche une message de fin de partie
int jouer_tour(char T[7][7], char *nom, char piece)
{
    int l1, c1, l2, c2;
    int temp;
    int dep, arr;
    int avec_Machine=0;
    printf("\n\n%s=== %s (%s%c%s) ===%s\n", JAUNE, nom, (piece == 'B') ? ROUGE : BLANC, piece, RESET, RESET);

    if (!peut_jouer(T, piece))
    {
        printf("\n%s%s ne peut plus jouer!%s\n", ROUGE, nom, RESET);
        return 0;
    }
    do
    {
        if (strcmp(nom, "Machine")==0)
        {
            pause_console();
            temp=liste_coup_legal_Machine(T,piece);
            if (temp == -1) return 0;
            l1 = temp / 1000 ;
            c1 = (temp/100) % 10 ;
            l2 = (temp/10) % 10 ;
            c2 = temp % 10 ;
            avec_Machine=1;
        }
        else
        {
            do
            {
                printf("Depart : ");
                dep=gestion_de_saisie();

                if (dep == -99) return 0;  //gestion arret

                l1 = dep/10 - 1;
                c1 = dep%10 - 1;
                break;
            } while (1);

            do
            {
                printf("Arrivee : ");
                arr=gestion_de_saisie();

                if (arr == -99) return 0;  //gestion arret en plein jeu

                l2 = arr/10 - 1;
                c2 = arr%10 - 1;
                break;
            } while (1);
        }
        if (l1 >= 0 && l1 <= 6 && c1 >= 0 && c1 <= 6 && l2 >= 0 && l2 <= 6 && c2 >= 0 && c2 <= 6)
        {
            if (est_coup_legal(T, l1, c1, l2, c2, piece))
            {
                deplacer_piece(T, l1, c1, l2, c2);
                capture_multiple(l2, c2, piece, avec_Machine);
                break;
            }
        }
        printf("%sMouvement invalide!%s\n", ROUGE, RESET);
    } while (1);
    return 1;
}

//Gère le jeu entre soit IA avancée soit (humain+ai_simple)
int jouer_tour_generique(char T[7][7], char *nom, char piece)
{
    if (strcmp(nom, "Machine2") == 0)
    {
        printf("\n%s=== Machine (%c) ===%s\n", JAUNE, piece, RESET);
        pause_console();
        return jouer_coup_ia(T, piece);   // IA avancée
    }
    else
    {
        return jouer_tour(T, nom, piece); // Humain + Ai simple
    }
}

//Permet de commencer le jeu, c'est un ensemble de toutes les fonctions écrites en haut
void commencer_le_jeu()
{
    int tour = tirage_premier_joueur();
    initiation(tour);

    while (1)
    {
        syst_konane_espace2();
        printf("%s %73s %s\n\n", JAUNE, "=== JEU ===", RESET);
        affiche_grille();

        if (tour == 0)
        {
            if (!jouer_tour_generique(T, joueur1, piece_joueur))
            {
                printf("\n%s>>> %s GAGNE! <<<%s\n", VERT, joueur2, RESET);
                break;
            }
            tour = 1;
        }
        else
        {
            if (!jouer_tour_generique(T, joueur2, piece_machine))
            {
                printf("\n%s>>> %s GAGNE! <<<%s\n", VERT, joueur1, RESET);
                break;
            }
            tour = 0;
        }
    }

    pause_console();
}

//Joueur contre Joueur
void j_vs_j()
{
    int avec_machine = 0;
    init_joueurs(avec_machine);
    commencer_le_jeu();
}

//Joueur contre IA simple
void j_vs_machine()
{
    int avec_machine = 1;
    init_joueurs(avec_machine);
    commencer_le_jeu();
}

//Joueur contre IA avancée
void j_vs_machine2()
{
    int avec_machine = 2;
    init_joueurs(avec_machine);
    commencer_le_jeu();
}


//Les fonctions qui permettent à l'IA avancée de jouer

#define PROFONDEUR 4 //Profondeur = 4
#define INF 999999

//Permet de faire des copies temporaires de l'état actuelle du tableau afin de permettre à l'IA de simuler des coups
void copier_plateau(char src[7][7], char dest[7][7])
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            dest[i][j] = src[i][j];
}


//Applique des coups aux copies de tableaux afin de simuler des parties
void appliquer_coup(char T[7][7], int coup, char piece)
{
    int l = coup / 1000;
    int c = (coup / 100) % 10;
    int l2 = (coup / 10) % 10;
    int c2 = coup % 10;

    deplacer_piece(T, l, c, l2, c2);

    int directions[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

    while (1)
    {
        int saut_trouve = 0;
        for (int d = 0; d < 4; d++)
        {
            int l_suivant = l2 + directions[d][0];
            int c_suivant = c2 + directions[d][1];

            if (l_suivant >= 0 && l_suivant < 7 && c_suivant >= 0 && c_suivant < 7)
            {
                if (est_coup_legal(T, l2, c2, l_suivant, c_suivant, piece))
                {
                    deplacer_piece(T, l2, c2, l_suivant, c_suivant);
                    l2 = l_suivant;
                    c2 = c_suivant;
                    saut_trouve = 1;
                    break;
                }
            }
        }
        if (!saut_trouve) break;
    }
}

//Compte le nombre de pions qui peuvent bouger et donne une liste des coups possibles en fonction de l'etat du tableau
int generer_et_compter(char T[7][7], char piece, int coups[])
{
    int count = 0;
    int directions[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (T[i][j] == piece)
            {
                for (int d = 0; d < 4; d++)
                {
                    int ni = i + directions[d][0];
                    int nj = j + directions[d][1];
                    if (ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && est_coup_legal(T, i, j, ni, nj, piece))
                    {
                        if (coups != NULL)
                            coups[count] = i*1000 + j*100 + ni*10 + nj;
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

//Permet d'évaluer un tableau (donne un score en fonction des pions qui peuvent encore capturer)
int evaluer_position(char T[7][7], char piece)
{
    int pions_joueur = generer_et_compter(T, piece, NULL);
    char adv = (piece == 'B') ? 'W' : 'B';
    int pions_adv = generer_et_compter(T, adv, NULL);

    if (pions_adv == 0) return 10000;
    if (pions_joueur == 0) return -10000;
    return (pions_joueur * 1000) / pions_adv;
}

//La fonction minimax avec alpha-beta pruning, afin de permettre à l'IA de connaitre quel coup joué
int minimax_ab(char T[7][7], int depth, int alpha, int beta, char joueur)
{
    if (depth == 0)
        return evaluer_position(T, joueur);

    int coups[100];
    int num_coups = generer_et_compter(T, joueur, coups);

    if (num_coups == 0)
        return -10000;

    char adv = (joueur == 'B') ? 'W' : 'B';

    for (int i = 0; i < num_coups; i++)
    {
        char T_copie[7][7];
        copier_plateau(T, T_copie);
        appliquer_coup(T_copie, coups[i], joueur);

        int score = -minimax_ab(T_copie, depth - 1, -beta, -alpha, adv);

        if (score > alpha)
            alpha = score;
        if (alpha >= beta)
            break;
    }

    return alpha;
}

//Permet à l'IA de jouer les coups les plus optimaux
int jouer_coup_ia(char T[7][7], char piece)
{
    int coups[100];
    int num_coups = generer_et_compter(T, piece, coups);

    if (num_coups == 0)
        return 0;

    int meilleur_score = -INF;
    int meilleur_coup = coups[0];
    char adv = (piece == 'B') ? 'W' : 'B';

    for (int i = 0; i < num_coups; i++)
    {
        char T_copie[7][7];
        copier_plateau(T, T_copie);
        appliquer_coup(T_copie, coups[i], piece);

        int score = -minimax_ab(T_copie, PROFONDEUR - 1, -INF, INF, adv);

        if (score > meilleur_score)
        {
            meilleur_score = score;
            meilleur_coup = coups[i];
        }
    }

    int l1 = meilleur_coup / 1000;
    int c1 = (meilleur_coup / 100) % 10;
    int l2 = (meilleur_coup / 10) % 10;
    int c2 = meilleur_coup % 10;

    printf("IA joue : (%d,%d) -> (%d,%d)\n", l1+1, c1+1, l2+1, c2+1);
    appliquer_coup(T, meilleur_coup, piece);

    return 1;
}
