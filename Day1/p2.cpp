#include <stdio.h>
#include <iostream>

int main() {
  int N;
  char *seat = new char[N+1];

  scanf("%d", &N);
  scanf("%s", seat);
  int couple_seat = 0;
  int cup_count = N + 1;
  int can_use;
  
  for(int i = 0 ; i < N; i++) {
    if(seat[i] == 'L') couple_seat++;
  }
  cup_count = cup_count - ( couple_seat / 2 );

  if(N >= cup_count) can_use = cup_count;
  else can_use = N;
  printf("%d", can_use);
  return 0;
}
