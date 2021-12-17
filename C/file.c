#include<stdio.h>

int main()
{
    FILE *fp;
    char op;
    int num1, num2, num3;

    fp = fopen("data.txt", "rt");

    if(fp == NULL){
        printf("파일열기 실패\n");
        return -1;
    }
    
    int i = -1;
    int result;
    while (!feof(fp)) {
        i++;
        fscanf(fp, "%c%d %d %d\n", &op, &num1, &num2, &num3);
        switch(op) {
            case '+' :
                result = num1 + num2 + num3;
                printf("%c %d %d %d \t line number %d: %d\n", op, num1, num2, num3, i, result);
                break;
            case '-' : 
                result = num1 - num2 - num3;
                printf("%c %d %d %d \t line number %d: %d\n", op, num1, num2, num3, i, result);
                break;
            case '*' : 
                result = num1 * num2 * num3;
                printf("%c %d %d %d \t line number %d: %d\n", op, num1, num2, num3, i, result);
                break;  
            case '/' : 
                printf("%c %d %d %d \t line number %d: %f\n", op, num1, num2, num3, i, ((float)num1 / num2 / num3));
                break;  
            case '%' : 
                result = num1 % num2 % num3;
                printf("%c %d %d %d \t line number %d: %d\n", op, num1, num2, num3, i, result);
                break;  
            default :
                printf("wrong input\n");
        }
    }

    fclose(fp);

    return 0;
}