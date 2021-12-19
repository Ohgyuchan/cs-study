#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    srand(time(NULL));
    char *word;
    char *wordlist[] = {"school", "library", "store", "factory", "computer",
                        "labtop", "word", "world", "handong", "major", "minor",
                        "apple", "banana", "berry", "peach", "carrot", "odd", "even",
                        "event", "hi", "hello", "bye", "iPhone", "Android", "SAMSUNG", "LG"};
    int idx = rand() % 26 + 1;
    word = wordlist[idx];
    
    int wordLen = sizeof(word);
    char *problem = (char *)malloc(wordLen + 1);
    
    for(int i=0; i <wordLen; i++) problem[i] = '_';

    int cnt = 10;
    int i = 0;

    while (1) {
        printf("The word looks like this: %s\n", problem);
        if(cnt == 0) {
            printf("You lost!!!\n");
            printf("Dou you want another game(y/n)");
            char yes;
            scanf("%c", &yes);
            if(yes == 'y') {
                cnt = 10;
                int idx = rand() % 26 + 1;
                word = wordlist[idx];
                
                int wordLen = sizeof(word);
                char *problem = (char *)malloc(wordLen + 1);
                
                for(int i=0; i <wordLen; i++) problem[i] = '_';
            } else {
                return 0;
            }
        }

        printf("You have %d guess left.\n", cnt);
        printf("your guess: ");
        
        char *answer;
        scanf("%s", answer);
        fflush(stdin); // 스트림을 비우기 위한 함수 이게 없으면 printf 두번 됨.
        cnt--;
        if(isdigit(answer[0])) {
            printf("input answer:");
            scanf("%s", answer);
            if( strcmp(answer, word) == 0) {
                printf("%s is correct\nYou win!!", answer);
            }
        }
        for(i = 0; i < wordLen; i++) {
            if(problem[i] == '_' && tolower(word[i]) == tolower(answer[0])) {
                problem[i] = tolower(answer[0]);
            }
        }

        for(i = 0; i < wordLen; i++)
            if(problem[i] == '_') break;
    }
    return 0;
}