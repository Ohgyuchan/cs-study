#include <stdio.h>
#include <math.h>
#define SIZE 10001

int num[SIZE] = { 0, };

int main() {
  int T, N;
/*
  for(int i = 2; i <= sqrt(SIZE); i++)
    for(int j = i * i; j <= SIZE; j += i)
      if(num[j] % i == 0)  
        num[j] = 1;
*/
  scanf("%d", &T);

  for(int i = 0; i < T; i++) {
    scanf("%d", &N);

    for(int i = 2; i < sqrt(N); i++)
      for(int j = i * i; j <= N; j += i)
        if(num[j] % i == 0)
          num[j] = 1;

    for(int j = N/2; j > 0; j--)
      if(num[j] == 0 && num[N-j] == 0) {
        printf("%d %d\n", j, N-j);
        break;
      }
  }

  return 0;
}
