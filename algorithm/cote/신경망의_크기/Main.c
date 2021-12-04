#include <stdio.h>
#include <stdlib.h>

int main() {
	int N;
	int result = 0;
	scanf("%d", &N);
	
	int *arr = (int *)malloc(sizeof(int) * N);
	
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		
		if(i > 0)
			result += (arr[i-1] * arr[i]);
	}
		
	printf("%d\n", result);
	
	return 0;
}
