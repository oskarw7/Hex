#include "IsGameOver.h"

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
        for(int k=0; k<board.size; k++) {
            for (int j = 0; j < board.size; j++)
                isVisited[k][j] = 0;
        }
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