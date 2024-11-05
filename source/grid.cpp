#include <iostream>
#include <stdio.h>

#include "../header/grid.h"

using namespace std;

void drawgrid(int grid[6][7]);
bool place_token(int grid[6][7], int col, int player);
int end_game(int grid[6][7]);

void drawgrid(int grille[6][7]){
    cout << "\t";
    for (int lin = 0; lin < 6; lin++){
        cout << "\t|";
        for (int col = 0; col < 7; col++){
            if (grille[lin][col] == 1) {
                cout << "\033[32mX\033[37m";
            } 
            else if (grille[lin][col] == 2) {
                cout << "\033[31mO\033[37m";
            }
            else {
                cout << "-";
            }
            cout << "|";
        }
        cout << "\n\t";
    }
    cout << "\t";
    for (int j = 1; j <= 7; j++)
    {
        cout <<" "<<j;
    }
    cout << "\n\n";
    
}

bool place_token(int grid[6][7], int column, int player){
    for (int line = 5 ; line >= 0; line--){
        if (grid[line][column - 1] == 0){
            grid[line][column - 1] = player;
            return true;
        }
    }
    return false;
}

//Fonction qui stoppe le jeu si toutes les cases sont pleines
int end_game(int grid[6][7]) {
    int col_end = 0;
    for(int j=0; j<7; j++)
    {
        if (grid[0][j] == 0) {
            continue;
        }
        else
        {
            col_end += 1;
        }
    }
    return col_end;
}
