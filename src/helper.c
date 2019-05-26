#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

void printAry(int *ary, int size) {
    for (int i = 0; i < size; i++) {
        printf(" %d, ", ary[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    if (a == b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void assertAsc(char *msg, long long startTime, int *ary, int size) {
    for (int i = 1; i < size; i++) {
        assert(ary[i - 1] < ary[i]);
    }
    printf("\x1b[36m[%s] success %lld ms\n\x1b[0m", msg, timeInMilliseconds() - startTime);
}

int getRandom(int min, int max) {
    return min + rand() % (max - min);
}

void getRandomArray(int *ary, int size) {
    int tempAry[size];
    for (int i = 0; i < size; i++) {
        tempAry[i] = i;
    }
    int t, i;
    while (size) {
        i = getRandom(0, size--);
        t = tempAry[size];
        ary[size] = tempAry[i];
        tempAry[i] = t;
    }
}

void copyRange(int *fromAry, int *toAry, int fromStart, int toStart, int size, int fromArySize, int toArySize) {
    for (int i = 0; i < size; i++) {
        int fromI = fromStart + i;
        int toI = toStart + i;
        if (fromI >= fromArySize || toI >= toArySize) break;
        toAry[toI] = fromAry[fromI];
    }
}

void copy(int *ary, int *destinationAry, int size) {
    copyRange(ary, destinationAry, 0, 0, size, size, size);
}