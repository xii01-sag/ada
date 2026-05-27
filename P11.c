#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    int *temp = (int *)malloc((right - left + 1) * sizeof(int));
    if (temp == NULL) return;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
        
    free(temp);
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    FILE *fp;
    fp = fopen("merge_data.txt", "w");
    if (fp == NULL)
    {
        return 1;
    }

    int n, i;
    clock_t start, end;
    double time_taken;

    printf("\nMerge Sort Performance Analysis\n");
    printf("-----------------------------------\n");
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
        mergeSort(arr, 0, n - 1);
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
        fprintf(gnuplot, "set title 'Merge Sort Time Complexity'\n");
        fprintf(gnuplot, "set xlabel 'Number of Elements (n)'\n");
        fprintf(gnuplot, "set ylabel 'Time Taken (seconds)'\n");
        fprintf(gnuplot, "set grid\n");
        fprintf(gnuplot, "plot 'merge_data.txt' using 1:2 with linespoints linewidth 2 title 'Merge Sort'\n");
        pclose(gnuplot);
    }

    return 0;
}
