#include "CanWin.h"

char whosTurn(BoardState board){
    if(board.red_count==board.blue_count)
        return 'r';
    else
        return 'b';
}

void add_pawn(BoardState* board, char color){
    if(color=='r')
        board->red_count++;
    else
        board->blue_count++;
}

void remove_pawn(BoardState* board, char color){
    if(color=='r')
        board->red_count--;
    else
        board->blue_count--;
}

void add_opponent_pawn(BoardState* board, char color){
    if(color=='r')
        board->blue_count++;
    else
        board->red_count++;
}

void remove_opponent_pawn(BoardState* board, char color){
    if(color=='r')
        board->blue_count--;
    else
        board->red_count--;
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
            return isGameOver(board)==(color=='b'?BLUE_WON:RED_WON) && areFieldsEmpty(board, moves_count);
        else
            return isGameOver(board)==(color=='b'?BLUE_WON:RED_WON) && areFieldsEmpty(board, moves_count-1);
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
                            if(isGameOver(board)==(color=='b'?BLUE_WON:RED_WON)){
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
    } else{
        if(!areFieldsEmpty(board, 1)) return 0;
        else return canWinWithNaive(board, color, 1, 1);
    }
    return 0;
}

int perfectIn4Moves(BoardState board, char color){
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++) {
            if(board.board[i][j]==' ') {
                int canWin = 0;
                board.board[i][j] = ((color=='b')?'r':'b');
                add_opponent_pawn(&board, color);
                for (int k=0; k<board.size; k++) {
                    for (int l=0; l<board.size; l++) {
                        if (board.board[k][l] == ' ') {
                            board.board[k][l] = color;
                            add_pawn(&board, color);
                            if(canWinWithPerfectIn1(board, color)){
                                board.board[k][l] = ' ';
                                remove_pawn(&board, color);
                                canWin = 1;
                                break;
                            }
                            board.board[k][l] = ' ';
                            remove_pawn(&board, color);
                        }
                    }
                    if(canWin)
                        break;
                }
                board.board[i][j] = ' ';
                remove_opponent_pawn(&board, color);
                if(!canWin)
                    return 0;
            }
        }
    }
    return 1;
}

int canWinWithPerfectIn2(BoardState board, char color){
    if(isGameOver(board))
        return 0;
    if(color!=whosTurn(board)){
        if(!areFieldsEmpty(board, 4))
            return 0;
        else
            return perfectIn4Moves(board, color);
    }
    else {
        if(!areFieldsEmpty(board, 3))
            return 0;
        for(int i=0; i<board.size; i++){
            for(int j=0; j<board.size; j++){
                if(board.board[i][j]==' '){
                    board.board[i][j] = color;
                    add_pawn(&board, color);
                    if(canWinWithPerfectIn1(board, color)){
                        board.board[i][j] = ' ';
                        remove_pawn(&board, color);
                        return 1;
                    }
                    board.board[i][j] = ' ';
                    remove_pawn(&board, color);
                }
            }
        }
        return 0;
    }
}