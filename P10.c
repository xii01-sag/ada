#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    while (1)
    {
        while (i <= high && arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i < j)
            swap(&arr[i], &arr[j]);
        else
            break;
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main()
{
    FILE *fp;
    fp = fopen("quick_data.txt", "w");
    if (fp == NULL)
    {
        return 1;
    }

    int n, i;
    clock_t start, end;
    double time_taken;

    printf("\nQuick Sort Performance Analysis\n");
    printf("--------------------------------------\n");
    srand(time(NULL));

    for (n = 5000; n <= 50000; n += 5000)
    {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL)
        {
            fclose(fp);
            return 1;
        }

        for (i = 0; i < n; i++)
        {
            arr[i] = rand() % 100000;
        }

        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("n = %d \t Time = %f seconds\n", n, time_taken);

        fprintf(fp, "%d %f\n", n, time_taken);
        free(arr);
    }
    fclose(fp);

    FILE *gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot != NULL)
    {
        fprintf(gnuplot, "set title 'Quick Sort Time Complexity'\n");
        fprintf(gnuplot, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'quick_data.txt' using 1:2 with linespoints linewidth 2 title 'Quick Sort'\n");
        pclose(gnuplot);
    }

    return 0;
}
