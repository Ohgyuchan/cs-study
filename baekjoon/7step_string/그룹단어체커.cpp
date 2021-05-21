#include <iostream>

using namespace std;

bool wordChecker(string str);

int main() {
  int T;
  int count = 0;

  cin >> T;

  for (int i = 0; i < T; i++) {
    string str;
    cin >> str;

    if(wordChecker(str))
      count++;
  }

  cout << count << endl;
  return 0;
}

bool wordChecker(string str) {
  bool alpha[26] = {false, };
  for(int i = 0 ; i < str.length(); i++) {
    if(alpha[str[i] - 'a'])
      return false;
    else {
      alpha[str[i] - 'a'] = true;
      char check = str[i];
      while(1) {
        if(str[i] == check)
          i++;
        else
          break;
      }
      i--;
    }
  }
  
  return true;
}
