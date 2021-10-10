#include <stdio.h>

int a[1000] = {0, };


// void selection_sort;
// void insertion_sort;
// void bubble_sort;
// void heap_sort;
// void merge_sort;
// void quick_sort;


int main() {
  int N;
  
  scanf("%d", &N);

  for(int i = 0; i < N; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < N; i++) {
    printf("%d\n", a[i]);
  }
  
  return 0;
}
