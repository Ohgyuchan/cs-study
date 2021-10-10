#include <stdio.h>

void up_down_sort(int a[], int n) {
  for(int i = 0; i < n-1; i++) {
    if(a[i] < a[i+1]) {
      int temp = a[i];
      a[i] = a[i+1];
      a[i+1] = temp;
    }
  }
}

int main() {
  int N;
  
  scanf("%d", &N);

  return 0;
}
