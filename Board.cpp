#include "Board.h"

int count_size(const char* line){
    int i=0, count=0;
    if(line[0]!=' ')
        return 0;
    while(line[i]!='-'){
        if(line[i]==' ')
            count++;
        i++;
    }
    return count;
}

void init_state(BoardState* board){
    board->size = 0;
    board->blue_count = 0;
    board->red_count = 0;
}

void init_board(BoardState* board, const char* buffer){
    board->size = (count_size(buffer)-1)/3 + 1;
    board->board = (char**)malloc(board->size*sizeof(char*));

    for(int i=0; i<board->size; i++)
        board->board[i] = (char*)malloc(board->size*sizeof(char));

    for(int i=0; i<board->size; i++) {
        for (int j = 0; j < board->size; j++)
            board->board[i][j] = '\0';
    }
}