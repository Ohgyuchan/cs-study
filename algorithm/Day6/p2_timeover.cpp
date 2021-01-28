#include <iostream>
#include <string.h>
#define SIZE 51

/*
1. 길이비교
2. 같으면 더 작은 게 앞(앞글자부터 사전순)
*/

using namespace std;

void swap(char **case1, char **case2) {
  char *temp;
  temp = *case1;
  *case1 = *case2;
  *case2 = temp;
}

void stringSort(char **str, int n) {
  for(int i = 0; i < n-1; i++) {
    for(int j = i + 1; j < n; j++) {
      if(strlen(str[i]) > strlen(str[j])) { //길이비교
        swap(str[i], str[j]);
        continue;
      } else if(strlen(str[i]) == strlen(str[j])) {
        for(int k = 0; k < strlen(str[i]); k++) { //사전 순 비교
          if(str[i][k] > str[j][k]) { //사전 순서 비교
            swap(str[i], str[j]);
            break;
          }
        }
      }
    }
  }

}

int main() {
  int n;
  cin >> n;

  char **str = new char*[n];

 for(int i = 0 ; i < n ; i++)
    str[i] = new char[SIZE];

  for(int i = 0; i < n; i++)
    cin >> str[i];
  cout << "\n";
  stringSort(str, n);

  for(int i = 0 ; i < n ; i++) {
    if(i > 0 && strcmp(str[i], str[i-1]) == 0)
      continue;
    cout << str[i] << endl;
  }
  
  for(int i = 0; i < n; i++)
    delete[] str[i];
  delete[] str;

  return 0;
} 
