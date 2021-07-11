#include <stdio.h>
/*
N의 분해합이란?
N과 N을 이루는 각 자리수의 합을 의미한다.
ex: N: 123, N의 분해합: 123 + 1 + 2 + 3 = 129
M의 분해합이 N인 경우, M을 N의 생성자라 하낟.
123은 129의 생성자!
어떤 자연수의 경우에는 생성자가 없을 수도 있고, 어떤 자연수는 생성자가 여러 개일 수도 있다.

TODO:
N이 주어졌을 때, N의 가장 작은 생성자를 구해내는 프로그램
생성자가 없을 시: 0 출력


123 => 1 + 2 + 3 + 123 = 129
123 => 1 + 2 + 4 + 124 = 131
*/
#include <stdio.h>

int main() {
    int N;
    
    scanf("%d", &N);
    
    for (int i = 1; i < N; i++) {
        int temp = i;
        int contructor = i;
        
        while(temp > 0) {
            contructor += temp % 10;
            temp /= 10;
        }
        
        if (contructor == N) {
            printf("%d", i);
            N = 0;
            break;
        }
    }
    
    if (N != 0)
        printf("0");

    return 0;
}