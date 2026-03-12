#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
int espace_vide();
void grille_initiale();
void affiche_grille();

void init_joueurs(int avec_machine);
int choix_retrait_initial(int est_machine);
void initiation(int tour);

int est_adjacente(int l1, int c1, int l2, int c2);
int est_coup_legal(char T[7][7], int l1, int c1, int l2, int c2, char piece);
int peut_jouer(char T[7][7], char piece);
int liste_coup_legal_Machine(char T[7][7], char piece);
void capture_multiple(int ligne, int colonne, char piece, int est_machine);
int jouer_tour(char T[7][7], char *nom, char piece);
void deplacer_piece(char T[7][7], int l1, int c1, int l2, int c2);

int jouer_tour_generique(char T[7][7], char *nom, char piece);
void commencer_le_jeu();
int jouer_coup_ia(char T[7][7], char piece);


void j_vs_j();
void j_vs_machine();
void j_vs_machine2();

#endif
