#include <stdio.h>

int main() {
  int N;
  int count;
  int arr[50][2]
  scanf("%d", &N);

  for(int i = 0 ; i < N ; i++) {
    scanf("%d %d", &arr[i][0], &arr[i][1]);
  }

  for(int i = 0; i < N; i++) {
    count = 0;

    for(int j = 0; j < N; j++) {
      if(arr[i][0] < arr[j][0])
        count++;
    }
    
    printf("%d", count + 1);

  }

  return 0;
}
