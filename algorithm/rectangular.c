#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 직사각형을 만드는 데 필요한 4개의 점 중 3개의 좌표가 주어질 때, 나머지 한점의 좌표를 구하는 알고리즘.
// v_row_len은 2차원 배열 v의 행(세로) 길이입니다.
// v_col_len은 2차원 배열 v의 열(가로) 길이입니다.
// v[i][j]는 v의 i번째 행의 j번째 열에 저장된 값을 의미합니다.
int* solution(int **v, size_t v_row_len, size_t v_col_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int row = 0, col = 0;
    int* answer = (int*)malloc(2);
    
    for(int i = 0 ; i < 2 ; i++) {
        if(v[0][i] != v[1][i]) {
            if(v[0][i] != v[2][i])
                answer[i] = v[0][i];
            else
                answer[i] = v[1][i];
        }
        else {
            answer[i] = v[2][i];
        }
    }
    
    return answer;
}
