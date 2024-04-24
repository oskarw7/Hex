#ifndef VALIDATEBOARD_H
#define VALIDATEBOARD_H

#include "Board.h"
#include "IsGameOver.h"

// Usuwa pionek na polu field z planszy
int remove_pawn(BoardState board, Field field, char color);

// Znajduje i-ty pionek danego koloru
Field find_pawn(BoardState board, char color, int index);

// Sprawdza, czy stan planszy jest możliwy - czy gra nie została zakończona wcześniej
int isBoardPossible(BoardState board);

// Sprawdza, czy plansza jest poprawna - czy proporcje liczby pionków są zachowane
int isBoardCorrect(BoardState board);

#endif