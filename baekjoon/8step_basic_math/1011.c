#include <stdio.h>
#include <math.h>

int main() {
  int T;
  long sr, x, y;

  scanf("%d", &T);

  for(int i = 0 ; i < T; i++) {
    scanf("%ld %ld", &x, &y);

    sr = (int)sqrt(y-x);

    if((y-x) == sr*sr)
      printf("%ld\n", 2 * sr-1);
    else if(sr*sr<(y-x) && (y-x) <= sr*sr+sr)
      printf("%ld\n", 2*sr);
    else if(sr*sr+sr < (y-x) && (y-x) < (sr+1) * (sr+1))
      printf("%ld\n", 2*sr+1);
  }

  return 0;
}
