#include <stdio.h>
#include "../global.h"

EM_PORT_API(int) getInt() {
    int int_n = 1;
    int int_n_addr = (int)&int_n;
    printf("int_n addr: %d, HEAP8 addr: %d\n", int_n_addr, int_n_addr >> 2);
    return int_n_addr;
}

double grow = 0.1;
EM_PORT_API(int) getDouble() {
    double db_n = 1.222 + grow++;
    int db_n_addr = (int)&db_n;
    printf("db_n addr: %d, HEAPF64 addr: %d\n", db_n_addr, db_n_addr >> 3);
    return db_n_addr;
}