#include<stdlib.h> 
#include<stdio.h> 
#include <omp.h>
#include"merge_sort.h"

void merge(float arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0;  
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort_seq(float arr[], int l, int r, int low_limit) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2;
  
        mergeSort_seq(arr, l, m,low_limit); 
        mergeSort_seq(arr, m+1, r, low_limit); 
  
        merge(arr, l, m, r); 
    } 
} 

void mergeSort_parS(float arr[], int l, int r, int low_limit)//Sections 
{
	if (l < r) 
	{ 
		if (r-l<low_limit)
		{
			mergeSort_seq(arr, l, r, low_limit); 
        		//mergeSort_seq(arr, m+1, r); 
		}
		else
		{
		int m = l+(r-l)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
        		mergeSort_parS(arr, l, m, low_limit); 
        		#pragma omp section 
        		mergeSort_parS(arr, m+1, r,low_limit);
  		}
  		merge(arr, l, m, r);  
  		}
        	
    }
}

void mergeSort_parT(float arr[], int l, int r, int low_limit)//Tasks
{ 
	if (l < r) 
	{ 
		if (r-l<low_limit)
		{
        		mergeSort_seq(arr, l, r, low_limit); 
		}
		else
		{
			int m = l+(r-l)/2;
			#pragma omp task
        		mergeSort_parT(arr, l, m, low_limit);
        		#pragma omp task
        		mergeSort_parT(arr, m+1, r,low_limit);
        		#pragma omp taskwait
        		merge(arr, l, m, r); 
        		
  		}
	} 
}
