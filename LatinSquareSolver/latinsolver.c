/**
 * @file latinsolver.c
 * @brief Main C file for the latin solver algorithm
 *
 */


#include "stack.h"
#include "algorithm.h"

// Function to read a Latin square from a file and initialize a Node structure
static int readLatinNode(Node **node, const char *filename, int *size)
{
    // Open the file for reading
    FILE *file = fopen(filename, "r");

    // Check if the file was successfully opened
    if (file == NULL) {
        perror("Error opening file"); // Print error message if file can't be opened
        exit(1); // Exit the program with an error code
    }

    // Read the size of the square from the file
    if (fscanf(file, "%d", size) != 1) {
        // If size cannot be read, print an error message and exit
        printf("Invalid size in file\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    initNode(&(*node), NULL, *size);

    // Read the Latin square values into the Node structure
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            // Read each value from the file into the square matrix
            if (fscanf(file, "%d", &((*node)->square)[i][j]) != 1) {
                // If a value cannot be read, print an error and exit
                printf("File contains invalid values!\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }

            // Check if the value is within the valid range for a Latin square
            if ((*node)->square[i][j] < -(*size) || (*node)->square[i][j] > *size) {
                // Print an error and exit if the value is out of range
                printf("File contains invalid values\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Check for additional values in the file
    int extraValue;
    if (fscanf(file, "%d", &extraValue) == 1) {
        // If an extra value is found, print an error message
        printf("Error: File contains extra values beyond the expected Latin square\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Close the file after reading
    fclose(file);

    // Return the initialized Node structure
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // Check if a filename argument is provided
    if (argc < 2) {
        // Print usage information if no filename is provided
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE; // Exit with an error code
    }

    Node *node = NULL; // Initialize the Node pointer to NULL
    int size; // Variable to store the size of the Latin square

    // Read the Latin square from the file and store it in the Node structure
    readLatinNode(&node, argv[1], &size);

    Stack *stack = NULL;
    initStack(&stack);
    push(stack, node);

    if(!solveLatinSquare(stack)) {
        free(stack);
    }

    freeNode(node);

    return EXIT_SUCCESS; // Exit the program successfully
}
