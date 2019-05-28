#include <stdio.h>
#include "../global.h"
#include "../helper.c"

#define highWatermark 100000

EM_PORT_API(void) insertionSort(int *ary, int size) {
    for (int i = 1; i < size; i++) {
        int cur = ary[i];
        int j = i - 1;
        int changedIndex = i;
        for (; j >= 0; j--) {
            if (cur < ary[j]) {
                ary[j + 1] = ary[j];
                changedIndex = j;
            } else {
                break;
            }
        }
        ary[changedIndex] = cur;
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

EM_PORT_API(void) mergeSort(int *ary, int size) {
    for (int i = 2; i / 2 <= size; i *= 2) {
        int half = i / 2;
        for (int j = 0; j < size; j += i) {
            int tempAry[i];
            int index = 0;
            int leftIndex = j;
            int leftIndexEnd = j + half - 1;
            int rightIndex = leftIndexEnd + 1;
            int rightIndexEnd = leftIndex + i - 1;
            while (leftIndex <= leftIndexEnd && rightIndex <= rightIndexEnd && rightIndex < size) {
                tempAry[index++] = ary[leftIndex] <= ary[rightIndex] ? ary[leftIndex++] : ary[rightIndex++];
            }
            while (leftIndex <= leftIndexEnd && leftIndex < size)
                tempAry[index++] = ary[leftIndex++];
            while (rightIndex <= rightIndexEnd && rightIndex < size)
                tempAry[index++] = ary[rightIndex++];
            copyRange(tempAry, ary, 0, j, i, i, size);
        }
    }
}

EM_PORT_API(void) bucketSort(int *ary, int size) {
    int min, max = min = ary[0];
    int i = 0;
    for (; i < size; i++) {
        ary[i] < min && (min = ary[i]);
        ary[i] > max && (max = ary[i]);
    }
    int bucketLen = max - min + 1;
    if (bucketLen > highWatermark) {
        printf("array too long!\n");
        return;
    }
    int *buckets = (int *) calloc(bucketLen, sizeof(int));
    for (i = 0; i < size; i++) {
        buckets[i - min]++;
    }
    int index = 0;
    for (i = 0; i < bucketLen; i++) {
        int num = buckets[i];
        for (int j = 0; j < num; j++) {
            ary[index + j] = i + min;
        }
        index += num;
    }
    free(buckets);
}

typedef struct item { // 使用typedef定义别名之后，可以在定义时不用加上struct
    int value;
    struct item *next;
} LinkItem;
typedef struct list {
    int num;
    struct item *first;
    struct item *last;
} LinkList;

EM_PORT_API(void) radixSort(int *ary, int size) {
    const int radix = 10;
    LinkList *buckets[radix];
    LinkItem *items[size];
    int max = ary[0];
    int i = 0;
    for (; i < radix; i++) { // 初始化每个桶为一个链表
        buckets[i] = (LinkList *) malloc(sizeof(LinkList));
        buckets[i]->first = NULL;
        buckets[i]->last = NULL;
    }
    for (i = 0; i < size; i++) { // 将传入的数组改成链表
        items[i] = (LinkItem *) malloc(sizeof(LinkItem));
        items[i]->value = ary[i];
        items[i]->next = NULL;
        ary[i] > max && (max = ary[i]);
    }
    int temp = max;
    int maxRadix = radix; // 计算所需要的最大基数
    while (temp > radix) {
        temp /= radix;
        maxRadix *= radix;
    }
    int prevRadix = 1;
    while (prevRadix < maxRadix) {
        int curRadix = prevRadix * radix;
        for (i = 0; i < size; i++) { // 元素 至 桶
            LinkItem *item = items[i];
            int bucketIndex = item->value % curRadix / prevRadix;
            if (buckets[bucketIndex]->first == NULL) {
                buckets[bucketIndex]->first = item;
                buckets[bucketIndex]->last = item;
            } else {
                buckets[bucketIndex]->last->next = item;
                buckets[bucketIndex]->last = item;
            }
        }
        int j = 0;
        for (i = 0; i < radix; i++) { // 桶 至 元素
            LinkList *list = buckets[i];
            LinkItem *item = list->first;
            while (item != NULL) {
                items[j++] = item;
                LinkItem *nextItem = item->next;
                item->next = NULL;
                item = nextItem;
            }
            list->first = NULL;
            list->last = NULL;
        }
        prevRadix = curRadix;
    }

    // 复制回数组并释放空间
    for (i = 0; i < size; i++) {
        ary[i] = items[i]->value;
        free(items[i]);
    }
    for (i = 0; i < radix; i++) {
        free(buckets[i]);
    }

}