#include <stdio.h>
#include <time.h>

void split_time(long total_sec, int *hr, int *min, int *sec);

int main(void)
{
    int hr, min, sec;
    long total_sec = (long)time(NULL);

    split_time(total_sec, &hr, &min, &sec);

    printf("Current UTC %02d시%02d분%02d초 입니다.\n", hr, min, sec);
            
    return 0;
}

void split_time(long total_sec, int *hr, int *min, int *sec) {
    *sec = total_sec;
    *min = *sec / 60;
    *sec = *sec % 60;
    *hr = *min / 60;
    *hr = *hr % 24;
    *min = *min % 60;
}