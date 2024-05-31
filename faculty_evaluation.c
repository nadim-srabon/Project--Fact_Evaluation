#include "faculty_evaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *criteriaNames[MAX_CRITERIA] = {
    "Interaction with Students",
    "Availability outside of class",
    "Punctuality",
    "Use of resources",
    "Encouragement of student Participation",
    "Feedback and Assessment",
    "Communication Skills",
    "Overall Performance"};

int readFacultyData(const char *filename, Faculty **faculties, int *facultyCount, int *facultyCapacity) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    *facultyCount = 0;
    *faculties = (Faculty *)malloc(*facultyCapacity * sizeof(Faculty));
    if (!*faculties) {
        fclose(file);
        perror("Memory allocation error");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (*facultyCount >= *facultyCapacity) {
            *facultyCapacity *= INCREASE_FACTOR;
            *faculties = (Faculty *)realloc(*faculties, *facultyCapacity * sizeof(Faculty));
            if (!*faculties) {
                fclose(file);
                perror("Memory allocation error");
                return 0;
            }
        }

        Faculty *faculty = &(*faculties)[*facultyCount];
        char *token = strtok(line, " ");
        if (!token) continue;
        faculty->code = strdup(token);

        token = strtok(NULL, " ");
        if (!token) continue;
        faculty->course = strdup(token);

        faculty->sectionCount = 0;
        faculty->sections = (int *)malloc(MAX_SECTIONS * sizeof(int));
        if (!faculty->sections) {
            fclose(file);
            perror("Memory allocation error");
            return 0;
        }

        while ((token = strtok(NULL, ",\n"))) {
            if (faculty->sectionCount < MAX_SECTIONS) {
                faculty->sections[faculty->sectionCount++] = atoi(token);
            }
        }

        (*facultyCount)++;
    }

    fclose(file);
    printf("----Welcome to Faculty Evaluation Module\n\n");
    return 1;
}

int findFaculty(Faculty **faculties, int facultyCount, const char *code) {
    for (int i = 0; i < facultyCount; i++) {
        if (strcmp((*faculties)[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

int findSection(Faculty *faculty, int section) {
    for (int i = 0; i < faculty->sectionCount; i++) {
        if (faculty->sections[i] == section) {
            return 1;
        }
    }
    return 0;
}

void evaluateFaculty(Faculty *faculty, int section) {
    int *evaluations = (int *)malloc(MAX_CRITERIA * sizeof(int));
    if (!evaluations) {
        perror("Memory allocation error");
        return;
    }

    printf("\nPlease rate the following criteria on a scale from 1 to 5:\n");
    printf("1 - Very Poor\n2 - Poor\n3 - Neutral\n4 - Good\n5 - Very Good\n\n");

    for (int i = 0; i < MAX_CRITERIA; i++) {
        do {
            printf("%s: ", criteriaNames[i]);
            scanf("%d", &evaluations[i]);
        } while (evaluations[i] < 1 || evaluations[i] > 5);
    }

    // Calculate the average rating
    int sum = 0;
    for (int i = 0; i < MAX_CRITERIA; i++) {
        sum += evaluations[i];
    }
    double average = (double)sum / MAX_CRITERIA;

    // Determine the grade based on the average rating
    char grade;
    if (average >= 4.5) grade = 'A';
    else if (average >= 3.5) grade = 'B';
    else if (average >= 2.5) grade = 'C';
    else if (average >= 1.5) grade = 'D';
    else grade = 'E';

    // Save the evaluation data to a file
    FILE *file = fopen("evaluation_data.txt", "a");
    if (!file) {
        perror("Error opening evaluation data file");
        free(evaluations);
        return;
    }

    fprintf(file, "Faculty Code: %s, Section: %d\n", faculty->code, section);
    for (int i = 0; i < MAX_CRITERIA; i++) {
        fprintf(file, "%s: %d\n", criteriaNames[i], evaluations[i]);
    }
    fprintf(file, "Average Rating: %.2f\n", average);
    fprintf(file, "Overall Grade: %c\n\n", grade);
    fclose(file);

    printf("\n\n\nEvaluation Summary:\n");
    for (int i = 0; i < MAX_CRITERIA; i++) {
        printf("%s: %d\n", criteriaNames[i], evaluations[i]);
    }

    printf("\n\n");

    free(evaluations);
}
