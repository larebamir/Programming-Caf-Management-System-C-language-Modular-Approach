#include "constants.h"
#ifndef TUTOR_H
#define TUTOR_H


struct Tutor {
    char id[20];
    char name[50];
    char title[50];
    char password[20];
};

struct Tutor addTutor();

extern struct Tutor tutors[MAX_TUTORS];
extern int tutorCount;

#endif /* TUTOR_H */
