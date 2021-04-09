#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

int word_time(char word[]);

int main() {
  char word[16];

  cin >> word;
  cout << word_time(word);
  

  return 0;
}

int word_time(char word[]) {
  int time = 0;
  
  for(int i = 0; i < strlen(word); i++) {
    switch(word[i]){
      case 'A' :
      case 'B' : 
      case 'C' : 
        time += 3;
        break;
      case 'D' : 
      case 'E' : 
      case 'F' :
        time += 4;
        break; 
      case 'G' : 
      case 'H' : 
      case 'I' : 
        time += 5;
        break;
      case 'J' : 
      case 'K' : 
      case 'L' : 
        
        time += 6;
        break;
      case 'N' : 
      case 'M' : 
      case 'O' :
        
        time += 7;
        break; 
      case 'P' : 
      case 'Q' : 
      case 'R' : 
      case 'S' : 
        time += 8;
        break;
      case 'T' : 
      case 'U' :
      case 'V' :
        time += 9;
        break;  
      case 'W' : 
      case 'X' : 
      case 'Y' : 
      case 'Z' :
        time += 10;
        break;
      default : continue; 
    }

  }

  return time;
}
