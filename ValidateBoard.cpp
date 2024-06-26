#include "ValidateBoard.h"

int remove_pawn(BoardState board, Field field, char color){
    char copy[MAX_SIZE][MAX_SIZE];
    for(int i=0; i<board.size; i++) {
        for (int j = 0; j < board.size; j++)
            copy[i][j] = board.board[i][j];
    }
    board.board[field.y][field.x] = ' ';

    int result = isGameOver(board), returned=0;
    if(result==BLUE_WON && color=='b')
        returned = 1;
    else if(result==RED_WON && color=='r')
        returned = 2;

    for(int i=0; i<board.size; i++) {
        for (int j = 0; j < board.size; j++)
            board.board[i][j] = copy[i][j];
    }

    return returned;
}

Field find_pawn(BoardState board, char color, int index){
    int count=0;
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            if(board.board[i][j]==color){
                if(count==index){
                    Field field = {i, j};
                    return field;
                }
                count++;
            }
        }
    }
    Field field = {-1, -1};
    return field;
}

int isBoardPossible(BoardState board){
    int result = isGameOver(board);
    if(result==1 && board.blue_count==board.red_count){
        for(int i=0; i<board.blue_count; i++){
            Field field = find_pawn(board, 'b', i);
            if(field.x!=-1 && field.y!=-1 && remove_pawn(board, field, 'b')==0)
                return 1;
        }
    }
    else if(result==2 && board.blue_count==board.red_count-1){
        for(int i=0; i<board.red_count; i++){
            Field field = find_pawn(board, 'r', i);
            if(field.x!=-1 && field.y!=-1 && remove_pawn(board, field, 'r')==0)
                return 1;
        }
    }
    else if(result!=0)
        return 0;
    else
        return 1;
    return 0;
}

int isBoardCorrect(BoardState board){
    return board.blue_count==board.red_count || board.blue_count==board.red_count-1;
}