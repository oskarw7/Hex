#include <stdio.h>
#include <string.h>

#include "Board.h"          // Zawiera funkcje inicjalizujące planszę i jej stan
#include "ParseInput.h"     // Zawiera funkcje parsujące wejście i wypełniające planszę
#include "ValidateBoard.h"  // Zawiera funkcje sprawdzające poprawność planszy i czy jej stan jest możliwy
#include "IsGameOver.h"     // Zawiera funkcje sprawdzające, czy gra się zakończyła
#include "CanWin.h"         // Zawiera funkcje sprawdzające, czy dany gracz może wygrać z naiwnym przeciwnikiem

// Zarządzanie wynikiem isGameOver
void isGameOverController(BoardState board){
    if(isBoardCorrect(board)){
        int result = isGameOver(board);
        if (result == BLUE_WON)
            printf("YES BLUE\n");
        else if (result == RED_WON)
            printf("YES RED\n");
        else
            printf("NO\n");
    } else
        printf("NO\n");
}

// Zarządzanie wynikiem isBoardPossible
void canWinWithNaiveController(BoardState board){
    if(isBoardCorrect(board)){
        canWinWithNaive(board, 'r', 1, 1) ? printf("YES\n") : printf("NO\n");
        canWinWithNaive(board, 'b', 1, 1) ? printf("YES\n") : printf("NO\n");
        canWinWithNaive(board, 'r', 2, 2) ? printf("YES\n") : printf("NO\n");
        canWinWithNaive(board, 'b', 2, 2) ? printf("YES\n\n") : printf("NO\n\n");
    } else
        printf("NO\nNO\nNO\nNO\n\n");
}

void canWinWithPerfectController(BoardState board){
    if(isBoardCorrect(board)){
        canWinWithPerfectIn1(board, 'r') ? printf("YES\n") : printf("NO\n");
        canWinWithPerfectIn1(board, 'b') ? printf("YES\n") : printf("NO\n");
        canWinWithPerfectIn2(board, 'r') ? printf("YES\n") : printf("NO\n");
        canWinWithPerfectIn2(board, 'b') ? printf("YES\n\n") : printf("NO\n\n");
    }
    else
        printf("NO\nNO\nNO\nNO\n\n");
}


int main() {
    BoardState board;
    init_state(&board);
    char buffer[MAX_LINE] = {'\0'};
    while(strcmp(buffer, "X")!=0){
        get_line(&board, buffer);
        if(board.size==0 && isFirstLine(buffer)){
            board.size = count_size(buffer);
        }
        else if(strcmp("BOARD_SIZE", buffer)==0){
            printf("%d\n", board.size);
        }
        else if(strcmp("PAWNS_NUMBER", buffer)==0){
            printf("%d\n", board.blue_count+board.red_count);
        }
        else if(strcmp("IS_BOARD_CORRECT", buffer)==0){
            (isBoardCorrect(board)) ? printf("YES\n") : printf("NO\n");
        }
        else if(strcmp("IS_GAME_OVER", buffer)==0){
            isGameOverController(board);
        }
        else if(strcmp("IS_BOARD_POSSIBLE", buffer)==0){
            if(isBoardCorrect(board))
                isBoardPossible(board) ? printf("YES\n\n") : printf("NO\n\n");
            else
                printf("NO\n\n");
        }
        else if(strcmp("CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT", buffer)==0){
            canWinWithNaiveController(board);
            init_state(&board);
        }
        else if(strcmp("CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT", buffer)==0){
            canWinWithPerfectController(board);
            init_state(&board);
        }
    }
    return 0;
}