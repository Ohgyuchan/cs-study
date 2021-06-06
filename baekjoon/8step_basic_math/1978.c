#include <stdio.h>
#include <math.h>
/*
 * 소수 찾기
 * 소수(Prime Number): 1과 자기 자신으로만 나누어 떨어지는 수.
 */
int main() {
  int N, pnum;
  
  scanf("%d", &N);

  int count = N;
  
  for(int i; i < N; i++) {
    scanf("%d", &pnum);
    if(pnum == 1) {
      count--;
      continue;
    }

    int sq_root = sqrt(pnum) + 1;
    for(int i = 2; i < sq_root; i++) {
      if(pnum % i == 0)
        count--;
    }
  }
  printf("%d\n", count);
  return 0;
}
