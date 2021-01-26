#include <stdio.h>
#include <stdlib.h>

double find_min_index(double arr[], int n) {
  double min = arr[0];

  for(int i = 0 ; i < n ; i++) {
    if(min >= arr[i]) {
       min = arr[i];
    }
  }

  return min;
}

int main() {
  int X, Y;
  int N;
  int *x, *y;
  double *price;

  scanf("%d %d", &X, &Y);
  scanf("%d", &N);

  x = (int *)malloc(sizeof(int)*N);
  y = (int *)malloc(sizeof(int)*N);
  price = (double *)malloc(sizeof(double)*N+1); //세븐25포함 N+1

  for(int i = 0; i < N; i++) {
    scanf("%d %d", &x[i], &y[i]);
    price[i] = (double)x[i] / (double)y[i];
  }
  price[N] = (double)X / (double)Y; //세븐 25포함

  double lowest_price = find_min_index(price, N+1) * 1000.0; //세븐 25포함

  printf("%.2lf", lowest_price);

  free(x);
  free(y);
  free(price);
  return 0;
}
