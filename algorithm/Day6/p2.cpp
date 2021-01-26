#include <stdio.h>
#include <stdlib.h>

int main() {
  int T;
  int h, w, n;

  scanf("%d", &T);
  int *YY = (int *)malloc(sizeof(int)*T);
  int *XX = (int *)malloc(sizeof(int)*T);

  for(int i = 0 ; i < T; i++) {
    scanf("%d %d %d", &h, &w, &n);
  
    YY[i] = n%h;
    XX[i] = n/h+1;
    
    if(YY[i] == 0) {
      YY[i] = h;
      --XX[i];
    }
  }
  
  for(int i = 0 ; i < T; i++)
    printf("%d\n", YY[i]*100+XX[i]);
  delete(YY);
  delete(XX);
}
