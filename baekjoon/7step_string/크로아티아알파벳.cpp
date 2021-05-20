#include <stdio.h>
#include <string.h>

int main() {
  char input[101];
  scanf("%s", input);
  
  int count = strlen(input);
  for(int i = 0; i < strlen(input)-1; i++) {
    if(input[i] == 'c') {
      if(input[i+1] == '=' || input[i+1] == '-')
        count--;
    }
    else if(input[i] == 'd') {
      if(input[i+1] == '-')
        count--;
      if(i <= strlen(input)-2 && input[i+1] == 'z' && input[i+2] == '=') {
        count -= 2;
        i = i + 2;
        continue;
      }
    }
    else if(input[i] == 'l') {
      if(input[i+1] == 'j')
        count--;
    }
    else if(input[i] == 'n') {
      if(input[i+1] == 'j')
        count--;
    }
    else if(input[i] == 's' && input[i+1] == '=')
      count--;
    else if(input[i] == 'z' && input[i+1] == '=')
      count--;
  }
  printf("%d", count);
  return 0;
}
