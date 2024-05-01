#include "IsGameOver.h"

int dfs(char color, int isVisited[MAX_SIZE][MAX_SIZE], BoardState board, int y, int x){
    int dx[ADJACENT_FIELDS] = {-1, 1, 0, 0, -1, 1};
    int dy[ADJACENT_FIELDS] = {0, 0, -1, 1, -1, 1};

    isVisited[y][x] = 1;
    if(color=='b' && y==board.size-1)
        return BLUE_WON;
    else if(color=='r' && x==board.size-1)
        return RED_WON;
    for(int i=0; i<ADJACENT_FIELDS; i++){
        int newX = x+dx[i];
        int newY = y+dy[i];
        if(newX>=0 && newX<board.size && newY>=0 && newY<board.size && board.board[newY][newX]==color && !isVisited[newY][newX]){
            int result = dfs(color, isVisited, board, newY, newX);
            if(result!=NO_WINNER)
                return result;
        }
    }
    return 0;
}

int isGameOver(BoardState board){
    int isVisited[MAX_SIZE][MAX_SIZE];
    int result=NO_WINNER;
    for(int i=0; i<board.size; i++){
        for(int j=0; j<board.size; j++) {
            for (int k = 0; k < board.size; k++)
                isVisited[j][k] = 0;
        }
        if(board.board[0][i]=='b' && dfs('b', isVisited, board, 0, i)==1) {
            result = BLUE_WON;
            break;
        }
        else if(board.board[i][0]=='r' && dfs('r', isVisited, board, i, 0)==2) {
            result = RED_WON;
            break;
        }
    }

    return result;
}