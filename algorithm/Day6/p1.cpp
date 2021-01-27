#include <iostream>

using namespace std;
/*
1. 3장씩 더한다
2. m과 차이가 가장 적은 것을 구한다.
*/

int main() {
  int n, m;
  int sum = 0, result = 0;
  cin >> n >> m;
  int *card = new int[n];

  for(int i = 0; i < n; i++)
    cin >> card[i];
  
  for(int i = 0; i < n - 2; i++) {
    for(int j = i + 1; j < n - 1; j++) {
      for(int k = j + 1; k < n; k++) {
        sum = card[i] + card[j] + card[k];
        if(m - sum < m - result && sum <= m )
          result = sum;
      }
    }
  }

  cout << result << endl;
  delete[] card;
  return 0;
}
