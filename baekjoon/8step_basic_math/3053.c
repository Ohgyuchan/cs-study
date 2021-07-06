#include <stdio.h>
#include <math.h>

int main() {
  int radius;
  scanf("%d", &radius);

  printf("%.6lf\n%.6lf", (double)(radius * radius * M_PI), (double)(radius * radius * 2));
  //M_PI = 원주율
  
  return 0;
}
