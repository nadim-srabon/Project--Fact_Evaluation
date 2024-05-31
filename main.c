#include <stdio.h>
#include <stdlib.h>
#include "faculty_evaluation.h"

int main() {
    const char *filename = "facultydata.txt";
    Faculty *faculties;
    int facultyCount = 0;
    int facultyCapacity = INITIAL_CAPACITY;

    if (!readFacultyData(filename, &faculties, &facultyCount, &facultyCapacity)) {
        printf("Error reading faculty data file.\n");
        return 1;
    }

    int evaluateAnother = 1; // Flag to control whether to evaluate another faculty member
    while (evaluateAnother) {
        char facultyCode[10];
        printf("Enter faculty code: ");
        scanf("%9s", facultyCode); // Limit input to prevent buffer overflow

        int facultyIndex = findFaculty(&faculties, facultyCount, facultyCode);
        if (facultyIndex == -1) {
            printf("Code does not match.\n");
            continue; // Ask for faculty code again
        }

        int section;
        printf("Enter section: ");
        scanf("%d", &section);

        if (!findSection(&faculties[facultyIndex], section)) {
            printf("Section does not match.\n");
            continue; // Ask for section again
        }

        // Proceed with the evaluation process
        printf("Faculty code and section match. Proceeding with evaluation...\n");
        evaluateFaculty(&faculties[facultyIndex], section);

        // Ask if the user wants to evaluate another faculty member
        char choice;
        printf("Do you want to evaluate another faculty member? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            evaluateAnother = 0;
        }
    }

    for (int i = 0; i < facultyCount; i++) {
        free(faculties[i].code);
        free(faculties[i].course);
        free(faculties[i].sections);
    }
    free(faculties);

    return 0;
}
