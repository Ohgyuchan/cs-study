#include <stdio.h>

int a[1000] = {0, };

void ascending_sort(int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int temp;
      if(a[i] < a[j]) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

int main() {
  int N;
  
  scanf("%d", &N);

  for(int i = 0; i < N; i++) {
    scanf("%d", &a[i]);
  }

  ascending_sort(N);

  for(int i = 0; i < N; i++) {
    printf("%d\n", a[i]);
  }
  
  return 0;
}
