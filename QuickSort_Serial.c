#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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

	fptr = fopen("sorted_array_serial.c","w");
	if (fptr == NULL) {
		printf("Error writing file! - QuickSort Serial");
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
	fptr = fopen("time_serial.txt","a");
	if (fptr == NULL) {
		printf("Error writing file! - Time Serial\n");
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
	if (size < 2) return;

	int pivot = array[size/2];

	int i,j;
	for (i = 0, j = size - 1;;i++, j--) {
		while (array[i] < pivot) i++;
		while (array[j] > pivot) j--;

		if (i>=j) break;
		swap(&array[i], &array[j]);
	}
	quicksort(array,i);
	quicksort(array+i, size - i);
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