#include <stdio.h>
#include <stdlib.h>
#include "../include/student.h"
#include "../include/database.h"
#include "../include/commands.h"
#include "../include/sorting.h"
#include "../include/utils.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

void displayMenu();

int main() {
    // Declaration text
    printf("Declaration\n");
    printf("===========\n\n");
    printf("SIT's policy on copying does not allow the students to copy source code as well as assessment solutions\n");
    printf("from another person AI or other places. It is the students' responsibility to guarantee that their\n");
    printf("assessment solutions are their own work. Meanwhile, the students must also ensure that their work is\n");
    printf("not accessible by others. Where such plagiarism is detected, both of the assessments involved will\n");
    printf("receive ZERO mark.\n\n");
    printf("We hereby declare that:\n");
    printf("• We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("• We did not copy any code from others or from other places.\n");
    printf("• We did not share our codes with others or upload to any other places for public access and will\n");
    printf("  not do that in the future.\n");
    printf("• We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("• We agree that we will not disclose any information or material of the group project to others or\n");
    printf("  upload to any other places for public access.\n");
    printf("• We agree that we did not copy any code directly from AI generated sources\n\n");
    printf("Declared by: P15-7\n");
    printf("Team members:\n");
    printf("1. Farid\n");
    printf("2. Lucas\n");
    printf("3. Linus\n");
    printf("4. Jazton\n");
    printf("5. Saran\n");
    printf("Date: 25th Nov 2025\n\n");
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
        case 3: 
            viewAllStudents(); 
            sortingMenu(); // Call sorting menu after viewing all students
            break;
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