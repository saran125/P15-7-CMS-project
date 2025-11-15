#include <stdio.h>
#include "../include/utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getNextId() {
    return 2300000;
}