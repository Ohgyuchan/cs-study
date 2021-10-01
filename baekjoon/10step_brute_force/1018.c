#include <stdio.h>
#include <stdlib.h>

char board[51][51];

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

int min(int a, int b, int c) {
    int min;
    min = a <= b ? a : b;
    min = min <= c ? min : c;
    return min;
}

// int check(int x,int y)
// {
// 	int cnt1 = 0;
// 	int cnt2 = 0;

// 	for (int i = x; i < x + 8; i++) {
// 		for (int j = y; j < y + 8; j++) {
// 			if ((i + j) % 2 == board[i][j]) cnt1++; // 탐색을 시작하는 첫번째 블록이 흰색 일때
// 			if ((i + j + 1) % 2 == board[i][j]) cnt2++; // 탐색을 시작하는 첫번째 블록이 검정색 일때
// 		}
// 	}

// 	return min(cnt1, cnt2); // 둘 중 최소값 반환
// }

int main() {
    int M, N;
    int count = 32;

    scanf("%d %d", &M, &N);
    
    for(int i = 0; i < M; i++) {
        scanf("%s", board[i]);
    }

    for (int i = 0; i <= M-8; i++)
		for (int j = 0; j <= N-8; j++)
            count = min(count, blackFirstChange(i, j), whiteFirstChange(i, j));
    
    printf("%d", count);

    return 0;
}