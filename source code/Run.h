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



void run_qsort_seq(float** , int , int , int );
void run_qsort_parS(float** , int , int , int );
void run_qsort_parT(float** , int , int , int );

void run_mergesort_seq(float** , int , int , int );
void run_mergesort_parS(float** , int , int , int );

void run_mergesort_parT(float** , int , int , int );
void run_bitonicSort_seq(float** , int , int , int , int );

void run_bitonicSort_parS(float** , int , int , int , int );

void run_bitonicSort_parT(float** , int , int , int , int );

void run_euclid_seq(float** , float**, float**, int , int , int );

void run_euclid_par(float** , float**, float**, int , int , int );

void run_manhattan_seq(float** , float**, float**, int , int , int );

void run_manhattan_par(float** , float**, float**, int , int , int );

