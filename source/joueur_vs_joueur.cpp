#include <iostream>
#include <string>
#include <stdio.h>

#include "../header/joueur_vs_joueur.h"
#include "../header/grid.h"

using namespace std;

bool win_game_1(int grid[6][7], int player);


void joueur_vs_joueur(int grid[6][7], int player, int p1, int p2, string choix) {
    while(true) {
        int col_end = end_game(grid);

        //Arrêter le jeu si toutes les cases sont pleines
        if (col_end == 7) {
            drawgrid(grid);
            cout <<"Toutes les cases sont pleines. Le jeu est termine\n";
            break;
        }

        bool player_1_win = win_game_1(grid, p1);
        bool player_2_win = win_game_1(grid, p2);
        //Arrêter le jeu si un joueur gagne
        if (player_1_win == true) {
            break;
        }
        else if (player_2_win == true) {
            break;
        }
        

        cout <<"Joueur "<<player<<", choisissez une colonne : ";
        cin >> choix;
        bool success = false;
        if (choix.size() == 1){
            if (choix[0] > '0' && choix[0] <= '7'){
                int col = choix[0]  - '0';
                success = place_token(grid, col, player);
            }
        }

        system("CLS");
        if (!success) {
            system("CLS");
            drawgrid(grid);
            cout << "Votre choix est incorrect\n";
        } 
        else {
            if (player == 1) {
                player = 2;
            } 
            else {
                player = 1;
            } 
            drawgrid(grid);
        }
    }
}

bool win_game_1(int grid[6][7], int player) {
    bool p_win = false;

    //A la verticale
    for (int j=0; j<7; j++)
    {
        if (p_win == true) {
            break;
        }
        for (int i=0; i<3; i++)
        {
            if (grid[i][j] == player && grid[i+1][j] == player && grid[i+2][j] == player && grid[i+3][j] == player)
            {
                p_win = true;
                drawgrid(grid);
                cout <<"Le joueur "<< player <<" a aligne 4 pions en verticale, il gagne donc la partie\n";
                break;
            }
        }
    }

    //A l'horizontale
    for (int j=0; j<4; j++)
    {
        if (p_win == true) {
            break;
        }
        for (int i=0; i<6; i++)
        {
            if (grid[i][j] == player && grid[i][j+1] == player && grid[i][j+2] == player && grid[i][j+3] == player)
            {
                p_win = true;
                drawgrid(grid);
                cout <<"Le joueur "<< player <<" a aligne 4 pions en horizontale, il gagne donc la partie\n";
                break;
            }
        }
    }
    
    //En diagonale descendante
    for (int j=0; j<4; j++)
    {
        if (p_win == true) {
            break;
        }
        for (int i=0; i<3; i++)
        {
            if (grid[i][j] == player && grid[i+1][j+1] == player && grid[i+2][j+2] == player && grid[i+3][j+3] == player)
            {
                p_win = true;
                drawgrid(grid);
                cout <<"Le joueur "<< player <<" a aligne 4 pions en diagonale, il gagne donc la partie\n";
                break;
            }
        }
    }

    //En diagonale montante
    for (int j=0; j<4; j++)
    {
        if (p_win == true) {
            break;
        }
        for (int i=3; i<6; i++)
        {
            if (grid[i][j] == player && grid[i-1][j+1] == player && grid[i-2][j+2] == player && grid[i-3][j+3] == player)
            {
                p_win = true;
                drawgrid(grid);
                cout <<"Le joueur "<< player <<" a aligne 4 pions en diagonale, il gagne donc la partie\n";
                break;
            }
        }
    }

    return p_win;
}
