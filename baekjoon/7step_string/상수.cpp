#include <iostream>
#include <cstdlib>

using namespace std;

void swap(char num[]); // 100의 자리와 1의 자리 스왑해주는 함수char

int main() {

  char A[4], B[4]; // 숫자 3자리 + \0 -> [4]

  scanf("%s %s", A, B);
  swap(A);
  swap(B);
  
  int n1 = atoi(A); //array to integer
  int n2 = atoi(B);

  if(n1 >= n2) { cout << n1; }
  else { cout << n2; }

  return 0;
}

void swap(char num[]) {
  char temp = num[0];
  num[0] = num[2];
  num[2] = temp;
}
