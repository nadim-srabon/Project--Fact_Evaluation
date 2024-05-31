**This program is designed to evaluate faculty members based on various criteria provided by users. It reads faculty data from a text file, allows users to input evaluation scores for each criterion, calculates an overall grade, and saves the evaluation data to another file. The project consists of three main files:

source code (faculty_evaluation.c): This file contains the implementation of functions responsible for reading faculty data, finding faculty members, finding sections, and evaluating faculty based on predefined criteria.

main file (main.c): The main program that interacts with users, reads faculty data, conducts evaluations, and manages the evaluation process.

header file (faculty_evaluation.h): This header file defines constants, structures, and function prototypes used throughout the project.**

**Functionality**

readFacultyData: Reads faculty data from a text file and populates the Faculty structure.
findFaculty: Searches for a faculty member based on their code.
findSection: Checks if a section is associated with a faculty member.
evaluateFaculty: Conducts evaluations for a faculty member based on predefined criteria, calculates an overall grade, and saves the evaluation data to a file.

**Constants**

MAX_LINE_LENGTH: Maximum length of a line in the faculty data file.
MAX_SECTIONS: Maximum number of sections a faculty member can have.
MAX_CRITERIA: Total number of evaluation criteria.
INITIAL_CAPACITY: Initial capacity for storing faculty data.
INCREASE_FACTOR: Factor by which the capacity is increased if exceeded.

**Additional Information**

Evaluation criteria are predefined in the header file.
Evaluation scores range from 1 to 5, where 1 represents "Very Poor" and 5 represents "Very Good".
Overall grades are determined based on the average evaluation score.
