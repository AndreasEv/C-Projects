/**
 * @file algorithm.c
 * @brief C file for solving the Latin square puzzle.
 *
 */

#include "algorithm.h"

bool checkDuplicates(Node *node, int num, int row, int col) {
    int size = node->size;

    // Check for duplicates in the row, excluding the current cell
    for (int k = 0; k < size; k++) {
        if (k != col && abs(node->square[row][k]) == num) {
            return true; // Duplicate found
        }
    }

    // Check for duplicates in the column, excluding the current cell
    for (int k = 0; k < size; k++) {
        if (k != row && abs(node->square[k][col]) == num) {
            return true; // Duplicate found
        }
    }

    return false; // No duplicates found
}

int findNextEmptyCell(Node *node, int *row, int *col) {
    if (node == NULL || row == NULL || col == NULL) {
        printf("Not all variables initialized in findNextEmptyCell\n");
        return EXIT_FAILURE;
    }

    int size = node->size;
    int lastRow = node->row; // Start searching from the last inserted row
    int lastCol = node->col; // Start searching from the last inserted column

    // Iterate over the matrix to find the next empty cell
    for (int i = lastRow; i < size; i++) {
        for (int j = lastCol; j < size; j++) {
            if ((node->square)[i][j] == 0) { // Check for empty cell
                *row = i;
                *col = j;
                return EXIT_SUCCESS; // Empty cell found
            }
        }
        lastCol = 0; // Reset column index after the first row iteration
    }

    *row = -1;
    *col = -1;
    return EXIT_FAILURE; // No empty cell found
}

bool solveLatinSquare(Stack *stack) {
    int size = stack->top->size;
    int pushCounter = 0; // Count the number of pushes
    int popCounter = 0;  // Count the number of pops
    int stepCounter = 1; // Track the solving steps

    Node *newNode = cloneNode(stack->top);
    int row, col;

    // Find the first empty cell in the puzzle
    findNextEmptyCell(newNode, &row, &col);

    while (row != -1 && col != -1) {
        bool pushed = false;

        // Attempt to place numbers in the current empty cell
        for (int i = 1; i <= size; i++) {
            if (newNode->moves[i - 1] == 1) { // Check if the number is valid for this step
                if (!checkDuplicates(newNode, i, row, col)) { // Validate against duplicates
                    updateNode(newNode, row, col, i); // Update the node with the new value
                    push(stack, newNode); // Push the updated node onto the stack
                    pushed = true;
                    break;
                }
            }
        }

        if (pushed) {
            printf("\nPUSH: STEP %d\n", stepCounter);
            pushCounter++;
        } else {
            // If no valid number, backtrack by popping the top node
            Node *retNode = (Node *)malloc(sizeof(Node));
            pop(stack, retNode);
            if(!isEmpty(stack)) { 
                int indexToChange = retNode->square[retNode->row][retNode->col] - 1;
                stack->top->moves[indexToChange] = 0; // Mark the number as invalid for this step
                printf("\nPOP: STEP %d\n", stepCounter);
                popCounter++;
            } else { // If stack is empty it's not solvable
                freeNode(retNode);
                freeNode(newNode);
                printf("LATIN SQUARE IS UNSOLVABLE!!");
                printf("\nPUSH NUM: %d\n", pushCounter);
                printf("POP NUM: %d\n", popCounter);
                return false;
            }
            freeNode(retNode); // Free the memory of the popped node
        }

        freeNode(newNode);
        newNode = cloneNode(stack->top); // Clone the current top node
        findNextEmptyCell(newNode, &row, &col); // Find the next empty cell
        printNode(stack->top); // Print the current state of the stack
        stepCounter++;
    }

    // Print statistics
    printf("\nPUSH NUM: %d\n", pushCounter);
    printf("POP NUM: %d\n", popCounter);

    freeNode(newNode); // Free the last node
    freeStack(stack);  // Free the stack

    return true; // Return success
}
#ifdef DEBUG_ALGORITHM

#include "algorithm.h"

int main() {
    printf("Debugging the solveLatinSquare function...\n");

    int size = 4; // Example size of the Latin square
    Stack *stack = NULL;

    // Initialize the stack
    if (initStack(&stack) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    // Create the initial Node for the Latin square
    Node *initialNode = NULL;
    if (initNode(&initialNode, NULL, size) == EXIT_FAILURE) {
        printf("[ERROR] Failed to initialize initialNode\n");
        freeStack(stack);
        return EXIT_FAILURE;
    }

    // Initialize the Latin square with some values (0 indicates empty cells)
    int initialSquare[4][4] = {
        {1, 2, 3, 4},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initialNode->square[i][j] = initialSquare[i][j];
        }
        initialNode->moves[i] = 1; // All numbers are valid at the start
    }

    // Push the initial node onto the stack
    push(stack, initialNode);

    // Free initialNode (stack now owns the copy)
    freeNode(initialNode);

    // Test findNextEmptyCell
    int row, col;
    if (findNextEmptyCell(stack->top, &row, &col) == EXIT_SUCCESS) {
        printf("Next empty cell found at row %d, column %d.\n", row, col);
    } else {
        printf("No empty cells found.\n");
    }

    // Test checkDuplicates
    bool hasDuplicates = checkDuplicates(stack->top, 2, 0, 1);
    printf("Check duplicates for number 2 at (0, 1): %s\n", hasDuplicates ? "true" : "false");

    // Solve the Latin square
    bool result = solveLatinSquare(stack);

    // Display the result
    if (result) {
        printf("Latin square solved successfully!\n");
    } else {
        printf("Failed to solve the Latin square.\n");
    }

    return EXIT_SUCCESS;
}

#endif
