#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void input_array(int a[], int cnt)
{
   int i;
   for (i = 0; i < cnt; i++) {
      a[i] = rand() % 100 + 1;
   }
}

void output_array(int a[], int cnt)
{
   int i;
   printf("Array:\n");
   for (i = 0; i < cnt; i++) {
      printf("\t%d", a[i]);
   }
   printf("\n");
}

void swap(int *x, int *y)
{
   int tmp = *x;
   *x = *y;
   *y = tmp;
}

bool sort(int a[], int cnt)
{
   int i, j;
   for (i = 0; i < cnt - 1; i++) {
      for (j = i + 1; j < cnt; j++) {
         if (a[i] > a[j]) {
            swap(&a[i], &a[j]);
         }
      }
   }
   return true;
}

int main()
{
    srand(time(NULL));
    
    int size;
    printf("input number of data: ");
    scanf("%d", &size);
    int *arr = (int *)malloc(sizeof(int) * size);
    
    input_array(arr, size);
    output_array(arr, size);

    if(sort(arr, size)) {
        printf("Called swap function\n");
        printf("============= sorted array =============\n");
        output_array(arr, size);
        int min = arr[0], max = arr[size-1];
        printf("\nmin: %d, max: %d\n", min, max);
    }

    return 0;
}