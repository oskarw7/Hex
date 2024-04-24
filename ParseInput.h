#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <stdio.h>
#include <string.h>

#include "Board.h"

// Sprawdza, czy linia jest pierwszą linią wejścia danej planszy
int isFirstLine(const char* line);

// Wstawia poziomą linię z wejścia na odpowiednie miejsca w tablicy reprezentującej planszę
// Tablica to plansza obrócona o 45 stopni przeciwnie do ruchu wskazówek zegara
void fill_diagonal(BoardState* board, const char* diagonal);

// Wczytuje linię z wejścia, wykrywa koniec planszy i koniec wejścia
void get_line(BoardState* board, char* buffer);

#endif
