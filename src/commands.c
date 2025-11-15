#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h" 
#include "../include/utils.h"
#include "../include/commands.h"
#include "../include/sorting.h" // Add this if not already included
#define FILENAME "P15_7_CMS.txt"

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nDatabase full! Cannot add more students.\n");
        return;
    }

    Student newStudent;
    newStudent.active = 1;

    printf("\n--- ADD NEW STUDENT ---\n");
    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);
    clearInputBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id && students[i].active) {
            printf("\nStudent ID already exists!\n");
            return;
        }
    }

    printf("Enter student name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;

    printf("Enter programme: ");
    fgets(newStudent.programme, MAX_PROGRAMME, stdin);
    newStudent.programme[strcspn(newStudent.programme, "\n")] = 0;

    printf("Enter mark: ");
    scanf("%f", &newStudent.mark);
    clearInputBuffer();

    students[studentCount++] = newStudent;

    FILE* fp = fopen(FILENAME, "a");
    if (fp) {
        fprintf(fp, "\n%d\t%s\t%s\t%.1f",
            newStudent.id, newStudent.name,
            newStudent.programme, newStudent.mark);
        fclose(fp);
        printf("\nStudent added and saved!\n");
    }
    else {
        printf("\nStudent added but failed to save to file!\n");
    }
}

void viewAllStudents() {
    if (studentCount == 0) {
        printf("\nNo students loaded!\n");
        return;
    }

    printf("\n--- ALL STUDENTS ---\n");
    printf("%-8s %-20s %-25s %-8s\n", "ID", "Name", "Programme", "Mark");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            printf("%-8d %-20s %-25s %-8.1f\n",
                students[i].id,
                students[i].name,
                students[i].programme,
                students[i].mark);
        }
    }
}

void searchStudent() {
    int searchId;
    printf("\n--- SEARCH STUDENT ---\nEnter ID: ");
    scanf("%d", &searchId);
    clearInputBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId && students[i].active) {
            printf("\nFound!\n");
            printf("ID: %d\nName: %s\nProgramme: %s\nMark: %.1f\n",
                students[i].id, students[i].name, students[i].programme, students[i].mark);
            return;
        }
    }
    printf("\nStudent not found!\n");
}

void updateStudent() {
    printf("\n--- UPDATE STUDENT ---\n");
    printf("Please edit the file manually.\n");
}

void deleteStudent() {
    printf("\n--- DELETE STUDENT ---\n");
    printf("Please edit the file manually.\n");
}

void sortingMenu() {
    int choice;
    while (1) {
        printf("\n--- SORTING OPTIONS ---\n");
        printf("1. SHOW ALL SORT BY ID\n");
        printf("2. SHOW ALL SORT BY MARK\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                displayStudentsSorted(1); // Sort by ID
                break;
            case 2:
                displayStudentsSorted(2); // Sort by Mark
                break;
            case 3:
                return; // Back to main menu
            default:
                printf("\nInvalid choice! Please try again.\n");
                continue;
        }
        break; // Exit the loop after displaying sorted data
    }
}