#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define MAX_PROGRAMME 50
#define FILENAME "P15_7_CMS.txt"

typedef struct {
    int id;
    char name[MAX_NAME];
    char programme[MAX_PROGRAMME];
    float mark;
    int active;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void displayMenu();
void openDatabase();
void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void clearInputBuffer();
int getNextId();
void sortStudentsById();
void sortStudentsByMark();
void displayStudentsSorted(int sortBy); // 1 for ID, 2 for Mark

int main() {
    // Display declaration
    printf("Declaration\n");
    printf("===========\n\n");
    printf("SIT's policy on copying does not allow the students to copy source code as well as assessment solutions\n");
    printf("from another person AI or other places. It is the students' responsibility to guarantee that their\n");
    printf("assessment solutions are their own work. Meanwhile, the students must also ensure that their work is\n");
    printf("not accessible by others. Where such plagiarism is detected, both of the assessments involved will\n");
    printf("receive ZERO mark.\n\n");
    printf("We hereby declare that:\n");
    printf("* We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("* We did not copy any code from others or from other places.\n");
    printf("* We did not share our codes with others or upload to any other places for public access and will\n");
    printf("  not do that in the future.\n");
    printf("* We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("* We agree that we will not disclose any information or material of the group project to others or\n");
    printf("  upload to any other places for public access.\n");
    printf("* We agree that we did not copy any code directly from AI generated sources\n\n");
    printf("Declared by: P15-7\n");
    printf("Team members:\n");
    printf("1. Farid\n");
    printf("2. Lucas\n");
    printf("3. Linus\n");
    printf("4. Jazton\n");
    printf("5. Saran\n");
    printf("Date: 25th Nov 2025\n\n");
    printf("Press Enter to continue...\n");
    getchar(); // Wait for user to press Enter
    
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
            case 1:
                openDatabase();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                viewAllStudents();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                saveToFile();
                printf("\nData saved successfully!\n");
                printf("\nThank you for using Course Management System!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
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

void openDatabase() {
    printf("\n--- OPEN DATABASE ---\n");
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Error: Cannot open database file '%s'\n", FILENAME);
        printf("Please make sure the file exists in the current directory.\n");
        return;
    }
    
    printf("Database file '%s' opened successfully!\n", FILENAME);
    printf("Contents:\n");
    printf("==========================================\n");
    
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    
    fclose(fp);
    printf("\n==========================================\n");
    printf("Database file closed.\n");
}

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
    
    // Check if ID already exists
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id && students[i].active) {
            printf("\nStudent with ID %d already exists!\n", newStudent.id);
            return;
        }
    }
    
    printf("Enter student name: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    printf("Enter programme: ");
    fgets(newStudent.programme, MAX_PROGRAMME, stdin);
    newStudent.programme[strcspn(newStudent.programme, "\n")] = 0;
    
    printf("Enter mark: ");
    scanf("%f", &newStudent.mark);
    clearInputBuffer();
    
    students[studentCount++] = newStudent;
    
    // Save the new student to the text file
    FILE *fp = fopen(FILENAME, "a");
    if (fp != NULL) {
        // Add a newline first to ensure we start on a new line
        fprintf(fp, "\n%d\t%s\t%s\t%.1f", 
               newStudent.id, newStudent.name, newStudent.programme, newStudent.mark);
        fclose(fp);
        printf("\nStudent added successfully and saved to database!\n");
    } else {
        printf("\nStudent added to memory but failed to save to file!\n");
    }
    
    printf("ID: %d | Name: %s | Programme: %s | Mark: %.1f\n", 
           newStudent.id, newStudent.name, newStudent.programme, newStudent.mark);
}

void viewAllStudents() {
    if (studentCount == 0) {
        printf("\nNo students in database! Use option 1 to load database first.\n");
        return;
    }
    
    printf("\n--- ALL STUDENTS ---\n");
    printf("Database Name: P15-7-CMS\n");
    printf("Authors: P15-7(Farid, Lucas, Linus, Jazton, Saran)\n");
    printf("Table Name: StudentRecords\n");
    printf("%-8s %-20s %-25s %-8s\n", "ID", "Name", "Programme", "Mark");
    printf("---------------------------------------------------------------\n");
    
    int activeCount = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            printf("%-8d %-20s %-25s %-8.1f\n", 
                   students[i].id, 
                   students[i].name, 
                   students[i].programme, 
                   students[i].mark);
            activeCount++;
        }
    }
    
    printf("\nTotal students: %d\n", activeCount);
    
    // Show sorting options
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

void searchStudent() {
    int searchId;
    printf("\n--- SEARCH STUDENT ---\n");
    printf("Enter student ID: ");
    scanf("%d", &searchId);
    clearInputBuffer();
    
    FILE *fp = fopen("P15_7_CMS.txt", "r");
    if (fp == NULL) {
        printf("\nNo data file found.\n");
        return;
    }
    
    char line[256];
    int found = 0;
    
    // Skip header lines
    for (int i = 0; i < 4; i++) {
        fgets(line, sizeof(line), fp);
    }
    
    // Search for student
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char name[MAX_NAME], programme[MAX_PROGRAMME];
        float mark;
        
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        if (sscanf(line, "%d\t%49[^\t]\t%49[^\t]\t%f", &id, name, programme, &mark) == 4) {
            if (id == searchId) {
                printf("\nStudent Found!\n");
                printf("-------------------------------------------\n");
                printf("ID: %d\n", id);
                printf("Name: %s\n", name);
                printf("Programme: %s\n", programme);
                printf("Mark: %.1f\n", mark);
                printf("-------------------------------------------\n");
                found = 1;
                break;
            }
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("\nStudent with ID %d not found!\n", searchId);
    }
}

void updateStudent() {
    printf("\n--- UPDATE STUDENT ---\n");
    printf("Note: Please use external text editor to modify P15_7_CMS.txt\n");
    printf("Current file format:\n");
    printf("ID<TAB>Name<TAB>Programme<TAB>Mark\n");
}

void deleteStudent() {
    printf("\n--- DELETE STUDENT ---\n");
    printf("Note: Please use external text editor to modify P15_7_CMS.txt\n");
    printf("Remove the corresponding line from the file.\n");
}

void saveToFile() {
    // File is already in the correct format, no need to rewrite
    printf("\nFile is maintained in text format: %s\n", FILENAME);
}

void loadFromFile() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\nNo existing database found.\n");
        studentCount = 0;
        return;
    }
    
    char line[256];
    studentCount = 0;
    
    // Skip header lines (first 4 lines)
    for (int i = 0; i < 4; i++) {
        if (!fgets(line, sizeof(line), fp)) {
            fclose(fp);
            printf("\nInvalid file format.\n");
            return;
        }
    }
    
    // Load actual student data into memory
    while (fgets(line, sizeof(line), fp) && studentCount < MAX_STUDENTS) {
        int id;
        char name[MAX_NAME], programme[MAX_PROGRAMME];
        float mark;
        char temp[256];
        
        // Parse the tab-separated line
        strcpy(temp, line);
        char *token = strtok(temp, "\t");
        if (token != NULL) {
            id = atoi(token);
            
            token = strtok(NULL, "\t");
            if (token != NULL) {
                strncpy(name, token, MAX_NAME - 1);
                name[MAX_NAME - 1] = '\0';
                
                token = strtok(NULL, "\t");
                if (token != NULL) {
                    strncpy(programme, token, MAX_PROGRAMME - 1);
                    programme[MAX_PROGRAMME - 1] = '\0';
                    
                    token = strtok(NULL, "\t");
                    if (token != NULL) {
                        mark = atof(token);
                        
                        // Store in students array
                        students[studentCount].id = id;
                        strncpy(students[studentCount].name, name, MAX_NAME - 1);
                        students[studentCount].name[MAX_NAME - 1] = '\0';
                        strncpy(students[studentCount].programme, programme, MAX_PROGRAMME - 1);
                        students[studentCount].programme[MAX_PROGRAMME - 1] = '\0';
                        students[studentCount].mark = mark;
                        students[studentCount].active = 1;
                        studentCount++;
                    }
                }
            }
        }
    }
    
    fclose(fp);
    printf("\nDatabase loaded: %d student records found.\n", studentCount);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getNextId() {
    // Simple implementation - you would normally check existing IDs
    return 2300000 + studentCount + 1;
}

void displayStudentsSorted(int sortBy) {
    // Create a copy of students array for sorting
    Student tempStudents[MAX_STUDENTS];
    int activeCount = 0;
    
    // Copy active students to temp array
    for (int i = 0; i < studentCount; i++) {
        if (students[i].active) {
            tempStudents[activeCount] = students[i];
            activeCount++;
        }
    }
    
    // Sort the temp array based on choice
    if (sortBy == 1) {
        // Sort by ID (ascending)
        for (int i = 0; i < activeCount - 1; i++) {
            for (int j = i + 1; j < activeCount; j++) {
                if (tempStudents[i].id > tempStudents[j].id) {
                    Student temp = tempStudents[i];
                    tempStudents[i] = tempStudents[j];
                    tempStudents[j] = temp;
                }
            }
        }
        printf("\n--- ALL STUDENTS SORTED BY ID ---\n");
    } else if (sortBy == 2) {
        // Sort by Mark (descending - highest first)
        for (int i = 0; i < activeCount - 1; i++) {
            for (int j = i + 1; j < activeCount; j++) {
                if (tempStudents[i].mark < tempStudents[j].mark) {
                    Student temp = tempStudents[i];
                    tempStudents[i] = tempStudents[j];
                    tempStudents[j] = temp;
                }
            }
        }
        printf("\n--- ALL STUDENTS SORTED BY MARK ---\n");
    }
    
    // Display sorted students
    printf("Database Name: P15-7-CMS\n");
    printf("Authors: P15-7(Farid, Lucas, Linus, Jazton, Saran)\n");
    printf("Table Name: StudentRecords\n");
    printf("%-8s %-20s %-25s %-8s\n", "ID", "Name", "Programme", "Mark");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < activeCount; i++) {
        printf("%-8d %-20s %-25s %-8.1f\n", 
               tempStudents[i].id, 
               tempStudents[i].name, 
               tempStudents[i].programme, 
               tempStudents[i].mark);
    }
    
    printf("\nTotal students: %d\n", activeCount);
}