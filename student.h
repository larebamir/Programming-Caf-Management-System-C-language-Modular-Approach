# include "constants.h"
# ifndef STUDENT_H
# define STUDENT_H



struct Student {
    char id[20];
    char name[50];
    char password[20];
    struct Session assignedSessions[MAX_ASSIGNED_SESSIONS];
    int numAssignedSessions;
};
struct Student registerStudent();
void enrollStudent(int sessionCount, struct Session* sessions, int studentCount, struct Student* students);
void listAssignedSessionsForStudent(struct Student student);
void enrollInSession(struct Student* student, int sessionCount,  struct Session* sessions);
extern struct Student students[MAX_STUDENTS];
extern int studentCount;

# endif /* STUDENT_H */
