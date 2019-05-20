#include <stdio.h>
#include <string.h>
#include "../global.h"


int main() {
    printf("C{enter main}\n");
    void readFile(const char *fileName);
    void writeFile(const char *fileName, const char *data);
    readFile("/fs/data/data1.txt");
    writeFile("/fs/data/data2.txt", "静夜思\n"); // 替换文件内容，刷新即会失效
    readFile("/fs/data/data2.txt");
    printf("\nC{exit main}\n");
    return 0;
}

void readFile(const char *fileName) {
    FILE *fp = fopen(fileName, "rt");
    if (fp) {
        while (!feof(fp)) {
            char c = fgetc(fp);
            if (c != EOF) {
                putchar(c);
            }
        }
        fclose(fp);
    }
}

void writeFile(const char *fileName, const char *data) {
    FILE* fp = fopen(fileName, "wt");
    if (fp) {
        fprintf(fp, "%s", data);
        fclose(fp);
    }
}

