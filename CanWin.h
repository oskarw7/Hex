#ifndef CANWIN_H
#define CANWIN_H

#include "Board.h"
#include "IsGameOver.h"

// Określa, który gracz ma teraz ruch
char whosTurn(BoardState board);

// Sprawdza, czy naiwny przeciwnik ma możliwość zagrania X ruchów
// przy jednoczesnej wygranej gracza
int areFieldsEmpty(BoardState board, int pawn_count);

// Sprawdza, czy gracz może wygrać w X ruchach z naiwnym przeciwnikiem
int canWinWithNaive(BoardState board, char color, int moves_left, int moves_count);

int canWinWithPerfectIn1(BoardState board, char color);

int canWinWithPerfectIn2(BoardState board, char color);

#endif
