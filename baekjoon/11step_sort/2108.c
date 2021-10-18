/*
산술평균 : N개의 수들의 합을 N으로 나눈 값
중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
최빈값 : N개의 수들 중 가장 많이 나타나는 값
범위 : N개의 수들 중 최댓값과 최솟값의 차이
*/
#include <stdio.h>

int num[500000] = {0, };

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

int mode(int list[], int n)
{
	int ar[8001] = { 0 };
	int i, idx, max = 0, cnt = 0;

	for (i = 0; i < n; i++)
	{
		idx = list[i] + 4000;
		ar[idx] += 1;
		
		if (ar[idx] > max)
			max = ar[idx];
	}

	for (i = 0, idx = 0; i < 8001 ; i++)
	{
		if (ar[i] == 0)
			continue;

		if (ar[i] == max)
		{
			if (cnt == 0)
			{
				idx = i;
				cnt += 1;
			}
			else if (cnt == 1)
			{
				idx = i;
				break;
			}
		}
	}
	return idx - 4000;

}

int main() {
    int n;
    float avg = 0;
    int mid = 0;
    int total = 0;
    int freq = 0;
    int sec_freq = 0;
    int range = 0;
    
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
        total += num[i];
    }

    merge_sort(num, 1, n);

    avg = (float)total / n;
    mid = num[(n / 2) + 1];
    range = num[n] - num[1];

    printf("%.0f\n", avg);
    printf("%d\n", mid);
    printf("%d\n", mode(num, n+1));
    printf("%d\n", range);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// int compare(const void* first, const void* second)
// {
// 	int* a = (int*)first;
// 	int* b = (int*)second;

// 	if (*a < *b)
// 		return -1;
// 	else if (*a > *b)
// 		return 1;
// 	else
// 		return 0;
// }

// int arith(int list[], int n)
// {
// 	double sum = 0;

// 	for (int i = 0; i < n; i++)
// 	{
// 		sum += (list[i]);
// 	}

// 	return round(sum / n);
// }

// int median(int list[], int n)
// {
// 	if (n == 1)
// 		return list[0];
// 	else
// 		return list[(n + 1) / 2 - 1];
// }

// int Mode(int list[], int n)
// {
// 	int ar[8001] = { 0 };
// 	int i, idx, max = 0, cnt = 0;

// 	for (i = 0; i < n; i++)
// 	{
// 		idx = list[i] + 4000;
// 		ar[idx] += 1;
		
// 		if (ar[idx] > max)
// 			max = ar[idx];
// 	}

// 	for (i = 0, idx = 0; i < 8001 ; i++)
// 	{
// 		if (ar[i] == 0)
// 			continue;

// 		if (ar[i] == max)
// 		{
// 			if (cnt == 0)
// 			{
// 				idx = i;
// 				cnt += 1;
// 			}
// 			else if (cnt == 1)
// 			{
// 				idx = i;
// 				break;
// 			}
// 		}
// 	}
// 	return idx - 4000;

// }

// int range(int list[], int n)
// {
// 	int max = list[n - 1];
// 	int min = list[0];

// 	return max - min;
// }

// int main()
// {
// 	int i, n;
// 	int* list;

// 	scanf("%d", &n);
// 	list = (int*)calloc(n, sizeof(int));

// 	for (i = 0; i < n; i++)
// 	{
// 		scanf(" %d", &list[i]);
// 	}
	
// 	qsort(list, n, sizeof(list[0]), compare);

// 	printf("%d\n", arith(list, n));
// 	printf("%d\n", median(list, n));
// 	printf("%d\n", Mode(list, n));
// 	printf("%d\n", range(list, n));
	
// 	return 0;
// }