#ifndef FACULTY_EVALUATION_H
#define FACULTY_EVALUATION_H

#define MAX_LINE_LENGTH 100
#define MAX_SECTIONS 10
#define MAX_CRITERIA 8
#define INITIAL_CAPACITY 10
#define INCREASE_FACTOR 2

typedef struct {
    char *code;
    char *course;
    int *sections;
    int sectionCount;
} Faculty;

typedef enum {
    INTERACTION_WITH_STUDENTS,
    AVAILABILITY_OUTSIDE_OF_CLASS,
    PUNCTUALITY,
    USE_OF_RESOURCES,
    ENCOURAGEMENT_OF_STUDENT_PARTICIPATION,
    FEEDBACK_AND_ASSESSMENT,
    COMMUNICATION_SKILLS,
    OVERALL_PERFORMANCE,
    NUM_CRITERIA
} EvaluationCriteria;

int readFacultyData(const char *filename, Faculty **faculties, int *facultyCount, int *facultyCapacity);
int findFaculty(Faculty **faculties, int facultyCount, const char *code);
int findSection(Faculty *faculty, int section);
void evaluateFaculty(Faculty *faculty, int section);

#endif
