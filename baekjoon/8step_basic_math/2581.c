#include <stdio.h>
#include <math.h>
/*
 * 소수 찾기
 * 소수(Prime Number): 1과 자기 자신으로만 나누어 떨어지는 수.
 * Solution: 자신의 2부터 자신의 제곱근까지 나눠보면 된다.
 */
int is_prime_number(int num) {
  if(num <= 1)
    return 0;
  
  else if(num % 2 == 0) {
    if(num == 2)
      return 1;
    return 0;
  }
  
  for(int i = 3; i <= sqrt(num); i++) {
    if(num % i == 0)
      return 0;
  }
  return 1;
}
int main() {
  int N, M, min, sum = 0;

  scanf("%d", &M);
  scanf("%d", &N);

  min = N;

  for(int i = M; i <= N; i++) {
    if(is_prime_number(i)) {
      sum += i;
      if(min > i)
        min = i;
    }
  }
  if(!sum) {
    printf("-1");
    return 0;
  }
  printf("%d\n%d\n", sum, min);
  return 0;
}
