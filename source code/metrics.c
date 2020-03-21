#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float euclidDist(float* q, float* p, int d)//d is dimension
{
	float sum = 0.0;
	for (int j = 0; j < d; ++j)
	{
		
		sum = sum + pow(q[j]-p[j],2);
	}
		
	return sqrt(sum);
}


float manHatDist(float* q, float* p,int d)//d is dimension
{
	float sum = 0.0;
	for (int j = 0; j < d; ++j)
	{
		sum = sum + abs(q[j]-p[j]);
	}
	return sum;
}

