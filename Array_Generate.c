#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_generate(int* array, int size) {
	int i;
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		array[i] = ((int)rand()) % 30;
	}
}

int main(int argc, char *argv[]) {
	FILE *fptr;
	fptr = fopen("array_input.txt","w");

	if (fptr == NULL) {
		printf("Error generate array!");
		exit(1);
	}

	int size = atoi(argv[1]);
	int *array = (int *)malloc(sizeof(int)*size);
	array_generate(array,size);

	fprintf(fptr, "%d\n", size);
	int i;
	for (i = 0; i < size; i++) {
		fprintf(fptr, "%d\n", array[i]);
	}
	fclose(fptr);
	return 0;
}