#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include "quick_sort.h"

int partition(int p, int r, float *data){
	float x=data[p];
	int k=p; 
	int l=r+1;
	float t;
	while(1){
		do{
			k++;
		}while((data[k] <= x) && (k<r));
		do{
			l--;
		}while(data[l] > x);
		while(k<l){
			t=data[k];
			data[k]=data[l];
			data[l]=t;
			do{
				k++;
			}while(data[k]<=x);
			do{
				l--;
			}while(data[l]>x);
		}
		t=data[p];
		data[p]=data[l];
		data[l]=t;
		return l;
	}
}

void q_sort_seq(int p, int r, float *data, int low_limit){
	if(p<r){
			int q=partition(p,r,data);
			q_sort_seq(p,q-1,data,low_limit);
			q_sort_seq(q+1,r,data,low_limit);
	}
}


void q_sort_parS(int p, int r, float *data, int low_limit){
	if(p<r){
		if((r-p)<low_limit){
			q_sort_seq(p,r,data, low_limit);
		}
		else{
		int q=partition(p,r,data);
		#pragma omp parallel sections
		{
			#pragma omp section
			q_sort_parS(p,q-1,data,low_limit);
			#pragma omp section
			q_sort_parS(q+1,r,data,low_limit);
			
		}
		}
	}
}


void q_sort_parT(int p, int r, float *data, int low_limit){
	if(p<r){
		if((r-p)<low_limit){
			q_sort_seq(p,r,data, low_limit);
		}
		else{
		int q=partition(p,r,data);
			#pragma omp task
			q_sort_parT(p,q-1,data,low_limit);
			#pragma omp task
			q_sort_parT(q+1,r,data,low_limit);
			#pragma omp taskwait
		}
	}
}

