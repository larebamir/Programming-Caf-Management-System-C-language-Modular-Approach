
#include <stdio.h>
#include <string.h>
#include "tutor.h"
#include "session.h"
#include "student.h"
#include "constants.h"
#include <stdlib.h> // Include the <stdlib.h> header for malloc

struct Tutor addTutor() {
   

    struct Tutor tutor;
    printf("Enter Tutor ID: ");
    scanf(" %s", tutor.id);
    printf("Enter Tutor Name: ");
    scanf(" %[^\n]", tutor.name);
    printf("Enter Tutor Title: ");
    scanf(" %[^\n]", tutor.title);
    printf("Enter Tutor Password: ");
    scanf(" %[^\n]", tutor.password);

    // tutors[tutorCount] = tutor;
    // tutorCount++;

    printf("Tutor added successfully!\n");
    return tutor;
}

struct Session addSession(int tutorCount, struct Tutor* tutors) {
    struct Session session;
    printf("Enter Session Code: ");
    scanf(" %s", session.code);
    printf("Enter Session Title: ");
    scanf(" %[^\n]", session.title);
    printf("Enter Session Day: ");
    scanf(" %[^\n]", session.day);
    printf("Enter Session Start Time: ");
    scanf(" %[^\n]", session.start_time);
    printf("Enter Session Location: ");
    scanf(" %[^\n]", session.location);

    int tutorIndex = -1;
    char tutorCode[20];
    printf("Available Tutors:\n");
    for (int i = 0; i < tutorCount; i++) {
        printf("%s. %s\n", tutors[i].id, tutors[i].name);
    }

    while (tutorIndex == -1) {
        printf("Enter Tutor Code: ");
        scanf(" %s", tutorCode);

        for (int i = 0; i < tutorCount; i++) {
            if (strcmp(tutors[i].id, tutorCode) == 0) {
                tutorIndex = i;
                break;
            }
        }

        if (tutorIndex == -1) {
            printf("Invalid Tutor Code! Please try again.\n");
        }
    }

    strcpy(session.tutor_code, tutorCode);
    session.numEnrolledStudents = 0; // Initialize numEnrolledStudents to 0

    // sessions[sessionCount] = session;
    // sessionCount++;

    printf("Session added successfully!\n");
    return session;
}

struct Student registerStudent() {
    
    struct Student student;
    printf("Enter Student ID: ");
    scanf(" %s", student.id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", student.name);
    printf("Enter Student Password: ");
    scanf(" %[^\n]", student.password);
    student.numAssignedSessions = 0;
    
    // students[studentCount] = student;
    // studentCount++;

    printf("Student registered successfully!\n");
    return  student;
}

void enrollStudent(int sessionCount, struct Session* sessions, int studentCount, struct Student* students) {
    printf("Available Sessions:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("%s. %s\n", sessions[i].code, sessions[i].title);
    }

    char sessionCode[20];
    printf("Enter Session Code: ");
    scanf(" %s", sessionCode);

    int sessionIndex = -1;
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].code, sessionCode) == 0) {
            sessionIndex = i;
            break;
        }
    }

    if (sessionIndex != -1) {
        printf("Available Students:\n");
        for (int i = 0; i < studentCount; i++) {
            printf("%s. %s\n", students[i].id, students[i].name);
        }

        char studentID[20];
        printf("Enter Student ID: ");
        scanf(" %s", studentID);

        int studentIndex = -1;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].id, studentID) == 0) {
                studentIndex = i;
                break;
            }
        }

        if (studentIndex != -1) {
            struct Session* session = &sessions[sessionIndex];
            struct Student* student = &students[studentIndex];
            
            // Check if the student is already enrolled in the session
            for (int i = 0; i < session->numEnrolledStudents; i++) {
                if (strcmp(session->studentIDs[i], student->id) == 0) {
                    printf("Student '%s' is already enrolled in session '%s'.\n", student->name, session->code);
                    return;
                }
            }
            // printf("Check if the student is already enrolled in the student %d\n",student->numAssignedSessions);
            
            // Check if the student is already enrolled in the session
            for (int i = 0; i < student->numAssignedSessions; i++) {
                if (strcmp(student->assignedSessions[i].code, session->code) == 0) {
                    printf("Student '%s' is already enrolled in session '%s'.\n", student->name, session->code);
                    return;
                }
            }
            // printf("Session '%d' is already full'.\n", session->numEnrolledStudents);
            
            // printf("Check if the student is already enrolled in the student");
            // Enroll the student in the session
            if (session->numEnrolledStudents < MAX_STUDENTS_PER_SESSION) {
                strcpy(session->studentIDs[session->numEnrolledStudents], student->id);
                session->numEnrolledStudents++;
                // printf("Check if the student is already enrolled in the student2"); 
                // Add the session to the student's assigned sessions
                strcpy(student->assignedSessions[student->numAssignedSessions].code, session->code);
                strcpy(student->assignedSessions[student->numAssignedSessions].tutor_code, session->tutor_code);
                strcpy(student->assignedSessions[student->numAssignedSessions].location, session->location);
                student->numAssignedSessions++;

                printf("Student '%s' has been enrolled in session '%s'.\n", student->name, session->code);
            } else {
                printf("Session '%s' is already full. Cannot enroll student '%s'.\n", session->code, student->name);
            }
        } else {
            printf("Invalid Student ID! Enrollment failed.\n");
        }
    } else {
        printf("Invalid Session Code! Enrollment failed.\n");
    }
}

char* getStudentNameByID(const char* studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            char* studentName = malloc(strlen(students[i].name) + 1);
            strcpy(studentName, students[i].name);
            return studentName;
        }
    }
    return NULL; // Return NULL if student ID is not found
}

void listSessionsAndStudents(int sessionCount,  struct Session* sessions) {
    printf("Listing of Programming Café sessions and participating students:\n");
    printf("Student Name, Session Code, Tutor Code, Location\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < sessionCount; i++) {
        for (int j = 0; j < sessions[i].numEnrolledStudents; j++) {
            char* studentName = getStudentNameByID(sessions[i].studentIDs[j]);
            printf("%s, %s, %s, %s\n", studentName, sessions[i].code, sessions[i].tutor_code, sessions[i].location);
        }
    }
}

void listAssignedSessionsForStudent(struct Student student) {
    printf("Assigned Sessions: \n");
    printf("--------------------------------------------------\n");
    printf("Session Code\tTutor Code\tLocation\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < student.numAssignedSessions; i++) {
        printf("%s\t\t%s\t\t%s\n", student.assignedSessions[i].code, student.assignedSessions[i].tutor_code, student.assignedSessions[i].location);
    }

    printf("--------------------------------------------------\n");
}

void listAssignedSessions(char* tutorCode,int sessionCount,  struct Session* sessions) {
    printf("Assigned Sessions: %s \n",tutorCode);
    
    // Iterate through all sessions and check if the tutor code matches
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].tutor_code, tutorCode) == 0) {
            printf("Session Code: %s\n", sessions[i].code);
            printf("Title: %s\n", sessions[i].title);
            printf("Day: %s\n", sessions[i].day);
            printf("Start Time: %s\n", sessions[i].start_time);
            printf("Location: %s\n", sessions[i].location);
            printf("-------------------------\n");
        }
    }

    printf("\n");
}

void enrollInSession(struct Student* student, int sessionCount,  struct Session* sessions) {
    printf("Available Sessions:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("%s. %s\n", sessions[i].code, sessions[i].title);
    }
    
    char sessionCode[100];
    printf("Enter the Session Code you want to enroll in: ");
    scanf("%s", sessionCode);

    // Find the session with the given code
    int sessionIndex = -1;
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].code, sessionCode) == 0) {
            sessionIndex = i;
            break;
        }
    }

    // Check if the session exists
    if (sessionIndex == -1) {
        printf("Invalid Session Code. Enrollment failed.\n");
        return;
    }

    // Check if the session is already full
    // Assuming a session can have a maximum capacity of MAX_STUDENTS_PER_SESSION students
    if (sessions[sessionIndex].numEnrolledStudents >= MAX_STUDENTS_PER_SESSION) {
        printf("Session is already full. Enrollment failed.\n");
        return;
    }
     
    // Check if the student is already enrolled in the session
    for (int i = 0; i < student->numAssignedSessions; i++) {
        if (strcmp(student->assignedSessions[i].code, sessionCode) == 0) {
            printf("Student '%s' is already enrolled in session '%s'.\n", student->name, sessionCode);
            return;
        }
    }
    

    // Enroll the student in the session
    strcpy(sessions[sessionIndex].studentIDs[sessions[sessionIndex].numEnrolledStudents], student->id);
    sessions[sessionIndex].numEnrolledStudents++;

    // Update the assigned sessions for the student
    strcpy(student->assignedSessions[student->numAssignedSessions].code, sessions[sessionIndex].code);
    strcpy(student->assignedSessions[student->numAssignedSessions].tutor_code, sessions[sessionIndex].tutor_code);
    strcpy(student->assignedSessions[student->numAssignedSessions].location, sessions[sessionIndex].location);
    student->numAssignedSessions++;

    printf("Enrollment successful.\n");
}