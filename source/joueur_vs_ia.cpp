#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include "../header/joueur_vs_ia.h"
#include "../header/grid.h"

using namespace std;

int ia_play(int grid[6][7], int p1, int ia);
bool ia_in_danger(int grid[6][7], int p1);
int ia_defensive(int grid[6][7], int p1);
int ia_offensive(int grid[6][7], int ia);
bool win_game_2(int grid[6][7], int player);


void joueur_vs_ia(int grid[6][7], int player, int p1, int ia, string choix) {
    while(true) {
        int col_end = end_game(grid);

        //Arrêter le jeu si toutes les cases sont pleines
        if (col_end == 7) {
            drawgrid(grid);
            cout <<"Toutes les cases sont pleines. Le jeu est termine\n";
            break;
        }

        bool player_win = win_game_2(grid, p1);
        bool ia_win = win_game_2(grid, ia);
        //Arrêter le jeu si un joueur gagne
        if (player_win == true) {
            break;
        }
        else if (ia_win == true) {
            break;
        }
        
        if (player == p1)
        {
            cout <<"Choisissez une colonne : ";
            cin >> choix;
            bool success = false;
            if (choix.size() == 1){
                if (choix[0] > '0' && choix[0] <= '7'){
                    int col = choix[0]  - '0';
                    success = place_token(grid, col, p1);
                }
            }

            system("CLS");
            if (!success) {
                system("CLS");
                drawgrid(grid);
                cout << "Votre choix est incorrect\n";
            }
            else
            {
                player = ia;
            }
        }
        
        else { //L'IA Joue
            int col = ia_play(grid, p1, ia);
            if (col_end < 6) {
                place_token(grid, col, ia);
                system("CLS");
                drawgrid(grid);
                cout << "L'IA a choisi la colonne " <<col<<"\n";
                player = p1;
            }
            else if (col_end == 6) {
                for (int j=0; j<7; j++) {
                    if (grid[0][j] == 0) {
                        col = j+1;
                        break;
                    }
                }
                place_token(grid, col, ia);
                system("CLS");
                drawgrid(grid);
                cout << "L'IA a choisi la colonne " <<col<<"\n";
                player = p1;
            }
        }
    }
}


int ia_play(int grid[6][7], int p1, int ia) {
    int c;

    bool danger = ia_in_danger(grid, p1);
    if (danger == true)
    {
        c = ia_defensive(grid, p1);
    }
    else
    {
        c = ia_offensive(grid, ia);
    }
    
    return c;
    
}

bool ia_in_danger(int grid[6][7], int p1) {
    bool danger = false;

    //Danger en diagonale descendante
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<3; i++)
        {
            if (grid[i][j] == p1 && grid[i+1][j+1] == p1 && grid[i+2][j+2] == p1 && grid[i+3][j+3] == 0) {
                if (i+3 == 5) {
                    danger = true;
                }
                
                else if (i+3 < 5 && grid[i+4][j+3] != 0) {
                    danger = true;
                }
            }
        }
    }

    //Danger en diagonale montante
    for (int j=0; j<4; j++)
    {
        for (int i=3; i<6; i++)
        {
            if (grid[i][j] == p1 && grid[i-1][j+1] == p1 && grid[i-2][j+2] == p1 && grid[i-3][j+3] == 0 && grid[i-2][j+3] != 0)
            {
                danger = true;
            }
        }
    }

    //Danger à la verticale
    for (int j=0; j<7; j++)
    {
        for (int i=5; i>2; i--)
        {
            if (grid[i][j] == p1 && grid[i-1][j] == p1 && grid[i-2][j] == p1 && grid[i-3][j] == 0)
            {
                danger = true;
            }
        }
    }

    //Danger à l'horizontale
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<6; i++)
        {
            if (grid[i][j] == p1 && grid[i][j+1] == p1 && grid[i][j+2] == p1 && grid[i][j+3] == 0) {
                if (i == 5) {
                    danger = true;
                }
                else if (i+1 <= 5 && grid[i+1][j+3] != 0) {
                    danger = true;
                }
            }

            else if (grid[i][j] == p1 && grid[i][j+1] == p1 && grid[i][j+2] == 0 && grid[i][j+3] == p1) {
                if (i == 5) {
                    danger = true;
                }
                else if (i+1 <= 5 && grid[i+1][j+2] != 0) {
                    danger = true;
                }
            }

            else if (grid[i][j] == p1 && grid[i][j+1] == 0 && grid[i][j+2] == p1 && grid[i][j+3] == p1) {
                if (i == 5) {
                    danger = true;
                }
                else if (i+1 <= 5 && grid[i+1][j+1] != 0) {
                    danger = true;
                }
            }

            else if (grid[i][j] == 0 && grid[i][j+1] == p1 && grid[i][j+2] == p1 && grid[i][j+3] == p1) {
                if (i == 5) {
                    danger = true;
                }
                else if (i+1 <= 5 && grid[i+1][j] != 0) {
                    danger = true;
                }
            }
        }
    }
    

    return danger;
}

int ia_defensive(int grid[6][7], int p1) {
    int c;

    //Bloquer le joueur en diagonale descendante
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<3; i++)
        {
            if (grid[i][j] == p1 && grid[i+1][j+1] == p1 && grid[i+2][j+2] == p1 && grid[i+3][j+3] == 0) {
                if (i+3 == 5)
                {
                    c = j+4;
                }
                
                else if (i+3 < 5 && grid[i+4][j+3] != 0) {
                    c = j+4;
                }
            }
        }
    }

    //Bloquer le joueur en diagonale montante
    for (int j=0; j<4; j++)
    {
        for (int i=3; i<6; i++)
        {
            if (grid[i][j] == p1 && grid[i-1][j+1] == p1 && grid[i-2][j+2] == p1 && grid[i-3][j+3] == 0 && grid[i-2][j+3] != 0)
            {
                c = j+4;
            }
        }
    }

    //Bloquer le joueur à la verticale
    for (int j=0; j<7; j++)
    {
        for (int i=5; i>2; i--)
        {
            if (grid[i][j] == p1 && grid[i-1][j] == p1 && grid[i-2][j] == p1 && grid[i-3][j] == 0)
            {
                c = j+1;
            }
        }
    }

    //Bloquer le joueur à l'horizontale
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<6; i++)
        {
            if (grid[i][j] == p1 && grid[i][j+1] == p1 && grid[i][j+2] == p1 && grid[i][j+3] == 0) {
                if (i == 5) {
                    c = j+4;
                }
                else if (i+1 <= 5 && grid[i+1][j+3] != 0) {
                    c = j+4;
                }
            }

            else if (grid[i][j] == p1 && grid[i][j+1] == p1 && grid[i][j+2] == 0 && grid[i][j+3] == p1) {
                if (i == 5) {
                    c = j+3;
                }
                else if (i+1 <= 5 && grid[i+1][j+2] != 0) {
                    c = j+3;
                }
            }

            else if (grid[i][j] == p1 && grid[i][j+1] == 0 && grid[i][j+2] == p1 && grid[i][j+3] == p1) {
                if (i == 5) {
                    c = j+2;
                }
                else if (i+1 <= 5 && grid[i+1][j+1] != 0) {
                    c = j+2;
                }
            }

            else if (grid[i][j] == 0 && grid[i][j+1] == p1 && grid[i][j+2] == p1 && grid[i][j+3] == p1) {
                if (i == 5) {
                    c = j+1;
                }
                else if (i+1 <= 5 && grid[i+1][j] != 0) {
                    c = j+1;
                }
            }
        }
    }
    

    return c;
}

int ia_offensive(int grid[6][7], int ia) {
    int list_cols[7];
    int available_cols[] = {};
    int c;
    int n = 0, a = 0;

    for (int col = 1; col <= 7; col++) {
        if (grid[0][col-1] == 0) {
            list_cols[n] = col;
            n+=1;
        }
    }

    for (int k=0; k<7; k++) {
        if (list_cols[k] == 0) {
            break;
        }
        available_cols[k] = list_cols[k];
        a += 1;
    }
    

    if (a > 1) {
        c = available_cols[rand() % a];
    }
    else if (a == 1) {
        c = available_cols[0];
    }
    else {
        c = 0;
        return c;
    }
    

    //Attaquer en diagonale descendante
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<3; i++)
        {
            if (grid[i][j] == ia && grid[i+1][j+1] == ia && grid[i+2][j+2] == ia && grid[i+3][j+3] == 0) {
                if (i+3 == 5)
                {
                    c = j+4;
                }
                
                else if (i+3 < 5 && grid[i+4][j+3] != 0) {
                    c = j+4;
                }
            }
        }
    }

    //Attaquer en diagonale montante
    for (int j=0; j<4; j++)
    {
        for (int i=3; i<6; i++)
        {
            if (grid[i][j] == ia && grid[i-1][j+1] == ia && grid[i-2][j+2] == ia && grid[i-3][j+3] == 0 && grid[i-2][j+3] != 0)
            {
                c = j+4;
            }
        }
    }

    //Attaquer à la verticale
    for (int j=0; j<7; j++)
    {
        for (int i=5; i>2; i--)
        {
            if (grid[i][j] == ia && grid[i-1][j] == ia && grid[i-2][j] == ia && grid[i-3][j] == 0)
            {
                c = j+1;
            }
        }
    }

    //Attaquer à l'horizontale
    for (int j=0; j<4; j++)
    {
        for (int i=0; i<6; i++)
        {
            if (grid[i][j] == ia && grid[i][j+1] == ia && grid[i][j+2] == ia && grid[i][j+3] == 0) {
                if (i == 5) {
                    c = j+4;
                }
                else if (i+1 <= 5 && grid[i+1][j+3] != 0) {
                    c = j+4;
                }
            }

            else if (grid[i][j] == ia && grid[i][j+1] == ia && grid[i][j+2] == 0 && grid[i][j+3] == ia) {
                if (i == 5) {
                    c = j+3;
                }
                else if (i+1 <= 5 && grid[i+1][j+2] != 0) {
                    c = j+3;
                }
            }

            else if (grid[i][j] == ia && grid[i][j+1] == 0 && grid[i][j+2] == ia && grid[i][j+3] == ia) {
                if (i == 5) {
                    c = j+2;
                }
                else if (i+1 <= 5 && grid[i+1][j+1] != 0) {
                    c = j+2;
                }
            }

            else if (grid[i][j] == 0 && grid[i][j+1] == ia && grid[i][j+2] == ia && grid[i][j+3] == ia) {
                if (i == 5) {
                    c = j+1;
                }
                else if (i+1 <= 5 && grid[i+1][j] != 0) {
                    c = j+1;
                }
            }
        }
    }

    return c;
}

//Fonction qui stoppe le jeu si un joueur gagne
bool win_game_2(int grid[6][7], int player) {
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
                if (player == 1) {
                    cout <<"Vous avez aligne 4 pions en verticale, vous gagnez donc la partie\n";
                    break;
                }
                else {
                    cout <<"L'IA a aligne 4 pions en verticale, elle gagne donc la partie\n";
                    break;
                }
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
                if (player == 1) {
                    cout <<"Vous avez aligne 4 pions en horizontale, vous gagnez donc la partie\n";
                    break;
                }
                else {
                    cout <<"L'IA a aligne 4 pions en horizontale, elle gagne donc la partie\n";
                    break;
                }
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
                if (player == 1) {
                    cout <<"Vous avez aligne 4 pions en diagonale, vous gagnez donc la partie\n";
                    break;
                }
                else {
                    cout <<"L'IA a aligne 4 pions en diagonale, elle gagne donc la partie\n";
                    break;
                }
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
                if (player == 1) {
                    cout <<"Vous avez aligne 4 pions en diagonale, vous gagnez donc la partie\n";
                    break;
                }
                else {
                    cout <<"L'IA a aligne 4 pions en diagonale, elle gagne donc la partie\n";
                    break;
                }
            }
        }
    }

    return p_win;
}
