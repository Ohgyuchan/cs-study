#include <stdio.h>
#include <string.h>

int main() {
    char words[2][100];
    char input[100];
    
    int i = 0;
    while(1) {
        printf("Enter Word: ");
        scanf("%s", input);
        if(strlen(input) > 20) {
            printf("Too long word\n");
            continue;
        }
        if(strlen(input) <= 2)
            break;
        
        if(i == 0) {
            strcpy(words[0], input);
            strcpy(words[1], input);
            i++;
            continue;
        }

        if(strcmp(words[0], input) > 0)
            strcpy(words[0], input);
        if(strcmp(words[1], input) < 0)
            strcpy(words[1], input);
    }

    printf("Smallest word: %s\n", words[0]);
    printf("Largest word: %s\n", words[1]);
    return 0;
}