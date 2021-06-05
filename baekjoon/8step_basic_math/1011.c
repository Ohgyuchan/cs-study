#include <stdio.h>

int main() {
  int T;
  
  scanf("%d", &T);
  
  int x, y;
  
  for(int i = 0 ; i < T ; i++) {
    scanf("%d %d", &x, &y);
    alpha_centauri(x, y);
  }
  
}
