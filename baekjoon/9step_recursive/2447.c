#include <stdio.h>
#include <math.h>
 
char star[2500][2500];
 
//모든 칸을 *로 채워주기
void arrange_star(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            star[i][j] = '*';
    }
}
 
//지정된 점(x,y)부터 가로새로로 3^count만큼 공백으로 채우기
void insert_blank_to_star(int x, int y, int count) {
    for (int i = x; i < x + (int)pow(3, count); i++) {
        for (int j = y; j < y + (int)pow(3, count); j++) {
            star[i][j] = ' ';
        }
    }
}
 
//공백으로 지정할 점(x,y) 찾기
void find_blank(int n, int count) {
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                //해당 기준점을 공백으로
                insert_blank_to_star((int)pow(3, count) + i * (int)pow(3, count + 1), 
                    (int)pow(3, count) + j * (int)pow(3, count + 1), count);
            }
        }
        //기준점 이동하기
        find_blank(n / 3, count + 1);
    }
}
 
int main() {
    int N;
    scanf("%d", &N);
    arrange_star(N);
 
    find_blank(N / 3, 0);
 
    //결과출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c", star[i][j]);
        printf("\n");
    }
    return 0;
}