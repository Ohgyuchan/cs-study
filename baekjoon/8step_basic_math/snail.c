#include <stdio.h>

int main() {
  int A, B, V;
  int day_count = 0, height = 0;

  scanf("%d %d %d", &A, &B, &V);
/*
  while(1) {

    height += A;

    if(V <= height)
      break;
    
    height -= B;
    day_count++;
  }
  day_count++;
  */

  /*
   * 정상에 도달하는 순간에는 미끄러지지 않기 때문에
   * V - B까지 올라가는 것과 결과가 같고, A만큼 올라가도 B만큼 떨어지기에
   * 하루에 A - B만큼 올라간다고 할 수있다.
   * day_count = (V - B) / (A - B)인셈인데
   * 여기서 V -  B가 A - B로 나눠 떨어지지 않으면 하루를 더 가야 되는 것을 의미하므로
   * +1을 해줘야 하는데 이를 코드로 표현하면
   *
   if( (V - B) % (A - B))
    day_count = (V - B) / (A - B) + 1;
   
   else
    day_count = (V - B) / (A - B);
   *
   * 이것은 V - B에서 1을 미리 빼주어 모든 경우를 나누어떨어지지 않게 만든 다음
   * 몫에 +1을 해주는 것과 같다.
   *
   * 즉,
   * day_count = (V - B - 1) / ( A - B ) + 1;
   * 
   * ex)
   * 5 / 5 = 1인 경우 4 / 5 = 0
   * 6 / 5 = 1인 경우 5 / 5 = 1
   * 7 / 5 = 1인 경우 6 / 5 = 1
   * 300 / 100 = 3인 경우 299 / 100 = 2
   * 
   * 모든 경우에 1을 더해주면 된다.
   *
   */
  day_count = (V - B - 1) / (A - B) + 1;

  printf("%d\n", day_count);

  return 0;
}
