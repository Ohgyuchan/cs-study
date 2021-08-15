#include <stdio.h>
int some[100][100] = {0,};
int sum(int n, int m) {
  printf("n = %d\tm = %d\n", n, m);
  some[1][1] = 1;
  
  for(int i = 2; i <= n; i++){
    for(int j = 2; j <= m; j++){
      some[1][j] = 1;
      some[i][1] = 1;
      some[i][j] = some[i][j-1] + some[i-1][j] + some[i-1][j-1];
    }
  }
  return some[n][m];
}
int main() {
 printf("%d", sum(10,10));
 return 0;
}
