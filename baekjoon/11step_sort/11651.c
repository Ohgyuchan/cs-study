/*
입력: int
출력: 좌표(y좌표순)
*/
#include <stdio.h>

typedef struct _Point {
    int x;
    int y;
} Point;

Point p[100000];

void quick_sort(Point *data, int start, int end);

int main() {
    int N;
    scanf("%d", &N);
    
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &p[i].x, &p[i].y);
    }

    quick_sort(p, 0, N);

    return 0;
}

void swap(twod arr[], int a, int b) { twod temp = arr[a]; arr[a] = arr[b]; arr[b] = temp; }
int partition(twod arr[], int left, int right) { int pivot = left; int low = left + 1; int high = right;
// 교차되기 전까지 반복 
    while (low <= high) { 
        // pivot보다 큰 값을 찾는 과정 
        while (arr[pivot].y >= arr[low].y) { 
            if (arr[pivot].y == arr[low].y) { 
                if (arr[pivot].x > arr[low].x) 
                    low++; 
                else 
                    break;
                    // ★핵심!★ 
            }
            else
                low++;
            }
            // pivot보다 작은 값을 찾는 과정
            while (arr[pivot].y <= arr[high].y) { 
                if (arr[pivot].y == arr[high].y) { 
                    if (arr[pivot].x < arr[high].x)
                    high--;
                    else
                    break; // ★핵심!!★
                }
                else
                    high--;
            }
            if (low <= high) // 교차되지 않은 상태이면 swap
                swap(arr, low, high);
    }
    swap(arr, left, high); // pivot과 high교환 return high; // 옮겨진 pivot의 위치정보 반환 } void quicksort(twod arr[], int left, int right) { if (left <= right) { int pivot = partition(arr, left, right); quicksort(arr, left, pivot - 1); // 왼쪽 정렬 quicksort(arr, pivot + 1, right); // 오른쪽 정렬 }
}