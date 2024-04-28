#ifndef CANWIN_H
#define CANWIN_H

#include "Board.h"
#include "IsGameOver.h"

// Określa, który gracz ma teraz ruch
char whosTurn(BoardState board);

// dodaje pionek na planszę dla gracza z zapytania
void add_pawn(BoardState* board, char color);

// usuwa pionek z planszy dla gracza z zapytania
void remove_pawn(BoardState* board, char color);

// dodaje pionek na planszę dla przeciwnika
void add_opponent_pawn(BoardState* board, char color);

// usuwa pionek z planszy dla przeciwnika
void remove_opponent_pawn(BoardState* board, char color);

// Sprawdza, czy naiwny przeciwnik ma możliwość zagrania X ruchów
// przy jednoczesnej wygranej gracza z zapytania
int areFieldsEmpty(BoardState board, int pawn_count);

// Sprawdza, czy gracz może wygrać w X ruchach z naiwnym przeciwnikiem
int canWinWithNaive(BoardState board, char color, int moves_left, int moves_count);

// Sprawdza, czy gracz może wygrać w 1 ruchu z perfekcyjnym przeciwnikiem
int canWinWithPerfectIn1(BoardState board, char color);

// Sprawdza, czy gracz może wygrać w 2 ruchach z perfekcyjnym przeciwnikiem
int canWinWithPerfectIn2(BoardState board, char color);

#endif
