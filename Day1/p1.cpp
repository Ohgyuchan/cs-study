#include <stdio.h>
#include <string.h>

int main(){
	char s[101] = "";
  int alpha[26] = {0, };
  scanf("%s", s);
  
  for(int i = 0; i < 101; i++) {
    switch(s[i]) {
      
      case 'a' :
        alpha[0]++;
        continue;
      
      case 'b' :
        alpha[1]++;
        continue;
      
      case 'c' :
        alpha[2]++;
        continue;
  
      case 'd' :
        alpha[3]++;
        continue;  
  
      case 'e' :
        alpha[4]++;
        continue;
   
      case 'f' :
        alpha[5]++;
        continue;
   
      case 'g' :
        alpha[6]++;
        continue;
     
      case 'h' :
        alpha[7]++;
        continue;
     
      case 'i' :
        alpha[8]++;
        continue;
     
      case 'j' :
        alpha[9]++;
       continue;
     
      case 'k' : 
        alpha[10]++;
        continue;
     
      case 'l' :
        alpha[11]++;
        continue;
    
      case 'm' :
        alpha[12]++;
        continue;
    
      case 'n' :
        alpha[13]++;
        continue;
    
      case 'o' :
        alpha[14]++;
        continue;
    
      case 'p' :
        alpha[15]++;
        continue;
    
      case 'q' :
        alpha[16]++;
        continue;
    
      case 'r' :
        alpha[17]++;
        continue;
    
      case 's' :
        alpha[18]++;
        continue;
    
      case 't' :
        alpha[19]++;
        continue;
    
      case 'u' :
        alpha[20]++;
        continue;
     
      case 'v' :
        alpha[21]++;
        continue;
     
      case 'w' :
        alpha[22]++;
        continue;
      
      case 'x' :
        alpha[23]++;
        continue;
      
      case 'y' :
        alpha[24]++;
        continue;
      
      case 'z' :
        alpha[25]++;
        continue;
    }
  }
  for(int i = 0; i < 26; i++) {
    printf("%d ", alpha[i]);
  }
  return 0;
} 
