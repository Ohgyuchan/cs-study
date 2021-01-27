#include <stdio.h>
#include <stdlib.h>

int getPeople(int k, int n) {
  if(n == 1)
    return 1;
  else if(k == 0)
    return n;
  return (getPeople(k-1, n) + getPeople(k, n-1));
  //k층 n호 = k-1층 n호 + k층 n-1호;
}

int main() {
  int t, k, n;
  
  scanf("%d", &t);
  int *people = (int *)malloc(sizeof(int)*t);

  for(int i = 0 ; i < t; i++) {
    scanf("%d", &k);
    scanf("%d", &n);

    people[i] = getPeople(k, n);
  }

  for(int i = 0 ; i < t; i++) {
    printf("%d\n", people[i]);
  }
  delete(people);
}

/*
1 7 28
1 6 21
1 5 15
1 4 10 20
1 3 6 10 
1 2 3 4         1층 3호 = 0층 3호 + 1층 2호
*/
