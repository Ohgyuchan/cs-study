#include <stdio.h>
#include <stdlib.h>

#define N 50

int count(int score[][4]) {
    int count = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 4; j++) {
            if(score[i][j] >= 0 && score[i][j] < 50)
                count++;
        }  
    }
    return count;
}

int sum(int score[]) {
    int sum = 0;
    for(int i = 0; i < 4; i++)
        sum += score[i];
    return sum;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// int main() {
//     char s[8] = "HanDong";
//     char *p;
//     for(p=&s[2]; p >= s; p--) {
//         ++*p;
//         printf("%c\n", *p);
//     }
//     printf("%s", s);
    
//     return 0;
// }

int main() {
    int a, b;
    char con1[10];
    char con2[10];
    scanf("%d %d", &a, &b);
    if(a > b) {
        int i = 0;
        int temp = a;
        while(temp > 0) {
            int i = 0;
        }
    } else {

    }
    return 0;
}


