#include <stdio.h>
#include <stdlib.h>

char board[50][50];

char whiteFirst[8][8] = {
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" }

};

//(0, 0)이 B인 체스보드
char blackFirst[8][8] = {
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" },
    { "BWBWBWBW" },
    { "WBWBWBWB" }
};

int whiteFirstChange(int y, int x) {

    int count = 0;

    for (int i = y; i < y + 8; i++)
        for (int j = x; j < x + 8; j++)
            if (board[i][j] != whiteFirst[i - y][j - x])
                count++;

    return count;
}

//(0, 0)이 B인 체스보드 기준 바뀔 칸 수

int blackFirstChange(int y, int x) {

    int count = 0;

    for (int i = y; i < y + 8; i++)
        for (int j = x; j < x + 8; j++)
            if (board[i][j] != blackFirst[i - y][j - x])
                count++;
                
    return count;

}

int main() {
    int M, N;
    int count = 0;

    scanf("%d %d", &M, &N);

    for(int i = 0; i < M; i++) {
            scanf("%s", board[i]);
    }

    for(int i = 0; i < M-1; i++) {
        for(int j = 0; j < N-1; j++) {
            if(j == 0) {
                if(board[i][j] == board[i-1][j] && board[i][j] == board[i][j+1] && board[i][j] == board[i+1][j]) {
                    if(board[i][j] == 'B')
                        board[i][j] = 'W';
                    else 
                        board[i][j] = 'B';
                    count++;
                }
                if(board[i][j] == board[i+1][j-1]) {
                    if(board[i][j] == 'B')
                        board[i][j] = 'W';
                    else 
                        board[i][j] = 'B';
                    count++;
                }
            } else {
                if(board[i][j] == board[i][j-1] && board[i][j] == board[i-1][j] && board[i][j] == board[i][j+1] && board[i][j] == board[i+1][j]) {
                    if(board[i][j] == 'B')
                        board[i][j] = 'W';
                    else 
                        board[i][j] = 'B';
                    count++;
                }
                if(board[i][j-1] == board[i-1][j] && board[i][j-1] == board[i][j+1] && board[i][j-1] == board[i+1][j]) {
                    if(board[i][j] == 'B')
                        board[i][j] = 'W';
                    else 
                        board[i][j] = 'B';
                    count++;
                }
            }
        }
    }

    printf("\n\n==================\n");

    for(int i = 0; i < M; i++)
        printf("%s\n", board[i]);

    printf("%d\n", count/2);

    return 0;
}