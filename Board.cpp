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
    return (count-1)/3 + 1;
}

void init_state(BoardState* board){
    board->size = 0;
    board->blue_count = 0;
    board->red_count = 0;

    for(int i=0; i<MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++)
            board->board[i][j] = '\0';
    }
}