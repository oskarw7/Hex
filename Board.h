#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

#define MAX_LINE 66 // najdłuższa linia w pliku wejściowym + '\0'
#define MAX_SIZE 11 // największy możliwy rozmiar planszy
#define ADJACENT_FIELDS 6 // liczba sąsiednich pól

// Struktura przechowująca stan planszy
typedef struct BoardState{
    char board[MAX_SIZE][MAX_SIZE];
    int size;
    int blue_count;
    int red_count;
} BoardState;

// Struktura przechowująca współrzędne pola planszy
typedef struct Field{
    int y;
    int x;
} Field;

// Oblicza rozmiar planszy
int count_size(const char* line);

// Zeruje stan planszy)
void init_state(BoardState* board);

#endif
