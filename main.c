#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "jeu.h"

////
#include "menu.c"
#include "jeu.c"

//Navigation entre les fonctions grace au "switch" dans la fonction main()


int main()
{
    int choix=0;
    int en_jeu = 1;

    srand(time(NULL));

    while (en_jeu)
    {
        system("cls");
        konane();

        switch (choix)
        {
            case 0: case 21:
                 choix = menu_principale();
                 break;
            case 1:
                 choix = choix_adversaire();
                 break;
            case 11:
                 choix=1;
                 j_vs_j();
                 break;
            case 12:
                 choix=1;
                 j_vs_machine();
                break;
            case 13 :
                 choix=1;
                 j_vs_machine2();
            case 14:
                 choix=0;
                 break;
            case 2:
                 choix = regles_jeu();
                 break;
            case 3: case 15: case 22:
                en_jeu = 0;
                break;
        }
    }

    printf("\nMerci d'avoir joue a KONANE !\n");
    return 0;
}
