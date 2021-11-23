#include <stdio.h>
#include <time.h>

#define MAX_DIM 512

typedef struct {
	int dim;
	float data[MAX_DIM];
} StaticVector;

typedef StaticVector Vector;

void FillVector(Vector *vec, int dim, int dir);
float GetVectorData(Vector *vec, int idx);
void SetVectorData(Vector *vec, int idx, float v);
void DisplayVector(Vector *vec);
float DotProduct_slow(Vector vec1, Vector vec2);
float DotProduct(Vector *vec1, Vector *vec2);


int main()
{
	Vector vec1, vec2;
    clock_t start1, end1, start2, end2;
    float result_time;

	FillVector(&vec1, 10, 0);
	printf("vec1 = ");
	DisplayVector(&vec1);

	FillVector(&vec2, 10, 1);
	printf("vec2 = ");
	DisplayVector(&vec2);

    start1 = clock();
    printf("DotProduct_slow(vec1, vec2) = %f\n", DotProduct_slow(vec1, vec2));
    end1 = clock();

    result_time = (float)(end1 - start1);
    printf("%.1f ms\n", result_time);

    start2 = clock();
    printf("DotProduct(&vec1, &vec2) = %f\n", DotProduct(&vec1, &vec2));
    end2 = clock();

    result_time = (float)(end2 - start2);
    printf("%.1f ms\n", result_time);

	return 0;
}

void FillVector(Vector *vec, int dim, int dir)
{
	vec->dim = dim;

	if(dir == 0) {
		for(int i = 1; i < dim + 1; i++)
			vec->data[i-1] = (float)i;
	}
	else {
		for(int i = 0; i < dim; i++) 
			vec->data[i] = (float)(dim - i);
	}
}

float GetVectorData(Vector *vec, int idx)
{
	return vec->data[idx];
}

void SetVectorData(Vector *vec, int idx, float v)
{
	vec->data[idx] = v;
}

float DotProduct_slow(Vector vec1, Vector vec2)
{
	if(vec1.dim != vec2.dim){
		printf("Error! vec1.dim = %d, vec2.dim = %d\n", vec1.dim, vec2.dim);
		return 0.F;
	}
	float dot = 0.F;

	for(int i = 0; i < vec1.dim; i++)
		dot += vec1.data[i] * vec2.data[i];

	return dot;
}

float DotProduct(Vector *vec1, Vector *vec2)
{
	if(vec1->dim != vec2->dim){
		printf("Error! vec1->dim = %d, vec2->dim = %d\n", vec1->dim, vec2->dim);
		return 0.F;
	}

	float dot = 0.F;

	for(int i = 0; i < vec1->dim; i++) {
		dot += vec1->data[i] * vec2->data[i];
	}

	return dot;
}

void DisplayVector(Vector *vec)
{
	for(int i = 0; i < vec->dim; i++)
		printf("%.2f ", vec->data[i]);

	printf("(dim = %d)\n", vec->dim);
}
