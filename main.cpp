#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 66 // środkowa linia w planszy 11x11

typedef struct BoardState{
    char** board;
    unsigned int size;
    unsigned int blue_count;
    unsigned int red_count;
} BoardState;

void init_state(BoardState* board){
    board->size = 0;
    board->blue_count = 0;
    board->red_count = 0;
}

int isBoardCorrect(BoardState board){
    return board.blue_count==board.red_count || board.blue_count==board.red_count-1;
}

int isFirstLine(const char* line){
    int i=0;
    while(line[i]!='\0' && line[i]!='\n'){
        if(line[i]!=' ' && line[i]!='-')
            return 0;
        i++;
    }
    return 1;
}

int count_spaces(const char* line){
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

void fill_diagonal(BoardState* board, const char* diagonal){
    int diag_size = strlen(diagonal);
    if(board->board[diag_size-1][0]=='\0'){
        int j=0;
        for(int i=diag_size-1; i>=0; i--){
            board->board[i][j] = diagonal[j];
            j++;
        }
    }
}

char* get_line(BoardState* board){
    char buffer[MAX_LINE], c, token=' ';
    char* diagonal = (char*)malloc(board->size*sizeof(char));
    memset(diagonal, '\0', board->size-1);
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
    if(c==EOF)
        return nullptr;
    else if(i==0 && c=='\n') {
        buffer[i] = '\n';
        i++;
        for(int j=0; j<board->size; j++)
            free(board->board[j]);
        free(board->board);
        init_state(board);
    }
    buffer[i] = '\0';
    free(diagonal);

    return buffer;
}

int main() {
    BoardState board;
    init_state(&board);
    char* buffer;
    while((buffer=get_line(&board))!=nullptr){
        if(isFirstLine(buffer)){
            board.size = (count_spaces(buffer)-1)/3 + 1;
            board.board = (char**)malloc(board.size*sizeof(char));
            for(int i=0; i<board.size; i++)
                board.board[i] = (char*)malloc(board.size*sizeof(char));
            for(int i=0; i<board.size; i++)
                memset(board.board[i], '\0', board.size);
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
    }
    return 0;
}
