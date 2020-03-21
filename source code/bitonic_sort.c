#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitonic_sort.h"


void compAndSwap(float* a, int i, int j, int dir)
{
    if (dir == (a[i] > a[j]))
    {
    	int t;
    	//printf("%f\n",a[i]);
    	t = a[i];
    	a[i] = a[j];
    	a[j] = t;
    	//printf("%f\n",a[i]);
    }
}

int pow_of_2_less_than(int n)
{
	int k = 1;
	while(k > 0 && k < n){
		k = k << 1;
	}
	return (unsigned int) k >> 1;
}

void bitonicMerge(float* a, int low, int cnt, int dir) 
{ 
    if (cnt>1) 
    { 
        int k = pow_of_2_less_than(cnt); 
        for (int i=low; i<low+cnt-k; i++) 
            compAndSwap(a, i, i+k, dir); 
        bitonicMerge(a, low, k, dir); 
        bitonicMerge(a, low+k, cnt - k, dir); 
    } 
} 
  
void bitonicSort_seq(float* a,int low, int cnt, int dir, int low_limit) 
{ 
    if (cnt>1) 
    { 
        int k = cnt/2; 
        
  	 
        bitonicSort_seq(a, low, k, !dir, low_limit); 
        
        bitonicSort_seq(a, low+k, cnt-k, dir, low_limit); 
  
        bitonicMerge(a,low, cnt, dir); 
    } 
}

void bitonicSort_parS(float* a,int low, int cnt, int dir, int low_limit) 
{ 
    if (cnt>1) 
    { 
        int k = cnt/2;
	if (cnt < low_limit)
    	{
    		bitonicSort_seq(a, low, cnt, dir, low_limit); 
    	}
    	else
    	{ 
        #pragma omp parallel sections
        {
  	#pragma omp section
        bitonicSort_parS(a, low, k, !dir, low_limit); 
        #pragma omp section
        bitonicSort_parS(a, low+k, cnt-k, dir, low_limit); 
        }
        bitonicMerge(a,low, cnt, dir); 
    } 
}
}


void bitonicSort_parT(float* a,int low, int cnt, int dir, int low_limit) 
{ 
    if (cnt>1) 
    { 
    	int k = cnt/2;
    	if (cnt < low_limit)
    	{
    		bitonicSort_seq(a, low, cnt, dir, low_limit);
    	}
    	else
    	{ 
  		#pragma omp task
        	bitonicSort_parT(a, low, k, !dir, low_limit); 
        	#pragma omp task
        	bitonicSort_parT(a, low+k, cnt-k, dir, low_limit); 
  		#pragma omp taskwait
        	bitonicMerge(a,low, cnt, dir); 
        }
    }
}


