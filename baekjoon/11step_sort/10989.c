#include <stdio.h>
/*
첫째 줄에 수의 개수 N(1 ≤ N ≤ 10,000,000)이 주어진다.
둘째 줄부터 N개의 줄에는 수가 주어진다. 이 수는 10,000보다 작거나 같은 자연수이다.
10,000보다 작거나 같은 자연수들의 정렬이므로 counting sort를 이용.
각 수가 몇 개인지 배열을 이용하여 count하고 출력.
*/
#define SIZE 10001
int count[SIZE] = {0, }; // 각 수를 세기 위한 배열

int main() {
    int N = 0;
    int num = 0;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &num);
        count[num]++; // 입력된 수의 갯수
    }

    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < count[i]; j++) {
            printf("%d\n", i);
        }
    }

    return 0;
}