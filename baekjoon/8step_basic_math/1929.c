#include <stdio.h>
#include <math.h>

int main() {
  int M, N;
  scanf("%d %d", &M, &N);

  for(int i = M; i <= sqrt(N); i++) {
    while(N % i == 0) {
      printf("%d\n", i);
      N /= i;
    }
  }

  if(N != 0)
    printf("%d\n", N);

  return 0;
}
