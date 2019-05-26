#include <stdio.h>
#include "./sort.c"

int main(void) {
    srand(time(NULL));
    int SIZE = 30000;
    int ary[SIZE];
    int templateAry[SIZE];
    getRandomArray(templateAry, SIZE);
    long long startTime;

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    insertionSort(ary, SIZE);
    assertAsc("correct for insertionSort", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    insertionSortHandsome(ary, SIZE);
    assertAsc("correct for insertionSortHandsome", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    shellSort(ary, SIZE);
    assertAsc("correct for shellSort", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    quickSort(ary, SIZE);
    assertAsc("correct for quickSort", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    selectionSort(ary, SIZE);
    assertAsc("correct for selectionSort", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    heapSort(ary, SIZE);
    assertAsc("correct for heapSort", startTime, ary, SIZE);

    copy(templateAry, ary, SIZE);
    startTime = timeInMilliseconds();
    mergeSort(ary, SIZE);
    assertAsc("correct for mergeSort", startTime, ary, SIZE);
    return 0;
}