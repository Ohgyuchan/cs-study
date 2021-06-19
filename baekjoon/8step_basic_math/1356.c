#include <stdio.h>

int num[11] = { 0, };

int main() {
  int N, count = 1;
  
  scanf("%d", &N);
  while(1) {
    num[count] = N % 10;
    N /= 10;
    
    if(!N) break;
    
    count++;
  }

  for(int i = 1; i < count; i++) {
    
    int left = 1, right = 1;
    
    for(int j = 1; j <= i; j++)
      left *= num[j];
    for(int k = count; k > i; k--)
      right *= num[k];

    if(left == right) {
      printf("YES\n");
      return 0;
    }
  }
  printf("NO\n");
  return 0;
}
