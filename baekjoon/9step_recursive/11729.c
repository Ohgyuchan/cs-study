#include <stdio.h>
#include <math.h>

void hanoi(int n, int from, int mid, int to) {
    if(n == 1)
        printf("%d %d\n", from, to);
    else {
        hanoi(n - 1, from, to, mid);
        printf("%d %d\n", from, to);
        hanoi(n - 1, mid, from, to);
    }
}

int main() {
    int N;

    scanf("%d", &N);

    printf("%d\n", (int)pow(2, N) - 1);

    hanoi(N, 1, 2, 3);

    return 0;
}