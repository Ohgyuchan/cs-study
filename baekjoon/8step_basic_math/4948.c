#include <stdio.h>
#include <math.h>

#define SIZE 1000001

int num[SIZE] = { 0, };

int main() {
  
  while(1) {

    int N, count = 0;
    scanf("%d", &N);
    
    if(N == 0) break;

    for(int i = 2; i <= 2 * N; i++) {
      
      if(!num[i])
        for(int j = i + i; j <= 2 * N; j += i)
          num[j] = 1;
      if(i > N && num[i] == 0)
       count++;
    
    }
    
    printf("%d\n", count);

  }
    
  return 0;
}
