#include <stdio.h>

typedef struct BASIC {
    int type;
    char name[20];
    int length;
}BASIC;

typedef struct SP_DATA {
    float size;
    float quad;
}SP_DATA;

typedef struct FIG_DATA {
    BASIC basic;
    SP_DATA sp_data;
}FIG_DATA;


int main() {
    FILE *fp;
    fp = fopen("p4ata.txt", "rt");
}