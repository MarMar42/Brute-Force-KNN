#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <string.h>
#include <sys/time.h>
#include "quick_sort.h"
#include "metrics.h"
#include "merge_sort.h"
#include "bitonic_sort.h"



void run_qsort_seq(float **dist, int n, int m, int low){
	for(int i = 0; i < n; i++){
		q_sort_seq(0, m-1, &dist[i][0], low);
	}	
}

void run_qsort_parS(float **dist, int n, int m, int low){
	for(int i = 0; i < n; i++){
		q_sort_parS(0, m-1, &dist[i][0], low);
	}
}

void run_qsort_parT(float **dist, int n, int m, int low){
	for(int i = 0; i < n; i++){
		#pragma omp parallel
		{
			#pragma omp single nowait
			{
	    			q_sort_parT(0, m-1, &dist[i][0], low);
	    		}
		}
	}
}

void run_mergesort_seq(float **dist, int n, int m, int low_limit){
	for(int i = 0; i < n; i++){
		mergeSort_seq(&dist[i][0],0, m-1, low_limit);
	}	
}


void run_mergesort_parS(float **dist, int n, int m, int low){
	for(int i = 0; i < n; i++){
		mergeSort_parS(&dist[i][0],0, m-1, low);
	}
}

void run_mergesort_parT(float **dist, int n, int m, int low){
	for(int i = 0; i < n; i++){
		#pragma omp parallel
		{
			#pragma omp single nowait
			{
	    			mergeSort_parT(&dist[i][0],0, m-1,low);
	    		}
		}
	}
}

void run_bitonicSort_seq(float **dist, int n, int m, int low_limit){
	for(int i = 0; i < n; i++){
		bitonicSort_seq(&dist[i][0],0, m, 1, low_limit);
	}	
}

void run_bitonicSort_parS(float **dist, int n, int m, int low_limit){
	for(int i = 0; i < n; i++){
		bitonicSort_parS( &dist[i][0],0, m, 1, low_limit);
	}
}

void run_bitonicSort_parT(float **dist, int n, int m, int low_limit){
	for(int i = 0; i < n; i++){
		#pragma omp parallel
		{
			#pragma omp single nowait
			{
	    			bitonicSort_parT(&dist[i][0],0, m, 1, low_limit);
	    		}
		}
	}
}


void run_euclid_seq(float **dist, float **ref, float **query, int n, int m, int d){
	for(int q = 0; q < n; q++){
		for(int r = 0; r < m; r++){
			dist[q][r] = euclidDist(query[q], ref[r], d);
		}
	}
}

void run_euclid_par(float **dist, float **ref, float **query, int n, int m, int d){
	int i;
	#pragma omp parallel for private(i) shared(dist)
	for(i = 0; i < n*m; i++){
		int q = i/m, r = i%m;
		dist[q][r] = euclidDist(query[q], ref[r], d);
	}
}

void run_manhattan_seq(float **dist, float **ref, float **query, int n, int m, int d){
	for(int q = 0; q < n; q++){
		for(int r = 0; r < m; r++){
			dist[q][r] = manHatDist(query[q], ref[r], d);
		}
	}
}

void run_manhattan_par(float **dist, float **ref, float **query, int n, int m, int d){
	int i;

	#pragma omp parallel for private(i) shared(dist)
	for(i = 0; i < n*m; i++){
		int q = i/m, r = i%m;
		dist[q][r] = manHatDist(query[q], ref[r], d);
		
	}
}


