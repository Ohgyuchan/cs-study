#include <stdio.h> 
#include <stdlib.h>

int main() {
    int n = 0;
    scanf("%d", &n);
    int size = n + 1;

    int *ans = (int *)malloc(sizeof(int) * (size));


    for(int i = 0 ; i < size; i++)
        ans[i] = 0;

    for (int i = 0 ; i < size; i++) {
        int num = i;
        
        while(1) {
            if(num == 0) {
                break;
            }
            ans[i] += num % 2;
            num /= 2;
        }
    }
    
    printf("[");
    
    for(int i = 0 ; i < size - 1; i++)
        printf("%d, ", ans[i]);

    printf("%d]\n", ans[size - 1]);

    return 0;
}
