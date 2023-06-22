#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "session.h"
#include "tutor.h"
#include "student.h"
#include "constants.h"
#include "constants.h"

// Declare global variables
struct Session sessions[MAX_SESSIONS]; // Array to store session records
struct Tutor tutors[MAX_TUTORS]; // Array to store tutor records
struct Student students[MAX_STUDENTS]; // Array to store student records
int tutorCount = 0; // Count of tutors in the system
int sessionCount = 0; // Count of sessions in the system
int studentCount = 0; // Count of students in the system

int userType; // Global variable to store the user's role

/**
 * Initializes the data by adding pre-defined tutor and session records.
 */
void initializeData() {
    FILE *tutorsFile = fopen("tutors.txt", "r");
    if (tutorsFile == NULL) {
        printf("Failed to open tutors.txt file.\n");
        exit(1);
    }

    FILE *sessionsFile = fopen("sessions.txt", "r");
    if (sessionsFile == NULL) {
        printf("Failed to open sessions.txt file.\n");
        exit(1);
    }

    char line[100];

    // Read tutors data
    while (fgets(line, sizeof(line), tutorsFile) != NULL) {
        char *code = strtok(line, ",");
        char *name = strtok(NULL, ",");
        char *title = strtok(NULL, ",");
        char *password = strtok(NULL, "\n");

        strcpy(tutors[tutorCount].id, code);
        strcpy(tutors[tutorCount].name, name);
        strcpy(tutors[tutorCount].title, title);
        strcpy(tutors[tutorCount].password, password);

        tutorCount++;
    }

    // Read sessions data
    while (fgets(line, sizeof(line), sessionsFile) != NULL) {
        char *code = strtok(line, ",");
        char *title = strtok(NULL, ",");
        char *day = strtok(NULL, ",");
        char *startTime = strtok(NULL, ",");
        char *location = strtok(NULL, ",");
        char *tutorCode = strtok(NULL, "\n");

        strcpy(sessions[sessionCount].code, code);
        strcpy(sessions[sessionCount].title, title);
        strcpy(sessions[sessionCount].day, day);
        strcpy(sessions[sessionCount].start_time, startTime);
        strcpy(sessions[sessionCount].location, location);
        strcpy(sessions[sessionCount].tutor_code, tutorCode);

        sessionCount++;
    }

    fclose(tutorsFile);
    fclose(sessionsFile);
}
void displayAdminMenu() {
    printf("Admin Menu\n");
    printf("1. Add Tutor\n");
    printf("2. Add Session\n");
    printf("3. Register Student\n");
    printf("4. Enroll Student into a Session\n");
    printf("5. List Sessions and Students\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
}

void displayTutorMenu() {
    printf("Tutor Menu\n");
    printf("1. List Assigned Sessions\n");
    printf("2. Logout\n");
    printf("Enter your choice: ");
}

void displayStudentMenu() {
    printf("Student Menu\n");
    printf("1. List Assigned Sessions\n");
    printf("2. Enroll in Session\n");
    printf("3. Logout\n");
    printf("Enter your choice: ");
}


void loginAsStudent() {
    char id[100];
    char password[100];
    int choice;

    printf("Enter your ID: ");
    scanf("%s", id);
    printf("Enter your password: ");
    scanf("%s", password);

    // Validate the login credentials
    int isValidLogin = 0;
    struct Student* loggedInStudent;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0 && strcmp(students[i].password, password) == 0) {
            isValidLogin = 1;
            loggedInStudent = &students[i];
            break;
        }
    }

    if (!isValidLogin) {
        printf("Invalid login credentials.\n");
        return;
    }

    do {
        displayStudentMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listAssignedSessionsForStudent(*loggedInStudent);
                break;
            case 2:
                enrollInSession(loggedInStudent, sessionCount, sessions);
                break;
            case 3:
                printf("Logged out as Student.\n");
                userType = 0; // Set the user type to 0 to return to the main menu
                break; // Break from the switch statement to go back to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 3);
}
void trimString(char *str) {
    // Trim leading whitespace
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';  // Null-terminate the trimmed string
}
void loginAsTutor() {
    char code[100];
    char password[100];
    int found = 0;
    int choice;

    printf("Enter tutor ID: ");
    scanf("%s", code);
    printf("Enter password: ");
    scanf("%s", password);
    
    printf("tutorCount %d",tutorCount);
    printf("Successfully Logged in! \n\n ");

    for (int i = 0; i < tutorCount; i++) {
        trimString(tutors[i].password);
        trimString(password);
        // printf("%s %s\n ",tutors[i].id, code);
        // printf("%s %s\n ",tutors[i].password, password);
        if (strcmp(tutors[i].id, code) == 0 && strcmp(tutors[i].password, password) == 0) {
            found = 1;
            
            // printf("found1 %d",found);
            // listAssignedSessions(code); // Call the function to list assigned sessions
            break;
        }
    }

    printf("found %d",found);
    if (found) {
        do {
            displayTutorMenu();
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    listAssignedSessions(code, sessionCount, sessions); // Call the function to list assigned sessions
                    break;
                case 2:
                    printf("Logged out as Tutor.\n");
                    userType = 0; // Set the user type to 0 to return to the main menu
                    break; // Break from the switch statement to go back to the main menu
                // case 3:
                //     printf("Going back to Main Menu.\n");
                //     userType = -1; // Set the user type to -1 to return to the main menu
                //     break; // Break from the switch statement to go back to the main menu
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
            printf("\n");
        } while (choice != 2 && choice != 3);
    } else {
        printf("Invalid tutor code or password. Login failed.\n");
        userType = -1; // Set the user type to -1 to return to the main menu
    }
}

void loginAsAdmin() {
    int choice;
    do {
        displayAdminMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (tutorCount == MAX_TUTORS) {
                    printf("Maximum tutor limit reached!\n");
                    return ;
                }
                struct Tutor t = addTutor();
                 tutors[tutorCount] = t;
                tutorCount++;
                // printf("tutorCount%d %s\n",tutorCount,t.id);
                break;
            case 2:
            if (sessionCount == MAX_SESSIONS) {
                printf("Maximum session limit reached!\n");
                return;
            }
                struct Session s = addSession(tutorCount, tutors);
                sessions[sessionCount] = s;
                sessionCount++;
                break;
            case 3:
                if (studentCount == MAX_STUDENTS) {
                printf("Maximum student limit reached!\n");
                return;
                }
                struct Student st = registerStudent();
                students[studentCount] = st;
                studentCount++;
                break;
            case 4:
                 if (sessionCount == 0) {
                    printf("No sessions available for enrollment!\n");
                    return;
                }
                enrollStudent(sessionCount, sessions, studentCount, students);
                break;
            case 5:
                listSessionsAndStudents(sessionCount, sessions);
                break;
            case 6:
                printf("Logged out as Admin.\n");
                userType = 0; // Set the user type to 0 to return to the main menu
                break; // Break from the switch statement to go back to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 6);
}
int main() {
    initializeData();

    do {
        printf("User Type:\n");
        printf("1. Admin\n");
        printf("2. Tutor\n");
        printf("3. Student\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        switch (userType) {
            case 1:
                loginAsAdmin();
                break;
            case 2:
                loginAsTutor();
                break;
            case 3:
                loginAsStudent();
                break;
            default:
                printf("Invalid user type. Exiting program.\n");
                break;
        }

        printf("\n");
    } while (userType != -1); // Continue looping until user selects to return to main menu

    printf("Returned to Main Menu. Exiting program.\n");

    return 0;
}