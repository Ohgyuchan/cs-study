#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) // 오름차순 비교 함수 구현
{
    int num1 = *(int *)a; // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
    int num2 = *(int *)b; // void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴

    if (num1 < num2) // a가 b보다 작을 때는
        return -1;   // -1 반환

    if (num1 > num2) // a가 b보다 클 때는
        return 1;    // 1 반환

    return 0; // a와 b가 같을 때는 0 반환
}

int binary_search(int *arr, int key, int size)
{
    int low, high, mid;
    low = 0;
    high = size - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return 1;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int search(int key, int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return 1;
    }
    return 0;
}

int main()
{
    int *arr1, *arr2;
    int N, M;

    scanf("%d", &N);

    arr1 = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr1[i]);
    }

    scanf("%d", &M);

    arr2 = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++)
    {
        scanf("%d", &arr2[i]);
    }

    // 정렬할 배열, 요소 개수, 요소 크기, 비교 함수를 넣어줌
    qsort(arr1, N, sizeof(int), compare);

    for (int i = 0; i < M; i++)
        printf("%d ", binary_search(arr1, arr2[i], N));
    // printf("\n");

    // for (int i = 0; i < M; i++)
    //     printf("%d ", search(arr2[i], N, arr1));

    free(arr1);
    free(arr2);

    return 0;
}