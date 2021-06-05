#include <stdio.h>
#include <stdlib.h>

int dp[5001];

void greedy_sugar(int n) {
  /*
   * 그리디: 5로 먼저 담고 남은 양 판별
   */
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
      printf("-1\n");
      return;
    }
  }
  printf("%d\n", result);
}

void dp_sugar(int n) {
  /*
   * dp: dp[3], dp[5] = 1이고,
   * dp[i] = dp[i-3] 과 dp[i-5] 중에서 더 작은 값에 +1
   * dp[i]
   */
  dp[3] = 1;
  dp[5] = 1;

  for(int i = 6; i <= n; i++) {
    if(dp[i-3])
      dp[i] = dp[i-3] + 1;

    if(dp[i-5]) {

      if(dp[i]) {
        
        if(dp[i] >= dp[i-5] + 1)
          dp[i] = dp[i-5] + 1;
        
        else
          dp[i] = dp[i];
      }
      else
        dp[i] = dp[i-5] + 1;
    }

   }

   if(dp[n] == 0)
     printf("-1\n");
   
   else
     printf("%d", dp[n]);

}

int main() {
  
  int N;
  scanf("%d", &N);
 
  greedy_sugar(N);
  //dp_sugar(N);
  
  return 0;

}
