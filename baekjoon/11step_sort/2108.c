/*
산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이
*/
#include <stdio.h>

int num[500000] = {0, };
int minus[4001] = {0, };
int plus[4001] = {0, };

void merge (int data[], int p, int q, int r) {
    int i = p, j = q+1, k = p;
    int tmp[r]; // 새 배열
    while(i<=q && j<=r) {
        if(data[i] <= data[j]) tmp[k++] = data[i++];
        else tmp[k++] = data[j++];
    }
    while(i<=q) tmp[k++] = data[i++];
    while(j<=r) tmp[k++] = data[j++];
    for(int a = p; a<=r; a++) data[a] = tmp[a];
}

void merge_sort(int data[], int p, int r) {
    int q;
    if(p < r) {
        q = (p+r)/2;
        merge_sort(data, p , q);
        merge_sort(data, q+1, r);
        merge(data, p, q,  r);
    }
}

void descending_merge (int data[], int p, int q, int r) {
    int i = p, j = q+1, k = p;
    int tmp[r]; // 새 배열
    while(i<=q && j<=r) {
        if(data[i] > data[j]) tmp[k++] = data[i++];
        else tmp[k++] = data[j++];
    }
    while(i<=q)
        tmp[k++] = data[i++];
    while(j<=r)
        tmp[k++] = data[j++];
    for(int a = p; a <= r; a++)
        data[a] = tmp[a];
}

void descending_merge_sort(int data[], int p, int r) {
    int q;
    if(p < r) {
        q = (p+r)/2;
        descending_merge_sort(data, p , q);
        descending_merge_sort(data, q+1, r);
        descending_merge(data, p, q,  r);
    }
}

int main() {
    int n;
    float avg = 0;
    int mid = 0;
    int total = 0;
    int freq = 0;
    int range = 0;
    
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
        total += num[i];
        if(num[i] < 0) {
            minus[num[i]]++;
        } else {
            plus[num[i]]++;
        }
    }

    merge_sort(num, 1, n);
    descending_merge_sort(minus, 0, num[n]);
    descending_merge_sort(plus, 0, num[n]);

    avg = total / n;
    mid = num[(n / 2) + 1];
    freq = minus[n-1] >= plus[n-1] ? minus[n-1] : plus[n-1];
    range = num[n] - num[1];

    printf("%.0f\n", avg);
    printf("%d\n", mid);
    printf("%d\n", freq);
    printf("%d\n", range);

    return 0;
}