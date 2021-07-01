#include <stdio.h>
#include <string.h>

int main() {
  char s;
 
  for(int i = 0 ; i < 100; i++) {
  
    if(scanf("%c", &s) == EOF) break;
    printf("%c", s); 
  
  }

  return 0;
}
