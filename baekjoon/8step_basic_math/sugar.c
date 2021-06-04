#include <stdio.h>

int sugar(int n) {
  int result = 0;
  
  while(n > 0) {
    if(n % 5 == 0) {
      n -= 5;
      result++;
    }
    else if(n % 3 == 0) {
      n -= 3;
      result++;
    }
    else if(n > 5) {
      n -= 5;
      result++;
    }
    else {
      return -1;
    }
  }
  return result;
}


int main() {
  
  int N;
  scanf("%d", &N);
  
  printf("%d\n", sugar(N));
  
  return 0;

}
