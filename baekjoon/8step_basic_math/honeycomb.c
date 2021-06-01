#include <stdio.h>
#include <stdlib.h>
/*
 * 육각형으로 이루어진 벌집이 있다.
 * 정중앙의 방(1)부터 시작해서 이웃하는 방에 돌아가면서 1씩 증가하며 주소를 매긴다.
 * 숫자 N이 주어졌을 때, 벌집의 중앙 1에서 N번방까지 최소 개수의 방을 지나서 갈 때
 * 몇개의 방을 지나가는지(시작과 끝을 포함하여)를 계사하는 프로그램
 * EX) 13 -> 3, 58 -> 5
 */

int main() {
  // N: 끝방번호, count: N번방까지의 최소 개수(벌집겹), range: 같은 벌집겹을 가진 방범위
  int N, count = 1, range = 1;
  scanf("%d", &N);
  
  while(1) {
    // N까지의 최소한의 방의 개수:
    // 1: 1개, 2~7: 2개, 8~19: 3개, 20~38: 4개while
    range += (count-1) * 6;
    
    if(N <= range) {
      break;
    }

    count++;

  }
  
  printf("%d\n", count);

  return 0;
}
