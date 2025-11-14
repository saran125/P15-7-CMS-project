#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "database.h"
#include "commands.h"
#include "sorting.h"
#include "utils.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

void displayMenu();

int main() {
    // Declaration text
    printf("Declaration\n");
    printf("===========\n\n");
    printf("SIT's policy on copying does not allow the students to copy source code as well as assessment solutions\n");
    printf("from another person AI or other places. It is the students' responsibility to guarantee that their\n");
    printf("assessment solutions are their own work...\n\n");

    printf("Press Enter to continue...\n");
    getchar();

    int choice;

    loadFromFile();

    printf("\n===========================================\n");
    printf("   COURSE MANAGEMENT SYSTEM (CMS)\n");
    printf("   Database: P15-7-CMS\n");
    printf("   Table: StudentRecords\n");
    printf("===========================================\n");

    while (1) {
        displayMenu();
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: openDatabase(); break;
        case 2: addStudent(); break;
        case 3: viewAllStudents(); break;
        case 4: searchStudent(); break;
        case 5: updateStudent(); break;
        case 6: deleteStudent(); break;
        case 7:
            saveToFile();
            printf("\nData saved successfully!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void displayMenu() {
    printf("\n-------------------------------------------\n");
    printf("MAIN MENU\n");
    printf("-------------------------------------------\n");
    printf("1. Open Database\n");
    printf("2. Add New Student\n");
    printf("3. View All Students\n");
    printf("4. Search Student\n");
    printf("5. Update Student Record\n");
    printf("6. Delete Student\n");
    printf("7. Save and Exit\n");
    printf("-------------------------------------------\n");
}