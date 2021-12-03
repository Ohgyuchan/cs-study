#include "sort.h"
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리

#define MAX 100000

int main() {
    clock_t start, end;
    int arr[MAX];
    srand(time(NULL)); // 매번 다른 시드값 생성
    
    for(int i = 0; i < MAX; i++)
        arr[i] = rand() % MAX + 1;

    start = clock();
    selection_sort(arr, MAX);
    end = clock();

    print_arr(arr, MAX);
    printf("\n======= EXECUTION TIME =======\n");
    printf("%.1f s", (float)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}