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
#include "Run.h"
#include "alloc.h"



void run(int m_vals[], int m_size, int n_vals[], int n_size, int d_vals[], int d_size, int iter);

int main() {
	int dv[] = {32, 64, 128, 256, 512};
	int nv[] = {200, 400, 800, 1600};
	int mv[] = {50000, 100000};
	run(mv, 2, nv, 4, dv, 5, 1);
	return 0;
}

void run(int m_vals[], int m_size, int n_vals[], int n_size, int d_vals[], int d_size, int iter){
	static void (*DistmetricM[2])() = {run_manhattan_seq, run_manhattan_par};
	static void (*DistmetricE[2])() = {run_euclid_seq,  run_euclid_par};
	int metricDetailsM[2][2] = {{1, 0}, {1, 1}};
	int metricDetailsE[2][2] = {{0, 0}, {0, 1}};
	static void(*Sort[9])() = {run_qsort_seq, run_qsort_parS, run_qsort_parT, run_mergesort_seq, run_mergesort_parS, run_mergesort_parT, run_bitonicSort_seq, run_bitonicSort_parS, run_bitonicSort_parT};
	int sortDetails[9][3] = {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {1, 0, 0}, {1, 1, 0}, {1, 2, 0}, {2, 0, 0}, {2, 1, 0}, {2, 2, 0}};
	
	FILE *distfile = fopen("dresults.txt","w");
	FILE *sortfile = fopen("sresults.txt","w");
	fprintf(distfile, "+===========+===========+===========+===========+===========+===========+\n");
	fprintf(distfile, "| Metric    | S or P    |   m       | n         | d         | S Time    |\n");
	fprintf(distfile, "+===========+===========+===========+===========+===========+===========+\n");
	
	fprintf(sortfile, "+===========+===========+===========+===========+===========+===========+\n");
	fprintf(sortfile, "| Sort      | S or P    |   m       | n         | d         | S Time    |\n");
	fprintf(sortfile, "+===========+===========+===========+===========+===========+===========+\n");
	for(int x = 0; x < m_size; x++){
		int m = m_vals[x];
		for(int y = 0; y < n_size; y++){
			int n = n_vals[y];
			for(int z = 0; z < d_size; z++){
				int d = d_vals[z];
				float **ref, **query, **distM, **distE;
				
				ref = create2DArray(m, d);
				query = create2DArray(n, d);
				
				distM = create2DArray(n, m);
				distE = create2DArray(n, m);
				
				ref = fill2dFloatWithRand(ref, m, d);
				query = fill2dFloatWithRand(query, n, d);
				
				for(int met = 0; met < 2; met++){
					printf("m = %i\n", m);
					printf("n = %i\n", n);
					printf("d = %i\n", d);
					printf("Euclidean = %i\n", met);
					double start = omp_get_wtime();
					DistmetricE[met](&distE[0], &ref[0], &query[0], n, m, d);
					double drun_time = omp_get_wtime() - start;
					char dPar[10];
					if(metricDetailsE[met][1] == 0){
						strcpy(dPar, "Serial");
					} else{
						strcpy(dPar, "Parallel");
					}
					fprintf(distfile, "| %-10s| %-10s| %-10i| %-10i| %-10i| %-10f|\n", "Euclidean", dPar, m, n, d, drun_time);
				}
				
				for(int met = 0; met < 2; met++){
					printf("m = %i\n", m);
					printf("n = %i\n", n);
					printf("d = %i\n", d);
					printf("Manhattan = %i\n", met);
					double start = omp_get_wtime();
					DistmetricM[met](&distM[0], &ref[0], &query[0], n, m, d);
					double drun_time = omp_get_wtime() - start;
					char dPar[10];
					if(metricDetailsM[met][1] == 0){
						strcpy(dPar, "Serial");
					} else{
						strcpy(dPar, "Parallel");
					}
					fprintf(distfile, "| %-10s| %-10s| %-10i| %-10i| %-10i| %-10f|\n", "Manhattan", dPar, m, n, d, drun_time);
				}
				fprintf(distfile, "+===========+===========+===========+===========+===========+===========+\n");
				free2dArray(ref,m);
				
				free2dArray(query,n);
				
				for(int met = 0; met < 2; met++){
					for(int s = 0; s < 9; s++){
						printf("m = %i\n", m);
						printf("n = %i\n", n);
						printf("d = %i\n", d);
						printf("Metric = %i\n", met);
						printf("sort = %i\n", s);
						
						float **dist = create2DArray(n, m);
						
						if(met == 0){
							copy2dFloat(distE, dist, n, m);
						} else{
							copy2dFloat(distE, dist, n, m);
						}
						char sType[10];
						char sPar[10];
						double start = omp_get_wtime();
						Sort[s](dist, n, m, 5000);
						double stime = omp_get_wtime() - start;
						if(sortDetails[s][0] == 0){
							strcpy(sType, "Quick");
						} else if(sortDetails[s][0] == 1){
							strcpy(sType, "Merge");
						} else{
							strcpy(sType, "Bitonic");
						}
						
						if(sortDetails[s][1] == 0){
							strcpy(sPar, "Serial");
						} else if(sortDetails[s][1] == 1){
							strcpy(sPar, "Section");
						} else{
							strcpy(sPar, "Task");
						}
						free2dArray(dist,n);
						fprintf(sortfile, "| %-10s| %-10s| %-10i| %-10i| %-10i| %-10f|\n", sType, sPar, m, n, d, stime);
						printf("\n\n");
					}
					fprintf(sortfile, "+===========+===========+===========+===========+===========+===========+\n");
				}
				free2dArray(distE,n);
				free2dArray(distM,n);
			}
		}
	}
	fclose(distfile);
	fclose(sortfile);
}

