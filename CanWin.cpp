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
    else if(isGameOver(board)){
        return 0;
    }
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            if(board.board[i][j]==' '){
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

int canWinWithPerfectIn1(BoardState board, char color){
    if(isGameOver(board))
        return 0;
    if(color!=whosTurn(board)){
        if(!areFieldsEmpty(board, 2))
            return 0;
        else{
            if(canWinWithNaive(board, color=='b'?'r':'b', 1, 1))
                return 0;
            else{
                int wins=0;
                for(int i=0; i<board.size; i++){
                    for(int j=0; j<board.size; j++){
                        if(board.board[i][j]==' '){
                            board.board[i][j] = color;
                            if(isGameOver(board)==(color=='b'?1:2)){
                                wins++;
                                if(wins==2) {
                                    board.board[i][j] = ' ';
                                    return 1;
                                }
                            }
                            board.board[i][j] = ' ';
                        }
                    }
                }
            }
        }
    }
    else{
        if(!areFieldsEmpty(board, 1))
            return 0;
        else
            return canWinWithNaive(board, color, 1, 1);
    }
    return 0;
}

int canWinWithPerfectIn2(BoardState board, char color){
    if(isGameOver(board))
        return 0;
    if(color!=whosTurn(board)){
        if(!areFieldsEmpty(board, 4))
            return 0;
        else{
            for(int i=0; i<board.size; i++){
                for(int j=0; j<board.size; j++) {
                    if(board.board[i][j]==' ') {
                        int canWin = 0;
                        board.board[i][j] = ((color=='b')?'r':'b');
                        (color=='b') ? board.red_count++ : board.blue_count++;
                        for (int k=0; k<board.size; k++) {
                            for (int l=0; l<board.size; l++) {
                                if (board.board[k][l] == ' ') {
                                    board.board[k][l] = color;
                                    (color == 'b') ? board.blue_count++ : board.red_count++;
                                    if(canWinWithPerfectIn1(board, color)){
                                        canWin = 1;
                                    }
                                    board.board[k][l] = ' ';
                                    (color == 'b') ? board.blue_count-- : board.red_count--;
                                }
                            }
                        }
                        board.board[i][j] = ' ';
                        (color == 'b') ? board.red_count-- : board.blue_count--;
                        if(!canWin)
                            return 0;
                    }
                }
            }
            return 1;
        }
    }
    else {
        if(!areFieldsEmpty(board, 3))
            return 0;
        for(int i=0; i<board.size; i++){
            for(int j=0; j<board.size; j++){
                if(board.board[i][j]==' '){
                    board.board[i][j] = color;
                    (color=='b') ? board.blue_count++ : board.red_count++;
                    if(canWinWithPerfectIn1(board, color)){
                        board.board[i][j] = ' ';
                        (color=='b') ? board.blue_count-- : board.red_count--;
                        return 1;
                    }
                    board.board[i][j] = ' ';
                    (color=='b') ? board.blue_count-- : board.red_count--;
                }
            }
        }
        return 0;
    }
}