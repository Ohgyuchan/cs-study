#include <stdio.h>

int sugar(int n) {
  int result;
  if(n < 5 && n % 3)
    return -1;
  else if(n % 3 == 0)
    return n / 3;
  else if(n % 5 == 0)
    return n / 5;

  result = n / 5;
  n = n - (result * 5);
  
  if(result % 3 != 0)
    return -1;
  
  result += n / 3;
  
  return result;
}

int main() {
  
  int N;
  scanf("%d", &N);
  
  printf("%d\n", sugar(N));
  
  return 0;

}
