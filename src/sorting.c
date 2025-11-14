#include <stdio.h>
#include <string.h>
#include "student.h"
#include "sorting.h"

void displayStudentsSorted(int sortBy) {
    Student temp[MAX_STUDENTS];
    int count = 0;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            temp[count++] = students[i];
        }
    }

    if (sortBy == 1) {
        for (int i = 0; i < count - 1; i++)
            for (int j = i + 1; j < count; j++)
                if (temp[i].id > temp[j].id) {
                    Student t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
        printf("\n--- SORTED BY ID ---\n");
    }
    else {
        for (int i = 0; i < count - 1; i++)
            for (int j = i + 1; j < count; j++)
                if (temp[i].mark < temp[j].mark) {
                    Student t = temp[i];
                    temp[i] = temp[j];
                    temp[j] = t;
                }
        printf("\n--- SORTED BY MARK ---\n");
    }

    printf("%-8s %-20s %-25s %-8s\n", "ID", "Name", "Programme", "Mark");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-25s %-8.1f\n",
            temp[i].id, temp[i].name, temp[i].programme, temp[i].mark);
    }
}