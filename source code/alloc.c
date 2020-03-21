#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copy2dFloat(float **start, float **end, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			end[i][j] = start[i][j];
		}
	}
}

float** alloc2dFloat(int row, int col){
	float **out  = (float**)malloc(row*sizeof(float*));
	for(int i = 0; i < row; i++){
		out[i] = (float*)malloc(col*sizeof(float));
	}
	return out;
}

int** alloc2dInt(int row, int col){
	int **out = (int**)malloc(row*sizeof(int*));
	for(int i = 0; i < row; i++){
		out[i] = (int*)malloc(col*sizeof(int));
	}
	return out;
}

void copy2dInt(int **start, int **end, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			end[i][j] = start[i][j];
		}
	}
}


float** fill2dFloatWithRand(float **out, int row, int col){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			out[r][c] = (double)rand();
		}
	}
	return out;
}

int** fill2dIntWithSeq(int **out, int row, int col){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++){
			out[r][c] = c;
		}
	}
	return out;
}

float** create2DArray(int row, int col)
{
	float** arr = (float**)malloc(sizeof(float*)*row);

	for (int i = 0;i < row; i++)
	{
		arr[i] = (float*)malloc(sizeof(float)*col);
	}
	return arr;
}

void free2dArray(float** x,int row)
{
  for (int i = 0; i < row; i++)
    free(x[i]);
  free(x);
}



