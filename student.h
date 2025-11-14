#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PROGRAMME 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME];
    float mark;
    int active;
} Student;

extern Student students[MAX_STUDENTS];
extern int studentCount;

#endif#pragma once
