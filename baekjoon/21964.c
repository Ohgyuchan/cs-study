#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    char *str;
    scanf("%d", &N);
    str = malloc(sizeof(char) * N);

    scanf("%s", str);

    for(int i = N - 5; i < N; i++)
        printf("%c", str[i]);

    free(str);
    return 0;
}