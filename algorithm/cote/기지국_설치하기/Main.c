#include <stdio.h>
#include <stdlib.h>
/*
기지국 하나
D 만큼
*/

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main() {
	int N, D, result = 0;
	
	scanf("%d %d", &N, &D);
	
	if(D == 0) {
		printf("1\n");
		return 0;
	}
	
	int *arr = (int *)malloc(sizeof(int) * N);
	
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	
	qsort (arr, N, sizeof(int), compare);
	
	if(arr[N-1] - arr[0] <= D) {
		printf("%d\n", N);
		return 0;
	}
	
	for(int i = arr[0]; i < arr[N-1]; i++) {
		int max_ran = i + D;
		int min_ran = i - D;
		int count = 0;
		for(int j = 0; j < N; j++) {
			if(arr[j] <= max_ran && arr[j] >= min_ran) {
				count++;
			}
		}
		if(result < count)
			result = count;
	}
	
	printf("%d\n", result);
	
	return 0;
}
