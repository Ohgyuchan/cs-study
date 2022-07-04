#include <stdio.h>

int main()
{
    int input[5] = {
        0,
    };

    scanf("%d", &input[0]);
    scanf("%d", &input[1]);
    scanf("%d", &input[2]);
    scanf("%d", &input[3]);
    scanf("%d", &input[4]);

    int result = 0;

    for (int i = 0; i < 5; i++)
    {
        result += input[i] * input[i];
    }

    printf("%d", result % 10);
}