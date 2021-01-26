#include <stdio.h>

int main() {
  long long a, b, c;
  long long count = 0;
  
  scanf("%lld %lld %lld", &a, &b, &c);

  if( b >= c ) {
      printf("-1");
      return 0;
  }
  count = a / (c - b) + 1;

  printf("%lld\n", count);
  return 0;
}
