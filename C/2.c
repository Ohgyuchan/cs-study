#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transMatrix(int **mat, int row) {
    printf("===================================\n");
    
    if(row >= 5) {
        printf("배열을 변환할 필요가 없습니다.\n");
    } else {
        int **result;
        result = (int**) malloc ( sizeof(int*) * 5);
        
        for(int i = 0; i < 5; i++){
            result[i] = (int*) malloc ( sizeof(int) * row);
        }

        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < row; j++)
                result[i][j] = mat[j][i];
        }

        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < row; j++) {
                printf("%d\t", result[i][j]);
            }
            printf("\n");
        }
    }
}

int main() {
    int row;
    int col = 5;
    srand(time(NULL));
    
    printf("행의 크기 입력:");
    scanf("%d", &row);

    int **mat;
    mat = (int**) malloc ( sizeof(int*) * row);
    for(int i = 0; i < row; i++){
        mat[i] = (int*) malloc ( sizeof(int) * col);
    }

    printf("배열 반환 결과 출력.\n");
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mat[i][j] = rand() % 11;
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    transMatrix(mat, row);

    return 0;
}