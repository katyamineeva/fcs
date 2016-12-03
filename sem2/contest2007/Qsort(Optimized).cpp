#define MagicConst 10
#include <stdio.h>
#include <stdlib.h>

int n;

void Swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


int ChoosePivot(int* a, int x, int y, int z) {
    if (a[x] <= a[y] && a[y] <= a[z]) {
        return y;
    }
    if (a[y] <= a[z] && a[z] <= a[x]) {
        return z;
    }
    return x;
}


void InsertionSort(int* a, int left, int right) {
    int i, ind;
    for (i = left + 1; i <= right; ++i) {
        ind = i;
        while (ind > left && a[ind] < a[ind - 1]) {
            Swap(&a[ind], &a[ind - 1]);
            --ind;
        }
    }
}


int Partition(int* a, int left, int right, int pivot) {
    Swap(&a[right], &a[pivot]);
    int PivotInd = right;
    --right;
    int PivotValue = a[PivotInd];

    while (left < right) {
        while (a[left] <= PivotValue && left < right) {
            ++left;
        }
        while (a[right] >= PivotValue && left < right) {
            --right;
        }
        Swap(&a[left], &a[right]);

        if (left + 1 == right) {
            break;
        }
        if (right - left > 1) {
            ++left;
            --right;
        }
    }

    if (a[right] >= PivotValue) {
        Swap(&a[right], &a[PivotInd]);
        PivotInd = right;
    } else {
        Swap(&a[right + 1], &a[PivotInd]);
        PivotInd = right + 1;
    }
    return PivotInd;
}


void QuickSort(int* a, int left, int right) {
    if (right - left > MagicConst) {
        int pivot = ChoosePivot(a, left, right, (left + right) / 2);
        int m = Partition(a, left, right, pivot);
        QuickSort(a, left, m - 1);
        QuickSort(a, m + 1, right);
    }

    if ((right - left <= MagicConst) && (right - left > 0)) {
        InsertionSort(a, left, right);
    }
}


int* ReadData() {
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &n);


    int* a = static_cast<int*>(malloc(n * sizeof(int)));
    int i;
    for (i = 0; i < n; ++i) {
        fscanf(input, "%d", &a[i]);
    }
    fclose(input);
    return a;
}


void WriteData(int* a) {
    FILE* output = fopen("output.txt", "w");

    int i;
    for (i = 0; i < n; ++i) {
        fprintf(output, "%d ", a[i]);
    }
    fclose(output);
}

void PrintData(int* a) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main() {
    int* a = ReadData();
    QuickSort(a, 0, n - 1);
    WriteData(a);
    free(a);
    return 0;
}
