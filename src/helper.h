void printAry(int *ary, int size) {
    for (int i = 0; i < size; i++) {
        printf(" %d ", ary[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    if (a == b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}