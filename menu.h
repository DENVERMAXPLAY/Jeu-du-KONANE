#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

extern char T[7][7];
extern char joueur1[50];
extern char joueur2[50];
extern char piece_joueur, piece_machine;

void pause_console();
void konane();
int menu_principale();
int choix_adversaire();
int regles_jeu();
int tirage_premier_joueur();
void VIDER_BUFFER();
void pause_console_en_plein_jeu();
int gestion_de_saisie();

#endif
