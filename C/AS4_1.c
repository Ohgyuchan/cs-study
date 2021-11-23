#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Matrixoper(int mat1[4][5], int mat2[4][5], char op) {
    printf("================= RESULT =================\n");
    if(op == '-') {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 5; j++)
                printf("%d\t", mat1[i][j] - mat2[i][j]);
            printf("\n");
        }

    } else if(op == '+') {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 5; j++)
                printf("%d\t", mat1[i][j] + mat2[i][j]);
            printf("\n");
        }
    }
    
}

void Print_matrix(int mat1[4][5], int mat2[4][5]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%d\t", mat1[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < 5; j++) {
            printf("%d\t", mat2[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat1[4][5];
    int mat2[4][5];
    char op;
    srand(time(NULL));
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            // a ~ b까지의 난수 생성
            // rand() % (b+1-a) + a;
            mat1[i][j] = rand() % 10 + 1;
            mat2[i][j] = rand() % 10 + 21;
        }
    }
    
    printf("input operator:");
    scanf("%c", &op);

    Print_matrix(mat1, mat2);
    Matrixoper(mat1, mat2, op);

    return 0;
}