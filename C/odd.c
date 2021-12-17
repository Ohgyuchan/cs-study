#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ROW 5
int data[ROW][10];

int main() {
    srand(time(NULL));

    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < 10; j++)
            data[i][j] = rand() % 99 + 1;
    }

    printf("============== data ===============\n");
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%02d ", data[i][j]);
        }
        printf("\n");
    }
    
    int count = 0;
    
    printf("============== odd list ===============\n");
    for(int i = ROW-1; i >= 0; i--) {
        for(int j = 10-1; j >= 0; j--) {
            if(data[i][j] % 2 != 0) {
                count++;
                printf("%d %d:%02d\t", i, j, data[i][j]);
            }
            if(count == 5){
                count = 0;
                printf("\n");
            }
        }
    }

    return 0;
}