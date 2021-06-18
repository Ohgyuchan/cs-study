#include <stdio.h>
#include <math.h>

#define SIZE 1000001

int num[SIZE] = { 0, };

int main() {
  int M, N;
  scanf("%d %d", &M, &N);

  for(int i = 2; i <= N; i++) {
    if(!num[i])
      for(int j = i + i; j <= N; j += i)
        num[j] = 1;
    if(i >= M && num[i] == 0)
      printf("%d\n", i);
  }
    
  return 0;
}
