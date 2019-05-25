#include <stdio.h>
#include "../global.h"
#include "../helper.h"

EM_PORT_API(void) insertionSort(int *ary, int size) {
    for (int i = 0; i < size; i++) {
        int cur = ary[i];
        int j = i - 1;
        int changedIndex = 0;
        for (; j >= 0; j--) {
            if (cur < ary[j]) {
                ary[j + 1] = ary[j];
                changedIndex = j;
            } else {
                break;
            }
        }
        if (changedIndex > 0) {
            ary[changedIndex] = cur;
        }
    }
}

EM_PORT_API(void) insertionSortHandsome(int *ary, int size) {
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        if (ary[i] < ary[j]) {
            int cur = ary[i];
            while (cur < ary[j] && j >= 0) {
                ary[j + 1] = ary[j];
                j--;
            }
            ary[j + 1] = cur;
        }
    }
}

EM_PORT_API(void) shellSort(int *ary, int size) {
    int interval = 1;
    while (interval < size / 3) {
        interval = interval * 3 + 1;
    }
    while (interval >= 1) {
        for (int i = interval; i < size; i++) {
            int cur = ary[i];
            if (cur < ary[i - interval]) {
                int j = i;
                for (; cur < ary[j - interval] && j >= interval; j -= interval) {
                    ary[j] = ary[j - interval];
                }
                ary[j] = cur;
            }
        }
        interval = (interval - 1) / 3;
    }
}

void quickSortInner(int *ary, int start, int end) {
    if (start >= end) return;
    int low = start;
    int high = end;
    int pivotPoint = ary[start];
    while (low < high) {
        while (ary[high] >= pivotPoint && low < high) {
            high--;
        }
        ary[low] = ary[high];
        while (ary[low] <= pivotPoint && low < high) {
            low++;
        }
        ary[high] = ary[low];
    }
    ary[low] = pivotPoint;
    quickSortInner(ary, start, low - 1);
    quickSortInner(ary, low + 1, end);
}

EM_PORT_API(void) quickSort(int *ary, int size) {
    quickSortInner(ary, 0, size - 1);
}

EM_PORT_API(void) selectionSort(int *ary, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (ary[minIndex] > ary[j]) {
                minIndex = j;
            }
        }
        swap(&ary[minIndex], &ary[i]);
    }
}

void heapFallSortInner(int *ary, int parent, int size) {
    int childIndex = parent * 2 + 1;
    int cur = ary[parent];
    while (childIndex < size) {
        if (childIndex + 1 < size && ary[childIndex + 1] > ary[childIndex]) {
            childIndex++;
        }
        if (cur >= ary[childIndex]) break;
        ary[parent] = ary[childIndex];
        parent = childIndex;
        childIndex = childIndex * 2 + 1;
    }
    ary[parent] = cur;
}

EM_PORT_API(void) heapSort(int *ary, int size) {
    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapFallSortInner(ary, i, size);
    }
    for (int i = size - 1; i > 0; i--) {
        swap(ary, &ary[i]);
        heapFallSortInner(ary, 0, i);
    }
}

int main(void) {
    int i[] = {1, 2, 6, 8, 9, 7, 4, 3, 5};
    heapSort(i, 9);
    printAry(i, 9);
    return 0;
}
