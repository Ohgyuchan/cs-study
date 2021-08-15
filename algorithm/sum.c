#include <stdio.h>
int mem[100][100] = {0,};

int sum(int n, int m) {
  printf("n = %d\t m = %d\n", n ,m);
  
  if(n == 1 || m == 1)
    return 1;
  
  else if(n > 1 && m > 1) {
    if(mem[n][m] > 0)
      return mem[n][m];

    mem[n][m] = sum(n, m-1) + sum(n-1, m) + sum(n-1, m-1);
  }
  return mem[n][m];

}

int main() {
  int result = sum(10, 10);
  printf("%d", result);
  return 0;
}
