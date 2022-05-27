#include <stdio.h>
#include <stdlib.h>



int main() {
    int *arr1, *arr2;
    int N, M;
    
    scanf("%d", &N);
    
    arr1 = (int*)malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++) {
        scanf("%d", &arr1[i]);
    }

    scanf("%d", &M);
    
    arr2 = (int*)malloc(sizeof(int) * M);
    for(int i = 0; i < M; i++) {
        scanf("%d", &arr2[i]);
    }

    qsort()



    return 0;
}