#include "CanWin.h"

char whosTurn(BoardState board){
    if(board.red_count==board.blue_count)
        return 'r';
    else
        return 'b';
}

int areFieldsEmpty(BoardState board, int pawn_count){
    int filled=0;
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            if(filled==pawn_count)
                return 1;
            if(board.board[i][j]==' ')
                filled++;
        }
    }
    if(filled==pawn_count)
        return 1;
    return 0;
}

int canWinWithNaive(BoardState board, char color, int moves_left, int moves_count){
    if(moves_left==0){
        if(color!=whosTurn(board))
            return isGameOver(board)==(color=='b'?1:2) && areFieldsEmpty(board, moves_count);
        else
            return isGameOver(board)==(color=='b'?1:2) && areFieldsEmpty(board, moves_count-1);
    }
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            if(board.board[i][j]==' ' && !isGameOver(board)){
                board.board[i][j] = color;
                if(canWinWithNaive(board, color, moves_left-1, moves_count)) {
                    board.board[i][j] = ' ';
                    return 1;
                }

                board.board[i][j] = ' ';
            }
        }
    }
    return 0;
}