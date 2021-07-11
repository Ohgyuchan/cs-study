#include <stdio.h>
#include <math.h>

int main() {
  int cycle;
  int x1, y1, r1, x2, y2, r2;
  double distance, subtraction;
  int addition;

  scanf("%d", &cycle);

  for(int i = 0 ; i < cycle; i++) {
    scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);
    
    distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    subtraction = r1 > r2 ? r1 - r2 : r2 - r1;
    addition = r1 + r2;

    if(distance == 0 && subtraction == 0)
      printf("-1\n");
    
    else if(subtraction < distance && distance < addition)
      printf("2\n");
    
    else if(distance == addition || distance == subtraction)
      printf("1\n");
    
    else
      printf("0\n");

  }

  return 0;
}
