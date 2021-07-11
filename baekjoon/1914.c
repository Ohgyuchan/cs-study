#include <stdio.h>
#include <math.h>

char K[31];

void hanoi(int n, int start, int middle, int end) 
{
    if (n == 1)
    {
        printf("%d %d\n", start, end);
        return;
    }
    hanoi(n - 1, start, end, middle);
    hanoi(1, start, middle, end);
    hanoi(n - 1, middle, start, end);
}

void print_hanoi_count(int n) {
    int temp = 0;
    int last = 0;
    int count = 0;
    K[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= last; j++) {
            temp = K[j] * 2;
            if (temp >= 10) {
                K[j] = temp % 10 + count;
                count = temp / 10;
                if (j == last) {
                    K[++last] = count;
                    count = 0;
                    break;
                }
            }
            else {
                K[j] = temp + count;
                count = 0;
            }
        }
    }
    K[0] -= 1;
    for (int i = last; i >= 0; i--) {
        printf("%d", K[i]);
    }
    printf("\n");
}

int main() {
    int N;

    scanf("%d", &N);

    print_hanoi_count(N);

    printf("%s\n", K);
    
    if(N <= 20)
        hanoi(N, 1, 2, 3);

    return 0;
}