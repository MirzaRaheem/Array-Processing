#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define numOfSubjects 3
#define numOfStudents 3

// Define the student struct
struct Student {
    char FirstName[50];
    char LastName[50];
    int StudentID;
    float SubjectMarks[numOfSubjects];
    int AggregateMarks;
    char Grade[12];
};

// Function prototypes
void inputStudentData(struct Student *student);
void calculateAggregateAndGrade(struct Student *student);
void displayStudentData(struct Student student);
int getMenuChoice();
void enrolStudent(struct Student *students, int numStudents);
void searchUpdate(struct Student *students, int numStudents);
void topStudents(struct Student *students, int numStudents);
int searchByStudentID(struct Student *students, int numStudents, int id);
int searchByLastName(struct Student *students, int numStudents, const char *lastName);
void exitProgram();

int main() {
    struct Student students[numOfStudents];

    int choice;
    for (int i = 0; i < numOfStudents; i++) {
        printf("\nStudent %d:\n", i + 1);
        inputStudentData(&students[i]);
        calculateAggregateAndGrade(&students[i]);
    }

    do {
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                enrolStudent(students, numOfStudents);
                break;
            case 2:
                searchUpdate(students, numOfStudents);
                break;
            case 3:
                topStudents(students, numOfStudents);
                break;
            case 4:
                exitProgram();
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

void inputStudentData(struct Student *student) {
    printf("Enter First Name: ");
    scanf("%s", student->FirstName);

    printf("Enter Last Name: ");
    scanf("%s", student->LastName);

    printf("Enter Student ID: ");
    scanf("%d", &student->StudentID);

    for (int i = 0; i < numOfSubjects; i++) {
        printf("Do you want to input Subject %d Marks? (Yes/No): ", i + 1);
        char inputChoice[5];
        scanf("%s", inputChoice);

        if (strcasecmp(inputChoice, "Yes") == 0) {
            printf("Enter Subject %d Marks: ", i + 1);
            scanf("%f", &student->SubjectMarks[i]);
        } else {
            student->SubjectMarks[i] = -1;
        }
    }
}

void calculateAggregateAndGrade(struct Student *student) {
    float totalMarks = 0.0;
    for (int i = 0; i < numOfSubjects; i++) {
        if (student->SubjectMarks[i] >= 0) {
            totalMarks += student->SubjectMarks[i];
        }
    }
    student->AggregateMarks = (int)(totalMarks / numOfSubjects);

    if (totalMarks == -numOfSubjects) {
        strcpy(student->Grade, "undefined");
    } else if (student->AggregateMarks >= 85) {
        strcpy(student->Grade, "HD");
    } else if (student->AggregateMarks >= 75) {
        strcpy(student->Grade, "D");
    } else if (student->AggregateMarks >= 65) {
        strcpy(student->Grade, "C");
    } else if (student->AggregateMarks >= 50) {
        strcpy(student->Grade, "P");
    } else {
        strcpy(student->Grade, "F");
    }
}

void displayStudentData(struct Student student) {
    printf("\nStudent ID: %d\n", student.StudentID);
    printf("First Name: %s\n", student.FirstName);
    printf("Last Name: %s\n", student.LastName);
    printf("Aggregate Marks: %d\n", student.AggregateMarks);
    printf("Grade: %s\n", student.Grade);
    printf("Subject Marks: ");
    for (int i = 0; i < numOfSubjects; i++) {
        printf("%.2f ", student.SubjectMarks[i]);
    }
    printf("\n");
}

int getMenuChoice() {
    int choice;
    printf("\nMenu:\n");
    printf("1. Enroll a student\n");
    printf("2. Search and Update student data\n");
    printf("3. Display top students\n");
    printf("4. Exit program\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void enrolStudent(struct Student *students, int numStudents) {
    int studentID;
    printf("Enter Student ID to enroll: ");
    scanf("%d", &studentID);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].StudentID == studentID) {
            printf("Student with ID %d already exists.\n", studentID);
            return;
        }
    }

    for (int i = 0; i < numStudents; i++) {
        if (students[i].StudentID == -1) {
            students[i].StudentID = studentID;
            printf("Enrollment completed for Student ID: %d\n", studentID);
            inputStudentData(&students[i]);
            calculateAggregateAndGrade(&students[i]);
            return;
        }
    }

    printf("No available slots for new students.\n");
}

void searchUpdate(struct Student *students, int numStudents) {
    int choice;
    printf("Search by:\n");
    printf("1. Student ID\n");
    printf("2. Last Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int studentID;
        printf("Enter Student ID to search: ");
        scanf("%d", &studentID);

        int studentIndex = searchByStudentID(students, numStudents, studentID);

        if (studentIndex == -1) {
            printf("Student with ID %d not found.\n", studentID);
            return;
        }

        struct Student *student = &students[studentIndex];
        displayStudentData(*student);

        char updateChoice[5];
        printf("Do you want to update this student's data? (Yes/No): ");
        scanf("%s", updateChoice);

        if (strcasecmp(updateChoice, "Yes") == 0) {
            printf("Enter updated data:\n");
            inputStudentData(student);
            calculateAggregateAndGrade(student);
            printf("Student data updated.\n");
        }
    } else if (choice == 2) {
        char lastName[50];
        printf("Enter Last Name to search: ");
        scanf("%s", lastName);

        int studentIndex = searchByLastName(students, numStudents, lastName);

        if (studentIndex == -1) {
            printf("Student with Last Name %s not found.\n", lastName);
            return;
        }

        struct Student *student = &students[studentIndex];
        displayStudentData(*student);

        char updateChoice[5];
        printf("Do you want to update this student's data? (Yes/No): ");
        scanf("%s", updateChoice);

        if (strcasecmp(updateChoice, "Yes") == 0) {
            printf("Enter updated data:\n");
            inputStudentData(student);
            calculateAggregateAndGrade(student);
            printf("Student data updated.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
}

void topStudents(struct Student *students, int numStudents) {
    int maxAggregateMarks = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].AggregateMarks > maxAggregateMarks) {
            maxAggregateMarks = students[i].AggregateMarks;
        }
    }

    printf("Top Students:\n");
    for (int i = 0; i < numStudents; i++) {
        if (students[i].AggregateMarks == maxAggregateMarks) {
            displayStudentData(students[i]);
        }
    }
}

int searchByStudentID(struct Student *students, int numStudents, int id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].StudentID == id) {
            return i;
        }
    }
    return -1; // Student not found
}

int searchByLastName(struct Student *students, int numStudents, const char *lastName) {
    for (int i = 0; i < numStudents; i++) {
        if (strcasecmp(students[i].LastName, lastName) == 0) {
            return i;
        }
    }
    return -1; // Student not found
}

void exitProgram() {
    printf("Exiting the program.\n");
    exit(0);
}
