#include <stdio.h>

int main() {
  /*
   * N: 찾을 분수의 번호
   * count: 대각선 내 분수 번호의 최대값
   * sum: 대각선에 위치한 분수, 분모의 합
   * parent: 분모
   * child: 분자
   */
  int N, count = 0, sum = 1;
  int child = 1, parent = 1;
  scanf("%d", &N);

  if(N == 1) {
    printf("1/1\n");
    return 0;
  }

  while(1) {
    count += sum;
    sum++;
    if(N <= count)
      break;
  }

  if(sum % 2 == 0)
    parent = sum - 1;
  else
    child = sum - 1;
  
  while(1) {
    if(N == count)
      break;
    if(sum % 2 == 0) {
      parent--;
      child++;
    }
    else {
      child--;
      parent++;
    }
    count--;
  }
  printf("%d/%d\n", child, parent);
  return 0;
}
