#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void generateRandomNumbers(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

int main() {
    FILE *fp;
    fp = fopen("selection_data.txt", "w");
    if (fp == NULL) {
        return 1;
    }
    
    int n, i;
    clock_t start, end;
    double time_taken;

    printf("\nSelection Sort Performance Analysis\n");
    printf("--------------------------------------\n");
    srand(time(NULL));

    for (n = 5000; n <= 50000; n += 5000) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            fclose(fp);
            return 1;
        }
        generateRandomNumbers(arr, n);
        start = clock();
        selectionSort(arr, n);
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("n = %d \t Time = %f seconds\n", n, time_taken);
        fprintf(fp, "%d %f\n", n, time_taken);
        free(arr);
    }

    fclose(fp);

    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot != NULL) {
        fprintf(gnuplot, "set title 'Selection Sort Time Complexity'\n");
        fprintf(gnuplot, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'selection_data.txt' using 1:2 with linespoints linewidth 2 title 'Selection Sort'\n");
        pclose(gnuplot);
    }

    return 0;
}
