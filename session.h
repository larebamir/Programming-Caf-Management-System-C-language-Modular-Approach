# include "constants.h"
#include "tutor.h"

# ifndef SESSION_H
# define SESSION_H


struct Session {
    char code[20];
    char title[50];
    char day[20];
    char start_time[20];
    char location[50];
    char tutor_code[20];
    char studentIDs[MAX_STUDENTS_PER_SESSION][100]; // Array to store student IDs
    int numEnrolledStudents; // Counter to keep track of enrolled students

};
struct Session addSession( int tutorCount, struct Tutor* tutors);
void listSessionsAndStudents(int sessionCount,  struct Session* sessions);
void listAssignedSessions(char* tutorCode, int sessionCount,  struct Session* sessions);
extern struct Session sessions[MAX_SESSIONS];
extern int sessionCount;

#endif /* SESSION_H */
