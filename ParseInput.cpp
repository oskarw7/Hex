#include "ParseInput.h"

int isFirstLine(const char* line){
    int i=0;
    if(line[0]=='\n')
        return 0;
    while(line[i]!='\0' && line[i]!='\n'){
        if(line[i]!=' ' && line[i]!='-')
            return 0;
        i++;
    }
    return 1;
}

void fill_diagonal(BoardState* board, const char* diagonal){
    int diag_size = strlen(diagonal);
    if(board->board[diag_size-1][0]=='\0'){
        int j=0;
        for(int i=diag_size-1; i>=0; i--){
            board->board[i][j] = diagonal[j];
            j++;
        }
    }
    else{
        int sum = 2*(board->size-1) - (diag_size-1), i = board->size-1, j = sum-i;
        for(int k=0; k<diag_size; k++){
            board->board[i][j] = diagonal[k];
            i--;
            j++;
        }
    }
}

void get_line(BoardState* board, char* buffer){
    char c, token=' ';
    char diagonal[MAX_SIZE+1] = {'\0'};
    int i=0, index=0;

    while((c=getchar())!='\n' && c!=EOF){
        buffer[i] = c;
        if(c=='r') {
            board->red_count++;
            token = 'r';
        }
        else if(c=='b') {
            board->blue_count++;
            token = 'b';
        }
        else if(c=='>'){
            diagonal[index] = token;
            index++;
            token = ' ';
        }
        i++;
    }
    if(strcmp(diagonal, "")!=0)
        fill_diagonal(board, diagonal);
    if(c==EOF){
        memset(buffer, '\0', strlen(buffer));
        buffer[i] = 'X';
        i++;
    }
    else if(i==0 && c=='\n') {
        buffer[i] = '\n';
        i++;
        init_state(board);
    }
    buffer[i] = '\0';
}
