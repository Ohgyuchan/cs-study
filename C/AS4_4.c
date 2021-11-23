#include <stdio.h>

int fibo(int); //함수 원형 선언

int main(void) 
{
  int num; // 개수를 입력받을 변수
  int i; // 반복을 위한 변수
  int temp; // 피보나치 수를 임시로 저장할 변수
  printf("fibonacci number:");
  scanf("%d", &num); //개수 입력
  for (i=1;i<=num; i++)
  {
    temp = fibo(i); //현재 i를 인자로 넣어 함수를 호출해 그 결과를 temp에 저장한다. // 피보나치 수열의 i번째 수를 찾는 것이다.
  }
 printf("%d번째 피보나치 수열의 값은 %d\n", num, fibo(num));
  return 0;
}