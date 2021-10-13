// void merge_sort;
#include <stdio.h>

int num[1000000] = {0, };
int N;

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
void print_out() {
    for(int i = 0; i < N; i++)
        printf("%d\n", num[i]);
}

int main() {
    scanf("%d", &N);

    for(int i = 0; i < N; i++)
        scanf("%d", &num[i]);

    merge_sort(num, 0, N-1);

    print_out();

    return 0;
}