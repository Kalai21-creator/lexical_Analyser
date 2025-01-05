#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define MAX_FILENAME_LEN 256

// Function to validate file existence
int validateFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}

int main() {
    char filename[MAX_FILENAME_LEN];
    FILE *source;

    printf("\n-------------------------[[ << LEXICAL ANALYSER >> ]]-------------------------------\n\n");

    // Prompt user for the source file
    printf("Enter the C source code filename (e.g., 1.txt): ");
    fgets(filename, MAX_FILENAME_LEN, stdin);

    // Remove the newline character from the filename
    filename[strcspn(filename, "\n")] = '\0';

    // Validate the file
    if (!validateFile(filename)) {
        printf("Error: The file '%s' does not exist or cannot be accessed.\n", filename);
        return 1;
    }

    // Open the file for reading
    source = fopen(filename, "r");
    if (source == NULL) {
        printf("Error: Could not open the source code file '%s'.\n", filename);
        return 1;
    }

    // Perform lexical analysis
    printf("\nStarting lexical analysis for file: %s\n\n", filename);
    lexicalAnalyzer(source);

    // Close the file
    fclose(source);

    printf("\n\n---------------------------------------------------------------------------------------\n\n");
    return 0;
}
