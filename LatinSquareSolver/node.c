/**
 * @file node.c
 * @brief C file for the node structure methods.
 *
 */

#include "node.h"

int initNode(Node **newNode, Node *node, int size) {
    if (*newNode == NULL) {
        *newNode = (Node *)malloc(sizeof(Node));
        if (*newNode == NULL) {
            perror("[ERROR] Failed to allocate memory for newNode in initNode");
            return EXIT_FAILURE;
        }
    }

    (*newNode)->size = size;

    // Allocate memory for the square matrix
    (*newNode)->square = (int **)malloc(size * sizeof(int *));
    if ((*newNode)->square == NULL) {
        perror("[ERROR] Failed to allocate memory for square array");
        free(*newNode);
        *newNode = NULL;  // Avoid dangling pointer
        return EXIT_FAILURE;
    }

    // Allocate memory for the moves array
    (*newNode)->moves = (int *)malloc(size * sizeof(int));
    if ((*newNode)->moves == NULL) {
        free((*newNode)->square);
        free(*newNode);
        *newNode = NULL;
        return EXIT_FAILURE;
    }

    // Allocate each row of the square matrix
    for (int i = 0; i < size; i++) {
        (*newNode)->square[i] = (int *)malloc(size * sizeof(int));
        if ((*newNode)->square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*newNode)->square[j]);
            }
            free((*newNode)->square);
            free((*newNode)->moves);
            free(*newNode);
            *newNode = NULL;
            return EXIT_FAILURE;
        }
    }

    // Initialize the square matrix and moves array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (*newNode)->square[i][j] = (node != NULL) ? node->square[i][j] : 0;
        }
        (*newNode)->moves[i] = (node != NULL) ? node->moves[i] : 1;
    }

    // Initialize row, column, and next pointer
    (*newNode)->row = node ? node->row : 0;
    (*newNode)->col = node ? node->col : 0;
    (*newNode)->next = NULL;

    return EXIT_SUCCESS;
}

void printNode(Node *node) {

    if (node == NULL || node->square == NULL) {
        printf("[ERROR] Node or square array is NULL\n");
        return;
    }

    for (int i = 0; i < node->size; i++) {
        printf("+");
        for (int j = 0; j < node->size; j++) {
            printf("-----+");
        }
        printf("\n");
        for (int j = 0; j < node->size; j++) {
            int number = (node->square)[i][j];
            // If the number is negative, print with parentheses
            if (number < 0) {
                printf("| (%d) ", -number);
            } else {
                // Print positive number normally
                printf("|  %d  ", number);
            }
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < node->size; j++) {
        printf("-----+");
    }
    printf("\n");
}

int updateNode(Node *node, int row, int col, int num) {
    if (node == NULL) {
        perror("[ERROR] Node is NULL in updateNode");
        return EXIT_FAILURE;
    }

    // Update the matrix value at the specified row and column
    node->square[row][col] = num;

    // Update the row and column attributes
    node->row = row;
    node->col = col;

    // Reset moves array
    for (int i = 0; i < node->size; i++) {
        node->moves[i] = 1;
    }

    return EXIT_SUCCESS;
}

void freeNode(Node *node) {
    if (node != NULL) {
        // Free each row of the square matrix
        if (node->square != NULL) {
            for (int i = 0; i < node->size; i++) {
                free(node->square[i]);
            }
            free(node->square);
        }

        // Free the moves array
        if (node->moves != NULL) {
            free(node->moves);
        }

        // Free the node structure itself
        free(node);
    }
}

Node *cloneNode(Node *node) {
    if (node == NULL) {
        printf("[ERROR] Node to clone is NULL\n");
        return NULL;
    }

    // Allocate memory for the new Node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("[ERROR] Failed to allocate memory for cloned node");
        return NULL;
    }

    // Copy basic attributes
    newNode->row = node->row;
    newNode->col = node->col;
    newNode->size = node->size;
    newNode->next = NULL;

    // Allocate and copy the moves array
    newNode->moves = (int *)malloc(node->size * sizeof(int));
    if (newNode->moves == NULL) {
        free(newNode);
        return NULL;
    }

    // Allocate and copy the square matrix
    newNode->square = (int **)malloc(node->size * sizeof(int *));
    if (newNode->square == NULL) {
        free(newNode->moves);
        free(newNode);
        return NULL;
    }
    for (int i = 0; i < node->size; i++) {
        newNode->square[i] = (int *)malloc(node->size * sizeof(int));
        if (newNode->square[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(newNode->square[j]);
            }
            free(newNode->square);
            free(newNode->moves);
            free(newNode);
            return NULL;
        }
        // Copy values from the original matrix
        for (int j = 0; j < node->size; j++) {
            newNode->square[i][j] = node->square[i][j];
        }
    }

    // Copy the moves array
    for (int i = 0; i < node->size; i++) {
        newNode->moves[i] = node->moves[i];
    }

    return newNode;
}
#ifdef DEBUG_NODE

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "node.h" // Assuming `Node` and its helpers like `cloneNode` and `freeNode` are defined here

int main() {
    printf("Debugging Node Implementation...\n");

    Node *node = NULL;

    // Test node initialization
    if (initNode(&node, NULL, 3) == EXIT_SUCCESS) {
        printf("[INFO] Node initialized successfully.\n");
    } else {
        printf("[ERROR] Node initialization failed.\n");
        return EXIT_FAILURE;
    }

    // Test updating the node
    if (updateNode(node, 1, 1, 5) == EXIT_SUCCESS) {
        printf("[INFO] Node updated successfully at (1, 1) with value 5.\n");
    } else {
        printf("[ERROR] Failed to update node.\n");
    }

    // Test printing the node
    printf("\n[INFO] Printing Node:\n");
    printNode(node);

    // Test cloning the node
    Node *clonedNode = cloneNode(node);
    if (clonedNode != NULL) {
        printf("\n[INFO] Cloned Node successfully.\n");
        printf("\n[INFO] Printing Cloned Node:\n");
        printNode(clonedNode);
    } else {
        printf("[ERROR] Cloning Node failed.\n");
    }

    // Test freeing the node
    freeNode(node);
    freeNode(clonedNode);
    printf("\n[INFO] Nodes freed successfully.\n");

    return EXIT_SUCCESS;
}

#endif
