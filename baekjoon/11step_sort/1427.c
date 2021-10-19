#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    char N[11];

    scanf("%s", N);

    for(int i = 0; i < strlen(N); i++) {
        for(int j = i; j < strlen(N); j++) {
            if(N[i] < N[j]) {
                swap(&N[i], &N[j]);
            }
        }
    }

    printf("%s", N);

    return 0;
}