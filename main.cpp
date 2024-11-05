#include <iostream>
#include <string>
#include <stdio.h>

#include "header/joueur_vs_joueur.h"
#include "header/joueur_vs_ia.h"
#include "header/grid.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string game_mode;
    string choix;
    char replay;
    int joueur = 1;
    int p1 = 1;
    int p2 = 2;

    cout << "\nBienvenue dans Puissance 4\n";
    cout << "\nChoisissez un mode de jeu :\n";
    cout << "1 -> Joueur vs Joueur\n";
    cout << "2 -> Joueur vs IA\n";
    cout << "0 -> Quitter\n";
    cin >> game_mode;

    while (game_mode[0] != '0' && game_mode[0] != '1' && game_mode[0] != '2')
    {
        system("CLS");
        cout << "Choix incorrect, veuillez choisir parmi les options suivantes :\n";
        cout << "1 -> Joueur vs Joueur\n";
        cout << "2 -> Joueur vs IA\n";
        cout << "0 -> Quitter\n";
        cin >> game_mode;
    }
    
    while (game_mode[0] != '0') {
        if (game_mode[0] == '1') {
            int grille[6][7] = {};
            system("CLS");
            drawgrid(grille);
            joueur_vs_joueur(grille, joueur, p1, p2, choix);
            cout << "\nVoulez-vous rejouer ? (o/n)";
            cin >> replay;
            if (replay == 'o') {
                cout << "\nChoisissez un mode de jeu :\n";
                cout << "1 -> Joueur vs Joueur\n";
                cout << "2 -> Joueur vs IA\n";
                cout << "0 -> Quitter\n";
                cin >> game_mode;
            }
            else {
                break;
            }
        }

        else if (game_mode[0] == '2') {
            int grille[6][7] = {};
            system("CLS");
            drawgrid(grille);
            joueur_vs_ia(grille, joueur, p1, p2, choix);
            cout << "\nVoulez-vous rejouer ? (o/n)";
            cin >> replay;
            if (replay == 'o') {
                cout << "\nChoisissez un mode de jeu :\n";
                cout << "1 -> Joueur vs Joueur\n";
                cout << "2 -> Joueur vs IA\n";
                cout << "0 -> Quitter\n";
                cin >> game_mode;
            }
            else {
                break;
            }
        }
    }
    
    return 0;
}
