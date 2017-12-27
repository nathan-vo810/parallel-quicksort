#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void quicksort_small(int *array, int size);

int* read_input(int* size) {
	
	FILE *fptr;
	int len;

	if ((fptr = fopen("array_input.txt","r")) == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	fscanf(fptr,"%d",&len);
	*size = len;
	
	int *array = (int *)malloc(sizeof(int)*len);
	int i = 0;
	for (int i = 0; i < len; i++) {
		fscanf(fptr,"%d",&array[i]);
	}
	fclose(fptr);
	return array;
}

void write_output(int *array, int size) {
	FILE *fptr;

	fptr = fopen("sorted_array_parallel.c","w");
	if (fptr == NULL) {
		printf("Error writing file! - QuickSort Parallel\n");
		exit(1);
	}
	int i;
	for (i = 0; i < size; i++) {
		fprintf(fptr, "%d\n", array[i]);
	}
	fclose(fptr);
}

void write_time(int size, double time) {
	FILE *fptr;
	fptr = fopen("time_parallel.txt","a");
	if (fptr == NULL) {
		printf("Error writing file! - Time Parallel\n");
		exit(1);
	}
	fprintf(fptr, "%d,%f\n",size,time);
	fclose(fptr);
}

void array_print(int *array, int size) {
	int i;
	for (int i = 0; i < size; i++) {
		printf("%d\n",array[i]);
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quicksort(int *array, int size) {
	/*
	pragma omp parallel: needed to create the parallel threads executing the tasks
	pragma omp single: one thread executes the initial quicksort call
	*/
	
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			quicksort_small(array, size);
		}
	}
}

void quicksort_small(int *array, int size) {
	if (size < 2) return;
	int pivot = array[size / 2];
	
	int i,j;

	for (i = 0, j = size - 1;; i++, j--) {
		while (array[i] < pivot) i++;
		while (array[j] > pivot) j--;
		if (i>=j) break;
		swap(&array[i],&array[j]);	
			
	}

	/*
	If the array size is smaller than the threshold - 1,000, then the quicksort called will execute in serial.
	Otherwise, a task is created to handle the quicksort
	*/
	
	if (size - i < 1000) {
		quicksort_small(array,i);
		quicksort_small(array+i, size - i);
	} else {
		#pragma omp task 	
		{ quicksort_small(array, i); }
		
		quicksort_small(array + i, size - i); 
	}
}

int main() {
	int size;
	int *array = read_input(&size);
	double time = omp_get_wtime();
	quicksort(array,size);
	time = omp_get_wtime() - time;
	printf("Execution time: %f\n", time);
	//write_time(size,time);
	write_output(array, size);
	return 0;
}