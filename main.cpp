#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 66 // liczba znaków w środkowej linii w planszy 11x11
#define MAX_SIZE 11 // maksymalny rozmiar planszy
#define ADJACENT_FIELDS 6

typedef struct BoardState{
    char** board;
    int size;
    int blue_count;
    int red_count;
} BoardState;

typedef struct Field{
    int y;
    int x;
} Field;

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

int remove_pawn(BoardState board, Field field, char color){
    char** copy = (char**)malloc(board.size*sizeof(char*));
    for(int i=0; i<board.size; i++)
        copy[i] = (char*)malloc(board.size*sizeof(char));
    for(int i=0; i<board.size; i++) {
        for (int j = 0; j < board.size; j++)
            copy[i][j] = board.board[i][j];
    }
    copy[field.y][field.x] = ' ';
    BoardState board_copy = {copy, board.size, board.blue_count, board.red_count};

    int result = isGameOver(board_copy), returned=0;
    if(result==1 && color=='b')
        returned = 1;
    else if(result==2 && color=='r')
        returned = 2;

    for(int i=0; i<board.size; i++)
        free(copy[i]);
    free(copy);

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

/*
R w 2, kolej R - 1 B
R w 2, kolej B - 2 B
B w 2, kolej R - 2 R
B w 2, kolej B - 1 R

R w 1, kolej R - 0 B
R w 1, kolej B - 1 B
B w 1, kolej R - 1 R
B w 1, kolej B - 0 R
*/

char whosTurn(BoardState board){
    if(board.red_count==board.blue_count)
        return 'r';
    else
        return 'b';
}

int areFieldsEmpty(BoardState board, int pawn_count){ //plansza na wejsciu nie moze byc zresetowana
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

int generate_move(BoardState board, char color, int moves_left, int moves_count){
    if(moves_left==0){
        if(color!=whosTurn(board))
            return isGameOver(board)==(color=='b'?1:2) && areFieldsEmpty(board, moves_count);
        else
            return isGameOver(board)==(color=='b'?1:2) && areFieldsEmpty(board, moves_count-1);
    }
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++){
            if(board.board[i][j]==' ' && !isGameOver(board)){ //+isGameOver
                board.board[i][j] = color;
                if(generate_move(board, color, moves_left-1, moves_count)) {
                    board.board[i][j] = ' ';
                    return 1;
                }

                board.board[i][j] = ' ';
            }
        }
    }
    return 0;
}

int canWin(BoardState board, char color, int moves_count){
    if(generate_move(board, color, moves_count, moves_count)){
        return 1;
        /*
        if(color!=whosTurn(board))
            return areFieldsEmpty(board, moves_count);
        else
            return areFieldsEmpty(board, moves_count-1); */
    }

    return 0;
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
                if(isBoardPossible(board))
                    printf("YES\n\n");
                else
                    printf("NO\n\n");
            } else
                printf("NO\n\n");
        }
        else if(strcmp("CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT", buffer)==0){
            if(isBoardCorrect(board)){
                canWin(board, 'r', 1) ? printf("YES\n") : printf("NO\n");
                canWin(board, 'b', 1) ? printf("YES\n") : printf("NO\n");
                canWin(board, 'r', 2) ? printf("YES\n") : printf("NO\n");
                canWin(board, 'b', 2) ? printf("YES\n\n") : printf("NO\n\n");
            } else
                printf("NO\nNO\nNO\nNO\n\n");
        }
        else if(strcmp("CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT", buffer)==0){
            for(int i=0; i<board.size; i++)
                free(board.board[i]);
            free(board.board);
            init_state(&board);
        }

    }
    return 0;
}