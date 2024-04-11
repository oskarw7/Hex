#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 66 // liczba znaków w środkowej linii w planszy 11x11
#define MAX_SIZE 11 // maksymalny rozmiar planszy
#define ADJACENT_FIELDS 6

typedef struct BoardState{
    char** board;
    unsigned int size;
    unsigned int blue_count;
    unsigned int red_count;
} BoardState;

//temp
void print_board(BoardState board){
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            printf("%c", board.board[i][j]);
        }
        printf("\n");
    }
}

void init_state(BoardState* board){
    board->size = 0;
    board->blue_count = 0;
    board->red_count = 0;
}

int dfs(char color, int** isVisited, BoardState board, int y, int x){
    int dx[ADJACENT_FIELDS] = {-1, 1, 0, 0, -1, 1};
    int dy[ADJACENT_FIELDS] = {0, 0, -1, 1, -1, 1};

    isVisited[y][x] = 1;
    if(color=='b' && y==board.size-1)
        return 1;
    else if(color=='r' && x==board.size-1)
        return 2;
    for(int i=0; i<ADJACENT_FIELDS; i++){
        int newX = x+dx[i];
        int newY = y+dy[i];
        if(newX>=0 && newX<board.size && newY>=0 && newY<board.size && board.board[newY][newX]==color && !isVisited[newY][newX]){
            int result = dfs(color, isVisited, board, newY, newX);
            if(result!=0)
                return result;
        }
    }
    return 0;
}

int isGameOver(BoardState board){
    int** isVisited = (int**)malloc(board.size*sizeof(int*));
    int result=0;
    for(int i=0; i<board.size; i++)
        isVisited[i] = (int*)malloc(board.size*sizeof(int));

    for(int i=0; i<board.size; i++){
        for(int k=0; k<board.size; k++)
            for(int j=0; j<board.size; j++)
                isVisited[k][j] = 0;
        if(board.board[0][i]=='b' && dfs('b', isVisited, board, 0, i)==1) {
            result = 1;
            break;
        }
        else if(board.board[i][0]=='r' && dfs('r', isVisited, board, i, 0)==2) {
            result = 2;
            break;
        }
    }

    for(int i=0; i<board.size; i++)
        free(isVisited[i]);
    free(isVisited);

    return result;
}

int isBoardCorrect(BoardState board){
    return board.blue_count==board.red_count || board.blue_count==board.red_count-1;
}

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
    char diagonal[MAX_SIZE] = {'\0'};
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
        for(int j=0; j<board->size; j++)
            free(board->board[j]);
        free(board->board);
        init_state(board);
    }
    buffer[i] = '\0';
}

int main() {
    BoardState board;
    init_state(&board);
    char buffer[MAX_LINE] = {'\0'};
    while(strcmp(buffer, "X")!=0){
        get_line(&board, buffer);
        if(board.size==0 && isFirstLine(buffer)){
            board.size = (count_spaces(buffer)-1)/3 + 1;
            board.board = (char**)malloc(board.size*sizeof(char*));
            for(int i=0; i<board.size; i++)
                board.board[i] = (char*)malloc(board.size*sizeof(char));
            for(int i=0; i<board.size; i++)
                for(int j=0; j<board.size; j++)
                    board.board[i][j] = '\0';
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
            if(isBoardCorrect(board)){
                int result = isGameOver(board);
                if (result == 1)
                    printf("YES BLUE\n");
                else if (result == 2)
                    printf("YES RED\n");
                else
                    printf("NO\n");
            } else
                printf("NO\n");
        }
        else if(strcmp("IS_BOARD_POSSIBLE", buffer)==0){
            if(isBoardCorrect(board)){
                
            } else
                printf("NO\n");
        }
    }
    return 0;
}