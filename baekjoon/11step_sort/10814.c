#include <stdio.h>
typedef struct person {
    int age;
    char name[101];
    int order;
} Person;

Person sort[100001];

void merge(Person* arr, int first, int mid, int last)
{
    int i, j, k;
    i = first;
    j = mid + 1;
    k = first;

    while (i <= mid && j <= last) {
        if (arr[i].age < arr[j].age)
            sort[k++] = arr[i++];
        else if (arr[i].age > arr[j].age)
            sort[k++] = arr[j++];
        else {
            if (arr[i].order < arr[j].order)
                sort[k++] = arr[i++];
            else if (arr[i].order > arr[j].order)
                sort[k++] = arr[j++];
        }
    }

    if (i <= mid) {
        while (i <= mid) 
            sort[k++] = arr[i++];
    }
    else {
        while (j <= last) 
            sort[k++] = arr[j++];
    }
    for (k = first; k <= last; k++)
        arr[k] = sort[k];
}

void merge_sort(Person* arr, int first, int last) {
    int mid;
    if (first < last) {
        mid = (first + last) / 2;
        merge_sort(arr, first, mid);
        merge_sort(arr, mid + 1, last);
        merge(arr, first, mid, last);
    }
}

int main() {
    Person person[100001];

    int N;
    scanf("%d", &N);

    for(int i = 0 ; i < N ; i++) {
        scanf("%d %s", &person[i].age, person[i].name);
        person[i].order = i;
    }

    merge_sort(person, 0, N-1);
    
    for (int i = 0; i < N; i++)
        printf("%d %s\n", person[i].age, person[i].name);

    return 0;
}