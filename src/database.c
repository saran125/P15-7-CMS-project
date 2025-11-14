#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "utils.h"
#include "database.h"

#define FILENAME "P15_7_CMS.txt"

void openDatabase() {
    printf("\n--- OPEN DATABASE ---\n");
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("Error: Cannot open file '%s'\n", FILENAME);
        return;
    }

    printf("Database file '%s' opened successfully!\n", FILENAME);
    printf("==========================================\n");

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    printf("\n==========================================\nDatabase file closed.\n");
}

void loadFromFile() {
    FILE* fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("\nNo existing database found.\n");
        studentCount = 0;
        return;
    }

    char line[256];
    studentCount = 0;

    for (int i = 0; i < 4; i++) {
        fgets(line, sizeof(line), fp);
    }

    while (fgets(line, sizeof(line), fp) && studentCount < MAX_STUDENTS) {
        int id;
        char name[MAX_NAME_LENGTH], programme[MAX_PROGRAMME];
        float mark;

        if (sscanf(line, "%d\t%49[^\t]\t%49[^\t]\t%f", &id, name, programme, &mark) == 4) {
            students[studentCount].id = id;
            strcpy(students[studentCount].name, name);
            strcpy(students[studentCount].programme, programme);
            students[studentCount].mark = mark;
            students[studentCount].active = 1;
            studentCount++;
        }
    }
    fclose(fp);

    printf("\nDatabase loaded: %d records found.\n", studentCount);
}

void saveToFile() {
    printf("\nFile remains in text format: %s\n", FILENAME);
}