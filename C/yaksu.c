#include <stdio.h>
#include <time.h>
#define NUM 10000000000


void yaksu(int num);
int yaksu_array(int num);
long long yaksu_count(long long num);
long long yaksu_count_halp(long long num);
void prime(int num);

int main() {
    clock_t start1, start2, end1, end2;
    // yaksu(12); // 1, 2, 3, 4, 6, 12
    // prime(12);
    start1 = clock();
    yaksu_count(NUM);
    end1 = clock();
    printf("%fs\n",(float)(end1 - start1)/CLOCKS_PER_SEC);

    start2 = clock();
    yaksu_count_halp(NUM);
    end2 = clock();
    printf("%fs\n",(float)(end2 - start2)/CLOCKS_PER_SEC);

    return 0;
}

void yaksu(int num) {
    printf("==yaksu==\n");
    for(int i = 1; i <= num; i++) {
        if(num % i == 0) {
            printf("%d ", i);
        }
    }
}

long long yaksu_count(long long num) {
    int count = 0;
    for(int i = 1; i * i <= num; i++) {
        if(num % i == 0) {
            count++;
        }
        if(i * i < num) {
            count++;
        }
    }

    printf("%d\n", count);
    return count;
}

long long yaksu_count_halp(long long num) {
    int count = 0;
    for(int i = 1; i * i <= num; i++) {
        if(num % i == 0) {
            count++;
        }
        if(i * i < num) {
            count++;
        }
    }

    printf("%d\n", count);
    return count;
}

void prime(int num) {
    for(int i = 1; i <= num; i++) {
        printf("==prime==\n");
        if(num % i == 0) {
            printf("%d ", i);
        }
    }
}