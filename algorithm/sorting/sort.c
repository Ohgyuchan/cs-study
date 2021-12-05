/*
정렬 알고리즘 (Sorting Algorithms)
1. 선택 정렬 (Selection Sort)
2. 삽입 정렬 (Insertion Sort)
3. 버블 정렬 (Bubble Sort)
4. 합병 정렬 (Merge Sort)
5. 퀵 정렬 (Quick Sort)
*/
#include "sort.h"

void print_arr(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d\t", arr[i]);
        if(i % 5 == 4)
            printf("\n");
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int *arr, int size) {
    for(int i = 0; i < size-1; i++) {
        int min_idx = i;
        
        for(int j = i + 1; j < size; j++)
            if(arr[i] > arr[j]) min_idx = j;

        swap(&arr[i], &arr[min_idx]);
    }
}

void insertion_sort() {

}

void bubble_sort() {

}

void merge_sort() {

}

void quick_sort() {

}
