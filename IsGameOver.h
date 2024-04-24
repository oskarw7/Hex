#ifndef ISGAMEOVER_H
#define ISGAMEOVER_H

#include "Board.h"

// Sprawdza, czy pionki danego koloru tworzą linię ciągłą od jednego do drugiego brzegu własnego koloru
int dfs(char color, int isVisited[MAX_SIZE][MAX_SIZE], BoardState board, int y, int x);

// Sprawdza, czy gra się zakończyła przy użyciu algorytmu DFS
int isGameOver(BoardState board);

#endif