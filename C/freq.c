#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void input_data(int *arr, int *freq, int size);
void output_data(int *arr, int size);
int fun5(int* freq);
float dev(int *arr, int size);
void search(int *arr, int size);
void frequency(int *freq);

int main()
{
  srand(time(NULL));
  int num, size;
  printf("input number of data: ");
  scanf("%d", &size);
  
  int *arr = (int *)malloc(sizeof(int) * size);
  int freq[11] = {0, }; // 모든 index의 element를 0으로 초기화

  input_data(arr, freq, size);

  while(1)
  {
    printf("\n");
    printf("*****************************************************************\n");
    printf("**  (1) 생성된 데이터의 내용을 출력(display)                   **\n");
    printf("**  (2) 각 수의 빈도수(frequency)를 출력(1차원 배열 출력)      **\n");
    printf("**  (3) 입력된 data의 표준편차 출력                            **\n");
    printf("**  (4) 입력 숫자를 DATA array에서 찾기                        **\n");
    printf("**  (5) 최빈수(mode)찾기                                       **\n");
    printf("**  (6) 종료                                                   **\n");
    printf("*****************************************************************\n");
    printf("input menu:");
    scanf("%d",&num);
    printf("\n");

    switch(num) {
      case 1:
        output_data(arr, size);
        continue;
      case 2:
        frequency(freq);
        continue;
      case 3:
        printf("Standard deviation: %.2f\n", dev(arr, size));
        continue;
      case 4:
        search(arr, size);
        continue;
      case 5:
        printf("Mode: %d, %d번 생성됨\n", fun5(freq), freq[fun5(freq)]);
        continue;
      case 6:
        break;
    }
  }
  return 0;
}

void input_data(int *arr, int *freq, int size)
{
  int i;
  for (i = 0; i < size; i++) {
    arr[i] = rand() % 11;
    freq[arr[i]]++;
  }
}

void output_data(int arr[], int size)
{
  int i;
  printf("\n");
  for (i = 0; i < size; i++) {
      printf("%4d", arr[i]);

      if(i % 10 == 9) printf("\n");
  }
}

int fun5(int* freq)
{
  int max = 0;
  int mode;
  for(int i = 0 ; i < 11; i++)
  {
    if(max < freq[i]) {
      max = freq[i];
      mode = i;
    }
  }

  return mode;
}

float dev(int *arr, int size)
{
  float sum = 0, s_sum = 0, var;
  float mean, std;
  for(int i = 0; i < size; i++)
    sum += arr[i];

  mean = sum / size;

  for(int i = 0; i < size; i++)
    s_sum += pow(( arr[i] - mean ), 2);
  
  var = s_sum / size;
  std = sqrt(var);

  return std;
}

void search(int *arr, int size)
{
  int target;
  int count = 0;
  printf("input find number:");
  scanf("%d", &target);

  for(int i = 0; i < size; i++) {
    if(arr[i] == target) {
      printf("data[%d] ", i);
      count++;
    }
  }
  
  if(count == 0)
    printf("There is no same data");

  printf("\n");
}

void frequency(int *freq)
{
  for(int i = 0; i < 11; i++) {
    printf("%02d: %d\t", i, freq[i]);
  }
  printf("\n");
}