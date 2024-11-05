#ifndef GRID_H
#define GRID_H

void drawgrid(int grid[6][7]);
bool place_token(int grid[6][7], int col, int player);
int end_game(int grid[6][7]);

#endif // GRID_H