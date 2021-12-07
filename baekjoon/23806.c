#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N*5; j++) {
            printf("@");
        }
        printf("\n");
    }

    for(int i = 0; i < N*3; i++) {
        for(int j = 0; j < N*5; j++) {
            if(j < N || j > N*5 - N-1) printf("@");
            else printf(" ");
        }
        printf("\n");
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N*5; j++) {
            printf("@");
        }
        if(i!=N) printf("\n");
    }
    return 0;
}